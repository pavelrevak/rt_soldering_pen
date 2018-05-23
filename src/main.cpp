#include <string.h>

#include "board/clock.hpp"
#include "board/systick.hpp"
#include "board/debug.hpp"
#include "board/adc.hpp"
#include "board/i2c.hpp"
#include "board/heater.hpp"
#include "board/buttons.hpp"
#include "board/display.hpp"
#include "lib/str.hpp"
#include "lib/font.hpp"
#include "lib/pid.hpp"
#include "lib/button.hpp"
#include "lib/preset.hpp"
#include "screen/main.hpp"

class MainClass {
    unsigned last_ticks = 0;

    static const int PERIOD_TIME_MS = 150;  // ms
    static const int STABILIZE_TIME_MS = 2;  // ms
    static const int IDLE_TIME_MIN_MS = 8;  // ms
    static const int STANDBY_TIME_S = 30;  // s
    static const int PERIOD_TICKS = Board::Clock::CORE_FREQ / 1000 * PERIOD_TIME_MS;
    static const int PERIOD_HEATING_TICKS = Board::Clock::CORE_FREQ / 1000 * (PERIOD_TIME_MS - STABILIZE_TIME_MS - IDLE_TIME_MIN_MS);
    static const int STABILIZE_TICKS = Board::Clock::CORE_FREQ / 1000 * STABILIZE_TIME_MS;
    static const int64_t STEADY_TICKS = STANDBY_TIME_S * Board::Clock::CORE_FREQ;
    static const int PID_K_PROPORTIONAL = 700;
    static const int PID_K_INTEGRAL = 200;
    static const int PID_K_DERIVATE = 100;
    static const int HEATING_POWER_MIN = 100;  // 0.1 W
    static const int HEATING_POWER_MAX = 40 * 1000;  // 20.0 W

    int64_t uptime_ticks = 0;
    int64_t staady_ticks = 0;
    int64_t heating_power = 0;  // uW * PERIOD_TICKS
    int64_t cumulated_power = 0;  // uW * PERIOD_TICKS
    int64_t total_power = 0;  // uW * CORE_FREQ
    int period_ticks = 0;
    int measure_cycle_heat_ticks = 0;
    int stabilize_ticks = 0;
    int heat_idle_ticks = 0;
    int heat_ticks = 0;
    int pen_temperature = 0;  // 0.001 degree C
    int cpu_temperature = 0;  // 0.001 degree C
    int cpu_voltage_idle = 0;  // mV
    int cpu_voltage_heat = 0;  // mV
    int supply_voltage_idle = 0;  // mV
    int supply_voltage_heat = 0;  // mV
    int supply_voltage_drop = 0;  // mV
    int pen_current = 0;  // mA
    int idle_measurements_count = 0;
    int heat_measurements_count = 0;
    int average_request_power = 0;
    int average_request_power_short = 0;

    Preset preset;
    Pid pid;

    screen::Main screen_main;
    screen::Screen *current_screen = &screen_main;

    enum class HeatPeriodState {
        PERIOD_START,
        DEBUG_PROCESS,
        BUTTONS_PROCESS,
        DISPLAY_PROCESS,
        PID_PROCESS,
        HEATING_START,
        HEATING_PROCESS,
        HEATING_END,
        STABILIZE_START,
        STABILIZE_PROCESS,
        STABILIZE_END,
        IDLE_START,
        IDLE_PROCESS,
        IDLE_END,
    } heat_period_state;

    enum class TempSensorStatus {
        UNKNOWN,
        OK,
        BROKEN,
        SHORTED,
    } temp_sensor_status = TempSensorStatus::UNKNOWN;

    enum class HeatingElementStatus {
        UNKNOWN,
        OK,
        BROKEN,
        SHORTED,
        WRONG_RESISTANCE,
    } heating_element_status = HeatingElementStatus::UNKNOWN;

    void period_start() {
        // heat_period_state = HeatPeriodState::DEBUG_PROCESS;
        heat_period_state = HeatPeriodState::BUTTONS_PROCESS;
    }

