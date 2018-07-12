"""Script for testing buttons on real HW without LCD using SWD programmer: ST-Link"""

import time
import swd

def main():
    """Main func"""
    dev = swd.Swd()
    button_up_last = None
    button_dw_last = None
    while True:
        try:
            gpiob_inputs = dev.get_mem32(0x48000410)
            button_up = not bool(gpiob_inputs & (1 << 5))
            button_dw = not bool(gpiob_inputs & (1 << 4))
            if button_up != button_up_last or button_dw != button_dw_last:
                button_up_last = button_up
                button_dw_last = button_dw
                print("up: %d  dw: %d" % (button_up, button_dw))
            time.sleep(.1)
        except KeyboardInterrupt:
            print()
            break

if __name__ == "__main__":
    main()
