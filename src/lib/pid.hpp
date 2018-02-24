#pragma once

#include "board/debug.hpp"

class Pid {
    int k_p = 0;
    int k_i = 0;
    int k_d = 0;
    int dt = 0;  // measurements per second
    int request_limit = 0;
    int error_i_limit = 0;

    int error_p_last = 0;
    int error_i = 0;

public:
    void set_constants(const int p, const int i, const int d, const int t, const int l) {
        k_p = p;
        k_i = i;
        k_d = d;
        dt = t;
        request_limit = l;
        error_i_limit = l * 1000 / k_i;
    }

    void reset() {
        error_i = 0;
        error_p_last = 0;
    }

    int process(const int feedback, const int set_point) {
        // proportional
        int error_p = set_point - feedback;
        int request_p = error_p * k_p / 1000;
        // integral
        int request_i = 0;
        if (request_p > request_limit) {
            // disable if process is for 100% controlled by P
            error_i = 0;
        } else {
            error_i += error_p / dt;
            if (error_i > error_i_limit) error_i = error_i_limit;
            if (error_i > 0) {
                request_i = error_i * k_i / 1000;
            } else {
                error_i = 0;
            }
        }
        // derivate
        int error_d = error_p - error_p_last;
        error_d *= dt;
        int request_d = error_d * k_d / 1000;
        if ((request_d > - 1000) && (request_d < 1000)) request_d = 0;
        // requested power in mW
        int request_power = request_p + request_i + request_d;
        if (request_power > request_limit) request_power = request_limit;
        if (request_power < 0) request_power = 0;

        // debug output
        Board::debug.dbg << feedback;
        Board::debug.dbg << '\t' << set_point;
        Board::debug.dbg << '\t' << request_power;
        Board::debug.dbg << '\t' << request_p;
        Board::debug.dbg << '\t' << request_i;
        Board::debug.dbg << '\t' << request_d;
        Board::debug.dbg << IOStream::endl;

        error_p_last = error_p;
        return request_power;
    }

};