    void debug_process() {
        // Board::debug.dbg << uptime_ticks;
        // Board::debug.dbg << ',' << period_ticks;
        // Board::debug.dbg << ',' << heat_idle_ticks;
        // Board::debug.dbg << ',' << heat_ticks;
        // Board::debug.dbg << ',' << preset_temperature[preset_temperature_select];
        // Board::debug.dbg << ',' << pen_temperature;
        // Board::debug.dbg << ',' << cpu_temperature;
        // Board::debug.dbg << ',' << cpu_voltage_idle;
        // Board::debug.dbg << ',' << cpu_voltage_heat;
        // Board::debug.dbg << ',' << supply_voltage_idle;
        // Board::debug.dbg << ',' << supply_voltage_heat;
        // Board::debug.dbg << ',' << pen_current;
        // Board::debug.dbg << ',' << idle_measurements_count;
        // Board::debug.dbg << ',' << heat_measurements_count;
        // Board::debug.dbg << ',' << heating_power / PERIOD_TICKS / 1000;
        // Board::debug.dbg << ',' << cumulated_power / PERIOD_TICKS / 1000;
        // Board::debug.dbg << IOStream::endl;
        heat_period_state = HeatPeriodState::BUTTONS_PROCESS;
    }

    static const unsigned BUTTONS_SAMPLE_TICKS = Board::Clock::CORE_FREQ / 1000 * 10;
    unsigned buttons_sample_ticks = 0;
    Button button_up;
    Button button_dw;
    Button button_both;

    void buttons_process_fast(unsigned delta_ticks) {
        buttons_sample_ticks += delta_ticks;
        if (buttons_sample_ticks < BUTTONS_SAMPLE_TICKS) return;
        buttons_sample_ticks -= BUTTONS_SAMPLE_TICKS;
        bool btn_up = Board::buttons.is_pressed_up();
        bool btn_dw = Board::buttons.is_pressed_dw();
        button_up.process(btn_up, btn_dw, 10);
        button_dw.process(btn_dw, btn_up, 10);
        button_both.process(btn_up && btn_dw, false, 10);
    }

    enum class Screen {
        MAIN,
        INFO,
        SETUP,
    } screen = Screen::MAIN;

    void buttons_process() {
        Button::Action btn_up = button_up.get_status();
        Button::Action btn_dw = button_dw.get_status();
        Button::Action btn_both = button_both.get_status();
        switch (screen) {
            case Screen::MAIN:
                if (current_screen->button_up(btn_up)) button_up.block();
                if (current_screen->button_dw(btn_dw)) button_dw.block();
                if (current_screen->button_both(btn_both)) button_both.block();
                break;
            case Screen::INFO:
                break;
            case Screen::SETUP:
                break;
        }
        heat_period_state = HeatPeriodState::DISPLAY_PROCESS;
    }

    void display_process_main() {
        if (Board::i2c.is_busy()) return;
        auto &fb = Board::display.get_fb();
        fb.clear();
        current_screen->redraw();
        Board::display.redraw();
        heat_period_state = HeatPeriodState::PID_PROCESS;
    }

    void display_process() {
        switch (screen) {
        case Screen::MAIN:
            display_process_main();
            break;
        case Screen::INFO:
            break;
        case Screen::SETUP:
            break;
        }
    }

    void pid_process() {
        if (temp_sensor_status != TempSensorStatus::OK) {
            pid.reset();
            heating_power = 0;
            heat_period_state = HeatPeriodState::HEATING_START;
            return;
        }
        int request_power = pid.process(cpu_temperature + pen_temperature, preset.get_temperature());
        // limit pen power
        if (request_power > HEATING_POWER_MAX) request_power = HEATING_POWER_MAX;
        if (request_power < HEATING_POWER_MIN) request_power = 0;
        // raw heating power
        heating_power = (int64_t)request_power * 1000 * PERIOD_TICKS;
        average_request_power_short *= 2;
        average_request_power_short += request_power;
        average_request_power_short /= 3;
        average_request_power *= 9;
        average_request_power += request_power;
        average_request_power /= 10;
        heat_period_state = HeatPeriodState::HEATING_START;
    }

