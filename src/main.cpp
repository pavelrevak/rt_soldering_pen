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

class MainClass {
    unsigned last_ticks = 0;

    static const int PERIOD_TIME = 150;  // 200 ms
    static const int STABILIZE_TIME = 2;  // 2 ms
    static const int IDLE_TIME_MIN = 8;  // 8 ms
    static const int PERIOD_TICKS = Board::Clock::CORE_FREQ / 1000 * PERIOD_TIME;
    static const int PERIOD_HEATING_TICKS = Board::Clock::CORE_FREQ / 1000 * (PERIOD_TIME - STABILIZE_TIME - IDLE_TIME_MIN);
    static const int STABILIZE_TICKS = Board::Clock::CORE_FREQ / 1000 * STABILIZE_TIME;  // 2 ms
    static const int PRESET_TEMPERATURE_MIN = 20 * 1000;  // 20 degree C
    static const int PRESET_TEMPERATURE_MAX = 400 * 1000;  // 400 degree C
    static const int PRESET_TEMPERATURE_STEP = 10 * 1000;  //  10 degree C
    static const int STANDBY_TEMPERATURE = 20 * 1000;  //  20 degree C
    static const int STANDBY_TICKS = 30 * Board::Clock::CORE_FREQ;  // 60 s
    static const int PID_K_PROPORTIONAL = 700;
    static const int PID_K_INTEGRAL = 200;
    static const int PID_K_DERIVATE = 100;
    static const int HEATING_POWER_MIN = 100;  // 0.1 W
    static const int HEATING_POWER_MAX = 40 * 1000;  // 20.0 W

    int64_t uptime_ticks = 0;
    int64_t standby_ticks = STANDBY_TICKS;  // PERIOD_TICKS / s
    int64_t heating_power = 0;  // uW * PERIOD_TICKS
    int64_t cumulated_power = 0;  // uW * PERIOD_TICKS
    int64_t total_power = 0;  // uW * CORE_FREQ
    int period_ticks = 0;
    int measure_cycle_heat_ticks = 0;
    int stabilize_ticks = 0;
    int idle_ticks = 0;
    int heat_ticks = 0;
    int preset_temperature[2] = { 300 * 1000, 250 * 1000};  // 0.001 degree C
    int preset_temperature_select = 0;
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

    Pid pid;

    enum class PeriodState {
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
    } period_state;

