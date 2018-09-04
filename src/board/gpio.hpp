#pragma once

#include <cstddef>
#include "io/reg/stm32/f0/gpio.hpp"
#include "lib/iopin.hpp"

namespace board {

namespace gpio {

enum class Pull {
    OFF = io::Gpio::Pupdr::Pupd::OFF,
    PULL_UP = io::Gpio::Pupdr::Pupd::PULL_UP,
    PULL_DOWN = io::Gpio::Pupdr::Pupd::PULL_DOWN,
};

enum class Otype {
    PUSH_PULL = io::Gpio::Otyper::Otype::PUSH_PULL,
    OPEN_DRAIN = io::Gpio::Otyper::Otype::OPEN_DRAIN,
};

enum class Ospeed {
    LOW = io::Gpio::Ospeedr::Ospeed::LOW,
    MEDIUM = io::Gpio::Ospeedr::Ospeed::MEDIUM,
    FAST = io::Gpio::Ospeedr::Ospeed::FAST,
    HIGH = io::Gpio::Ospeedr::Ospeed::HIGH,
};

}

/**
 * @class GpioPin
 * @details template version access to GPIO pins
 *
 * @tparam Base address of GPIO port
 * @tparam Pin number of pin on GPIO port
 */
template <size_t Base, unsigned Pin>
class GpioPin : public lib::IoPin {

    io::Gpio &r_gpio = io::GPIO(Base);

public:
    /**
     * @brief Configure GPIO pin to analog mode
     *
     * @return reference to this instance
     */
    inline GpioPin &configure_analog() {
        r_gpio.MODER.set(Pin, io::Gpio::Moder::Mode::ANALOG);
        return *this;
    }

    /**
     * @brief Configure GPIO pin to input mode
     *
     * @return reference to this instance
     */
    inline GpioPin &configure_input() {
        r_gpio.MODER.set(Pin, io::Gpio::Moder::Mode::INPUT);
        return *this;
    }

    /**
     * @brief Configure GPIO pin to output mode
     *
     * @return reference to this instance
     */
    inline GpioPin &configure_output() {
        r_gpio.MODER.set(Pin, io::Gpio::Moder::Mode::OUTPUT);
        return *this;
    }

    /**
     * @brief Configure GPIO pin to output mode
     *
     * @param val value to set before setting output mode
     * @return reference to this instance
     */
    inline GpioPin &configure_output(const bool val) {
        set(val);
        configure_output();
        return *this;
    }

    /**
     * @brief Configure GPIO pin to alternate function
     *
     * @param alternate function number
     * @return reference to this instance
     */
    inline GpioPin &configure_af(const unsigned int af) {
        r_gpio.MODER.set(Pin, io::Gpio::Moder::Mode::AF);
        r_gpio.AFR.set(Pin, af);
        return *this;
    }

    /**
     * @brief Configure GPIO pin pull resistors
     *
     * @param val pull resistor state:
     *          - gpio::Pull::FLOAT
     *          - gpio::Pull::PULL_UP
     *          - gpio::Pull::PULL_DOWN
     * @return reference to this instance
     */
    inline GpioPin &configure_pull(const gpio::Pull pull=gpio::Pull::OFF) {
        r_gpio.PUPDR.set(Pin, static_cast<uint32_t>(pull));
        return *this;
    }

    /**
     * @brief Configure GPIO pin output driver mode
     *
     * @param val pull resistor state:
     *          - gpio::Otype::PUSH_PULL
     *          - gpio::Otype::OPEN_DRAIN
     * @return reference to this instance
     */
    inline GpioPin &configure_otype(const gpio::Otype otype=gpio::Otype::PUSH_PULL) {
        r_gpio.OTYPER.set(Pin, static_cast<uint32_t>(otype));
        return *this;
    }

    /**
     * @brief Configure GPIO pin output driver speed
     *
     * @param val pull resistor state:
     *          - gpio::Ospeed::LOW
     *          - gpio::Ospeed::MEDIUM
     *          - gpio::Ospeed::FAST
     *          - gpio::Ospeed::HIGH
     * @return reference to this instance
     */
    inline GpioPin &configure_ospeed(const gpio::Ospeed ospeed=gpio::Ospeed::MEDIUM) {
        r_gpio.OSPEEDR.set(Pin, static_cast<uint32_t>(ospeed));
        return *this;
    }

    /**
     * @brief Clear output (set to low)
     */
    inline void clr() override {
        r_gpio.BSRR.clr(Pin);
    }

    /**
     * @brief Set output (set to high)
     */
    inline void set() override {
        r_gpio.BSRR.set(Pin);
    }

    /**
     * @brief Set output (set to value)
     */
    inline void set(const bool val) override {
        if (val) r_gpio.BSRR.set(Pin);
        else r_gpio.BSRR.clr(Pin);
    }

    /**
     * @brief Toggle output (invert)
     */
    inline void toggle() override {
        set(!get());
    }

    /**
     * @brief Get output
     *
     * @return output value
     */
    inline bool get() const override {
        return r_gpio.ODR.get(Pin);
    }

    /**
     * @brief Get input value
     *
     * @return input value
     */
    inline bool get_input() const override {
        return r_gpio.IDR.get(Pin);
    }
};

}