    void heating_start() {
        cumulated_power = 0;
        heat_ticks = 0;
        if ((temp_sensor_status != TempSensorStatus::OK) || (heating_power <= 0)) {
            heat_period_state = HeatPeriodState::IDLE_START;
            return;
        }
        heating_element_status = HeatingElementStatus::UNKNOWN;
        measure_cycle_heat_ticks = 0;
        heat_measurements_count = 0;
        cpu_voltage_heat = 0;
        supply_voltage_heat = 0;
        pen_current = 0;
        Board::adc.measure_heat_start();
        Board::heater.on();
        heat_period_state = HeatPeriodState::HEATING_PROCESS;
    }

    void heating_process(unsigned delta_ticks) {
        heat_ticks += delta_ticks;
        measure_cycle_heat_ticks += delta_ticks;
        if (!Board::adc.measure_is_done()) return;
        cpu_voltage_heat += Board::adc.get_cpu_voltage();
        supply_voltage_heat += Board::adc.get_supply_voltage();
        pen_current += Board::adc.get_pen_current();
        heat_measurements_count++;
        cumulated_power += (int64_t)Board::adc.get_supply_voltage() * Board::adc.get_pen_current() * measure_cycle_heat_ticks;
        measure_cycle_heat_ticks = 0;
        if ((cumulated_power >= heating_power) || (period_ticks >= PERIOD_HEATING_TICKS)) {
            total_power += cumulated_power;
            Board::heater.off();
            heat_period_state = HeatPeriodState::HEATING_END;
            return;
        }
        Board::adc.measure_heat_start();
    }

    void heating_end() {
        cpu_voltage_heat /= heat_measurements_count;
        supply_voltage_heat /= heat_measurements_count;
        supply_voltage_drop = supply_voltage_heat - supply_voltage_idle;
        pen_current /= heat_measurements_count;
        screen_main.set_supply_voltage_drop(supply_voltage_drop);
        screen_main.set_total_power(total_power / Board::Clock::CORE_FREQ / 1000 / 3600);

        heat_period_state = HeatPeriodState::STABILIZE_START;
    }

    void stabilize_start() {
        stabilize_ticks = 0;
        heat_period_state = HeatPeriodState::STABILIZE_PROCESS;
    }

    void stabilize_process(unsigned delta_ticks) {
        stabilize_ticks += delta_ticks;
        if (stabilize_ticks < STABILIZE_TICKS) return;
        heat_period_state = HeatPeriodState::STABILIZE_END;
    }

    void stabilize_end() {
        heat_period_state = HeatPeriodState::IDLE_START;
    }

    void idle_start() {
        temp_sensor_status = TempSensorStatus::UNKNOWN;
        heat_idle_ticks = 0;
        idle_measurements_count = 0;
        cpu_voltage_idle = 0;
        pen_temperature = 0;
        cpu_temperature = 0;
        supply_voltage_idle = 0;
        Board::adc.measure_idle_start();
        screen_main.set_heating_power(cumulated_power / PERIOD_TICKS / 1000);
        heat_period_state = HeatPeriodState::IDLE_PROCESS;
    }

    void idle_process(unsigned delta_ticks) {
        heat_idle_ticks += delta_ticks;
        if (!Board::adc.measure_is_done()) return;
        cpu_voltage_idle += Board::adc.get_cpu_voltage();
        supply_voltage_idle += Board::adc.get_supply_voltage();
        cpu_temperature += Board::adc.get_cpu_temperature();
        if (Board::adc.is_pen_broken()) {
            if (temp_sensor_status != TempSensorStatus::BROKEN) {
                preset.set_standby();
            }
            temp_sensor_status = TempSensorStatus::BROKEN;
        } else {
            if (temp_sensor_status == TempSensorStatus::UNKNOWN) {
                temp_sensor_status = TempSensorStatus::OK;
            }
            pen_temperature += Board::adc.get_pen_temperature();
        }
        // measurements counter
        idle_measurements_count++;
        if (period_ticks >= PERIOD_TICKS) {
            period_ticks -= PERIOD_TICKS;
            heat_period_state = HeatPeriodState::IDLE_END;
            return;
        }
        Board::adc.measure_idle_start();
    }

