#pragma once

#include "board/gpio.hpp"

namespace board {

class HwId {
 public:
    enum class HwRevision : unsigned {
        HW_0X,
        HW_1X,
        UNKNOWN,
    };

    void init_hw() {
        GpioPin<io::base::GPIOB, 1> hw_id1;
        hw_id1.configure_input().configure_pull(gpio::Pull::PULL_UP);
        if (hw_id1.get_input()) {
            _hw_revision = HwRevision::HW_0X;
        } else {
            _hw_revision = HwRevision::HW_1X;
        }
        hw_id1.configure_pull(gpio::Pull::OFF);
    }

    HwRevision get_hw_revision() {
        return _hw_revision;
    }

    static HwId &get_instance() {
        static HwId instance;
        return instance;
    }

 private:
    HwRevision _hw_revision = HwRevision::UNKNOWN;
};

}  // namespace board
