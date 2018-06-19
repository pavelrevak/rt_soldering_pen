#pragma once

namespace lib {

struct IoPin {
    virtual void clr() = 0;
    virtual void set() = 0;
    virtual void set(const bool) = 0;
    virtual void toggle() = 0;
    virtual bool get() const = 0;
    virtual bool get_input() const = 0;
};

}