    void idle_end() {
        cpu_voltage_idle /= idle_measurements_count;
        supply_voltage_idle /= idle_measurements_count;
        cpu_temperature /= idle_measurements_count;
        pen_temperature /= idle_measurements_count;
        heat_period_state = HeatPeriodState::PERIOD_START;
        if (temp_sensor_status == TempSensorStatus::OK) {
            screen_main.set_pen_temperature(cpu_temperature + pen_temperature);
        } else {
            screen_main.set_pen_temperature(cpu_temperature);
        }
        screen_main.set_supply_voltage_idle(supply_voltage_idle);
        if (staady_ticks > STEADY_TICKS) {
            staady_ticks = 0;
            preset.set_standby();
        } else {
            int derivate_request_power = average_request_power_short - average_request_power;
            if ((derivate_request_power > 150) || derivate_request_power < -200) {
                staady_ticks = 0;
            }
            screen_main.set_idle_seconds(staady_ticks / Board::Clock::CORE_FREQ);
        }
    }

    void process(unsigned delta_ticks) {
        uptime_ticks += delta_ticks;
        period_ticks += delta_ticks;
        staady_ticks += delta_ticks;
        buttons_process_fast(delta_ticks);
        switch (heat_period_state) {
            case HeatPeriodState::PERIOD_START: period_start(); break;
            case HeatPeriodState::DEBUG_PROCESS: debug_process(); break;
            case HeatPeriodState::BUTTONS_PROCESS: buttons_process(); break;
            case HeatPeriodState::DISPLAY_PROCESS: display_process(); break;
            case HeatPeriodState::PID_PROCESS: pid_process(); break;
            case HeatPeriodState::HEATING_START: heating_start(); break;
            case HeatPeriodState::HEATING_PROCESS: heating_process(delta_ticks); break;
            case HeatPeriodState::HEATING_END: heating_end(); break;
            case HeatPeriodState::STABILIZE_START: stabilize_start(); break;
            case HeatPeriodState::STABILIZE_PROCESS: stabilize_process(delta_ticks); break;
            case HeatPeriodState::STABILIZE_END: stabilize_end(); break;
            case HeatPeriodState::IDLE_START: idle_start(); break;
            case HeatPeriodState::IDLE_PROCESS: idle_process(delta_ticks); break;
            case HeatPeriodState::IDLE_END: idle_end(); break;
        }
    }

    void init_hw() {
        Board::clock.init_hw();
        Board::systick.init_hw();
        Board::debug.init_hw();
        Board::heater.init_hw();
        Board::buttons.init_hw();
        Board::adc.init_hw();
        Board::i2c.init_hw();
        Board::display.init_hw();
    }

public:
    MainClass() : screen_main(preset) {}

    void run() {
        init_hw();
        io::Nvic::isr_enable();

        Board::display.init();

        pid.set_constants(PID_K_PROPORTIONAL, PID_K_INTEGRAL, PID_K_DERIVATE, 1000 / PERIOD_TIME_MS, HEATING_POWER_MAX);

        Board::debug.dbg << IOStream::endl;
        last_ticks = Board::systick.get_counter();

        heat_period_state = HeatPeriodState::PERIOD_START;

        while (true) {
            unsigned delta_ticks = last_ticks;
            last_ticks = Board::systick.get_counter();
            delta_ticks = ((1 << Board::Systick::DIV_BITS) - 1) & (delta_ticks - last_ticks);
            process(delta_ticks);
        }
    }
};

void main_app() {
    MainClass main_class;
    // start application
    main_class.run();
}
