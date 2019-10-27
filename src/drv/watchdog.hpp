#pragma once

#include "io/reg/stm32/f0/iwdg.hpp"

namespace drv {

class Watchdog {
    static const unsigned WATCHDOG_FREQUENCY = 40000;  // Hz
    // DIVIDER  min_time  max_time
    // DIV_4    0.1 ms    409.6 ms
    // DIV_256  6.4 ms    26.2144 s

 public:
    static void enable(const unsigned time_ms, const unsigned window_time_ms) {
        unsigned prediv = io::Iwdg::Pr::Pre::DIV_4;
        unsigned reload = time_ms * WATCHDOG_FREQUENCY / 1000;
        unsigned window = window_time_ms * WATCHDOG_FREQUENCY / 1000;
        reload /= static_cast<unsigned>(1 << (prediv + 2));
        window /= static_cast<unsigned>(1 << (prediv + 2));
        while (reload > io::Iwdg::Rlr::Rl::MAX) {
            prediv++;
            reload >>= 1;
            window >>= 1;
        }
        io::IWDG.KR.KEY = io::Iwdg::Kr::START;
        io::IWDG.KR.KEY = io::Iwdg::Kr::WRITE_ACCESS;
        io::IWDG.PR.PRE = prediv;
        io::IWDG.RLR.RL = reload;
        while (io::IWDG.SR.r);
        io::IWDG.WINR.WIN = window;
    }

    static void refresh() {
        io::IWDG.KR.KEY = io::Iwdg::Kr::REFRESH;
    }
};

}  // namespace drv
