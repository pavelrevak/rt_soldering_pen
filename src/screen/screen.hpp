#pragma once

namespace screen {

class Screen;

enum class ScreenId {
    MAIN,
    MENU,
    COUNT,
};

class ScreenHolder {
    ScreenId _screen_id = ScreenId::MAIN;
    Screen **_screens_list_ptr;

 public:
    ScreenHolder(Screen **screens_list_ptr) :
        _screens_list_ptr(screens_list_ptr) {}

    void set(ScreenId id) {
        _screen_id = id;
    }

    Screen *get() {
        return _screens_list_ptr[static_cast<int>(_screen_id)];
    }
};

class Screen {
    board::Display::Fb &fb = board::display.get_fb();

    ScreenHolder &_screen_holder;

 protected:
    void change_screen(ScreenId id) {
        _screen_holder.set(id);
    }

 public:
    Screen(ScreenHolder &screen_holder) : _screen_holder(screen_holder) {}

    virtual bool button_up(const lib::Button::Action) { return false; }
    virtual bool button_dw(const lib::Button::Action) { return false; }
    virtual bool button_both(const lib::Button::Action) { return false; }
    virtual void draw() = 0;
};
}  // namespace screen
