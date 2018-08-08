#pragma once

// #include <cmath>
#include "minmax.hpp"

namespace lib {

class Pid {
    int _kp = 0;
    int _ki = 0;
    int _kd = 0;
    int _period_ms = 0;
    int _limit_mw = 0;
    int _error_i_limit = 0;

    int _error = 0;
    int _error_i = 0;
    int _error_d = 0;
    int _error_last = 0;

    int _request_p = 0;
    int _request_i = 0;
    int _request_d = 0;

    void _derivate() {
        _error_d = (_error - _error_last) * 1000 / _period_ms;
    }

    static const int INTEGRATION_ENABLED_ERROR_D_MIN = -15000;
    static const int INTEGRATION_ENABLED_ERROR_D_MAX = 100000;

    void _integrate() {
        // MOD: integration is enabled only if error_d is in interval
        if (interval(
            _error_d,
            INTEGRATION_ENABLED_ERROR_D_MIN,
            INTEGRATION_ENABLED_ERROR_D_MAX)
        ) {
            _error_i += _error * _period_ms / 1000;
            // MOD: limit I: 0 <-> max power
            minmax(&_error_i, 0, _error_i_limit);
        } else if (_error < 0) {
            // MOD: if temperature still rising and is over, then zero _error_i
            _error_i = 0;
        }
    }

    int _calculate_proportional() const {
        return _error * _kp / 1000;
    }

    int _calculate_integral() const {
        return _error_i * _ki / 1000;
    }

    int _calculate_derivate() const {
        return _error_d * _kd / 1000;
    }

public:
    void set_constants(const int kp, const int ki, const int kd, const int period_ms, const int limit_mw) {
        _kp = kp;
        _ki = ki;
        _kd = kd;
        _period_ms = period_ms;
        _limit_mw = limit_mw;
        if (_ki > 0) {
            _error_i_limit = limit_mw * 1000 / _ki;
        } else {
            _error_i_limit = 0;
        }
        reset();
    }

    void reset() {
        _error = 0;
        _error_i = 0;
        _error_d = 0;
        _error_last = 0;
        _request_p = 0;
        _request_i = 0;
        _request_d = 0;
    }

    int process(const int feedback, const int set_point) {
        _error = set_point - feedback;

        _derivate();
        _integrate();

        _request_p = _calculate_proportional();
        _request_d = _calculate_derivate();
        _request_i = _calculate_integral();

        // store last value
        _error_last = _error;

        int request_power = _request_p + _request_i + _request_d;
        // limit requested power
        return minmax(request_power, 10, _limit_mw);
    }

    // for debugging purposes
    int get_request_p() const {
        return _request_p;
    }

    int get_request_i() const {
        return _request_i;
    }

    int get_request_d() const {
        return _request_d;
    }

    int get_error() const {
        return _error;
    }

    int get_error_i() const {
        return _error_i;
    }

    int get_error_d() const {
        return _error_d;
    }

};

}