    void change_state(PeriodState state) {
        period_state = state;
    }

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
        // change_state(PeriodState::DEBUG_PROCESS);
        change_state(PeriodState::BUTTONS_PROCESS);
    }

    void debug_process() {
        // Board::debug.dbg << uptime_ticks;
        // Board::debug.dbg << ',' << period_ticks;
        // Board::debug.dbg << ',' << idle_ticks;
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
        change_state(PeriodState::BUTTONS_PROCESS);
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
        button_up.process_fast(Board::buttons.is_pressed_up(), Board::buttons.is_pressed_down());
        button_dw.process_fast(Board::buttons.is_pressed_down(), Board::buttons.is_pressed_up());
        button_both.process_fast(Board::buttons.is_pressed_up() && Board::buttons.is_pressed_down(), false);
    }

    enum class Mode {
        STANDBY,
        ON,
    } mode = Mode::STANDBY;

    void set_standby() {
        mode = Mode::STANDBY;
    }

    void set_on() {
        standby_ticks = 0;
        mode = Mode::ON;
    }

    int edit_preset = -1;
    int edit_blink = 0;
    bool edit_blocking = false;

    void buttons_process_main() {
        Button::Action btn_up = button_up.process();
        Button::Action btn_dw = button_dw.process();
        Button::Action btn_both = button_both.process();
        if (edit_preset < 0) {
            switch (btn_up) {
                case Button::Action::RELEASED_SHORT:
                    // wake-up and preset 1
                    preset_temperature_select = 0;
                    set_on();
                    break;
                case Button::Action::PRESSED_LONG:
                    // edit preset 1
                    edit_preset = 0;
                    edit_blink = 5;
                    edit_blocking = true;
                    break;
                default:
                    break;
            }
            switch (btn_dw) {
                case Button::Action::RELEASED_SHORT:
                    // wake-up and preset 2
                    preset_temperature_select = 1;
                    set_on();
                    break;
                case Button::Action::PRESSED_LONG:
                    // edit preset 2
                    edit_preset = 1;
                    edit_blink = 5;
                    edit_blocking = true;
                    return;
                default:
                    break;
            }
            switch (btn_both) {
                case Button::Action::RELEASED_SHORT:
                    set_standby();
                    break;
                case Button::Action::PRESSED_LONG:
                    // enter MENU
                    break;
                default:
                    break;
            }
        } else {
            switch (btn_up) {
                case Button::Action::RELEASED_SHORT:
                case Button::Action::PRESSED_LONG:
                case Button::Action::REPEAT:
                    if (edit_blocking) break;
                    if (preset_temperature[edit_preset] < PRESET_TEMPERATURE_MAX) {
                        preset_temperature[edit_preset] += PRESET_TEMPERATURE_STEP;
                    }
                    edit_blink = 0;
                case Button::Action::PRESSED:
                    edit_blocking = false;
                    edit_blink = -6;
                default:
                    break;
            }
            switch (btn_dw) {
                case Button::Action::RELEASED_SHORT:
                case Button::Action::PRESSED_LONG:
                case Button::Action::REPEAT:
                    if (edit_blocking) break;
                    if (preset_temperature[edit_preset] > PRESET_TEMPERATURE_MIN) {
                        preset_temperature[edit_preset] -= PRESET_TEMPERATURE_STEP;
                    }
                    edit_blink = 0;
                case Button::Action::PRESSED:
                    edit_blocking = false;
                    edit_blink = -6;
                default:
                    break;
            }
            switch (btn_both) {
                case Button::Action::RELEASED_SHORT:
                    edit_preset = -1;
                    break;
                default:
                    break;
            }
        }
        change_state(PeriodState::DISPLAY_PROCESS);
    }

    enum class Screen {
        MAIN,
        INFO,
        SETUP,
    } screen = Screen::MAIN;

    void buttons_process() {
        switch (screen) {
        case Screen::MAIN:
            buttons_process_main();
            break;
        case Screen::INFO:
            break;
        case Screen::SETUP:
            break;
        }
    }

    /** display preset temperature in 1/1000 degree Celsius */
    void display_preset_temperature(int x, int y, int preset) {
        if ((edit_preset == preset) && (edit_blink > 4)) return;
        auto &fb = Board::display.get_fb();
        char tmps[20];
        Str::i2a(preset_temperature[preset] / 1000, 3, '\240', tmps);
        if (preset_temperature_select != preset) {
            x = 6;
        } else if (mode == Mode::STANDBY) {
            x = fb.draw_text(x, y, "\274", Font::num13);
        } else {
            x = fb.draw_text(x, y, "\275", Font::num13);
        }
        x = fb.draw_text(x, y, tmps, Font::num13);
        fb.draw_text(x, y, "\260C", Font::num7);
    }

    /** display temperature in 1/1000 degree Celsius */
    void display_temperature(int x, int y, int temperature) {
        auto &fb = Board::display.get_fb();
        char tmps[20];
        Str::i2a((temperature + 500) / 1000, 3, '\240', tmps);
        // Str::i2a((temperature + 500) / 1000, 3, '0', tmps);
        x = fb.draw_text(x, y, tmps, Font::num22);
        fb.draw_text(x, y, "\260C", Font::num9);
    }

    /** display voltage in millivolts */
    void display_voltage(int x, int y, int voltage) {
        auto &fb = Board::display.get_fb();
        char tmps[20];
        if (voltage < 10 * 1000) {
            Str::d2a((voltage) / 10, 1, 2, '\240', tmps);
        } else {
            Str::d2a((voltage) / 100, 1, 1, '\240', tmps);
        }
        x = fb.draw_text(x, y, tmps, Font::num7);
        fb.draw_char(x, y, 'V', Font::sans8);
    }

    /** display power in milliwatts */
    void display_watts(int x, int y, int watts) {
        auto &fb = Board::display.get_fb();
        char tmps[20];
        Str::d2a(watts / 100, 2, 1, '\240', tmps);
        x = fb.draw_text(x, y, tmps, Font::num7);
        fb.draw_char(x, y, 'W', Font::sans8);
    }

    /** display power in milliwatts */
    void display_watt_hours(int x, int y, int watt_hours) {
        auto &fb = Board::display.get_fb();
        char tmps[20];
        if (watt_hours < 100000) {
            Str::d2a(watt_hours / 10, 2, 2, '\240', tmps);
        } else {
            Str::d2a(watt_hours / 100, 3, 1, '\240', tmps);
        }
        x = fb.draw_text(x, y, tmps, Font::num7);
        fb.draw_text(x, y, "Wh", Font::sans8);
    }

    void display_time(int x, int y, int time) {
        auto &fb = Board::display.get_fb();
        char tmps[20];
        Str::i2a(time, 3, '\240', tmps);
        x = fb.draw_text(x, y, tmps, Font::num7);
    }

    int blink = 0;

    void display_process_main() {
        if (Board::i2c.is_busy()) return;
        auto &fb = Board::display.get_fb();
        fb.clear();
        if (blink++ >= 6) blink = 0;
        if (edit_blink++ >= 6) edit_blink = 0;
        display_preset_temperature(0, 0, 0);
        display_preset_temperature(0, 19, 1);
        display_voltage(106, 14, supply_voltage_idle);

        int temperature = cpu_temperature;
        if ((temp_sensor_status == TempSensorStatus::OK) && (heating_element_status <= HeatingElementStatus::OK)) {
            temperature += pen_temperature;
            if (supply_voltage_drop) {
                display_voltage(100, 25, supply_voltage_drop);
            }
            display_watt_hours(45, 0, total_power / Board::Clock::CORE_FREQ / 1000 / 3600);
            // display_time(45, 0, standby_ticks / Board::Clock::CORE_FREQ);
            // display_watts(75, 0, average_request_power_short - average_request_power);
            if (mode == Mode::STANDBY) {
                if ((blink < 4) || (pen_temperature < 20000)) {
                    fb.draw_text(87, 0, "STANDBY", Font::sans8);
                }
            } else {
                display_watts(106, 0, cumulated_power / PERIOD_TICKS / 1000);
                if (standby_ticks > Board::Clock::CORE_FREQ * 4) {
                    fb.draw_text(83, 0, "IDLE", Font::sans8);
                } else if (standby_ticks > Board::Clock::CORE_FREQ * 3) {
                    fb.draw_text(83, 0, "IDL", Font::sans8);
                } else if (standby_ticks > Board::Clock::CORE_FREQ * 2) {
                    fb.draw_text(83, 0, "ID", Font::sans8);
                } else if (standby_ticks > Board::Clock::CORE_FREQ * 1) {
                    fb.draw_text(83, 0, "I", Font::sans8);
                }
            }
        } else if (temp_sensor_status == TempSensorStatus::BROKEN) {
            fb.draw_text(83, 0, "NO RT TIP", Font::sans8);
        } else {
            fb.draw_text(66, 0, "RT TIP ERROR", Font::sans8);
            temperature += pen_temperature;
        }
        display_temperature(48, 10, temperature);

        Board::display.redraw();
        change_state(PeriodState::PID_PROCESS);
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
            change_state(PeriodState::HEATING_START);
            return;
        }
        int request_temperature = preset_temperature[preset_temperature_select];
        if (mode == Mode::STANDBY) {
            request_temperature = STANDBY_TEMPERATURE;
        }
        int request_power = pid.process(cpu_temperature + pen_temperature, request_temperature);
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
        change_state(PeriodState::HEATING_START);
    }

    void heating_start() {
        cumulated_power = 0;
        heat_ticks = 0;
        if ((temp_sensor_status != TempSensorStatus::OK) || (heating_power <= 0)) {
            change_state(PeriodState::IDLE_START);
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
        change_state(PeriodState::HEATING_PROCESS);
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
            change_state(PeriodState::HEATING_END);
            return;
        }
        Board::adc.measure_heat_start();
    }

    void heating_end() {
        cpu_voltage_heat /= heat_measurements_count;
        supply_voltage_heat /= heat_measurements_count;
        supply_voltage_drop = supply_voltage_heat - supply_voltage_idle;
        pen_current /= heat_measurements_count;
        change_state(PeriodState::STABILIZE_START);
    }

    void stabilize_start() {
        stabilize_ticks = 0;
        change_state(PeriodState::STABILIZE_PROCESS);
    }

    void stabilize_process(unsigned delta_ticks) {
        stabilize_ticks += delta_ticks;
        if (stabilize_ticks < STABILIZE_TICKS) return;
        change_state(PeriodState::STABILIZE_END);
    }

    void stabilize_end() {
        change_state(PeriodState::IDLE_START);
    }

    void idle_start() {
        temp_sensor_status = TempSensorStatus::UNKNOWN;
        idle_ticks = 0;
        idle_measurements_count = 0;
        cpu_voltage_idle = 0;
        pen_temperature = 0;
        cpu_temperature = 0;
        supply_voltage_idle = 0;
        Board::adc.measure_idle_start();
        change_state(PeriodState::IDLE_PROCESS);
    }

    void idle_process(unsigned delta_ticks) {
        idle_ticks += delta_ticks;
        if (!Board::adc.measure_is_done()) return;
        cpu_voltage_idle += Board::adc.get_cpu_voltage();
        supply_voltage_idle += Board::adc.get_supply_voltage();
        cpu_temperature += Board::adc.get_cpu_temperature();
        if (Board::adc.is_pen_connected()) {
            if (temp_sensor_status == TempSensorStatus::UNKNOWN) {
                temp_sensor_status = TempSensorStatus::OK;
            }
            pen_temperature += Board::adc.get_pen_temperature();
        } else {
            if (temp_sensor_status != TempSensorStatus::BROKEN) {
                set_standby();
            }
            temp_sensor_status = TempSensorStatus::BROKEN;
        }
        // measurements counter
        idle_measurements_count++;
        if (period_ticks >= PERIOD_TICKS) {
            period_ticks -= PERIOD_TICKS;
            change_state(PeriodState::IDLE_END);
            return;
        }
        Board::adc.measure_idle_start();
    }

    void idle_end() {
        cpu_voltage_idle /= idle_measurements_count;
        supply_voltage_idle /= idle_measurements_count;
        cpu_temperature /= idle_measurements_count;
        pen_temperature /= idle_measurements_count;
        change_state(PeriodState::PERIOD_START);
        if (standby_ticks > STANDBY_TICKS) {
            standby_ticks = STABILIZE_TICKS;
            set_standby();
        } else {
            int derivate_request_power = average_request_power_short - average_request_power;
            if ((derivate_request_power > 150) || derivate_request_power < -200) {
                standby_ticks = 0;
            }
        }
    }

    void process(unsigned delta_ticks) {
        uptime_ticks += delta_ticks;
        period_ticks += delta_ticks;
        standby_ticks += delta_ticks;
        buttons_process_fast(delta_ticks);
        switch (period_state) {
            case PeriodState::PERIOD_START: period_start(); break;
            case PeriodState::DEBUG_PROCESS: debug_process(); break;
            case PeriodState::BUTTONS_PROCESS: buttons_process(); break;
            case PeriodState::DISPLAY_PROCESS: display_process(); break;
            case PeriodState::PID_PROCESS: pid_process(); break;
            case PeriodState::HEATING_START: heating_start(); break;
            case PeriodState::HEATING_PROCESS: heating_process(delta_ticks); break;
            case PeriodState::HEATING_END: heating_end(); break;
            case PeriodState::STABILIZE_START: stabilize_start(); break;
            case PeriodState::STABILIZE_PROCESS: stabilize_process(delta_ticks); break;
            case PeriodState::STABILIZE_END: stabilize_end(); break;
            case PeriodState::IDLE_START: idle_start(); break;
            case PeriodState::IDLE_PROCESS: idle_process(delta_ticks); break;
            case PeriodState::IDLE_END: idle_end(); break;
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
    void run() {
        init_hw();
        io::Nvic::isr_enable();

        Board::display.init();

        pid.set_constants(PID_K_PROPORTIONAL, PID_K_INTEGRAL, PID_K_DERIVATE, 1000 / PERIOD_TIME, HEATING_POWER_MAX);

        Board::debug.dbg << IOStream::endl;
        last_ticks = Board::systick.get_counter();

        change_state(PeriodState::PERIOD_START);

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
