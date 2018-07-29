# RT soldering pen MANUAL

## Specs

- Supported pens: all Weller RT tips with 3.5mm JACK.
- Supply voltage: 5 - 18V (recommended: 7 - 16V)
- Supply current: pulse peaks to 6A @12V (average resistance of RT heating elements is 2 Ohm, so current depends on supply voltage)
- Supply current in idle: max 15mA
- Regulation: PSD (PID) regulator with PWM power transfer (150ms period)
- Set-point temperature: 20°C - 400°C
- Maximum measurable tip temperature: 530°C + ambient temperature
- Maximum heating power: is limited by SW to 40W or by supply voltage: 40W @11V, 20W @8V
- Heating speed: 30°C -> 300°C: about 4s with RT-2 pen and 40W limit
- Temperature accuracy: about +/-5°C (calibration is planed)
- Other features: Celsius / Fahrenheit, right / left handed mode, normal / advanced mode display
- FW updating: by any SWD programmer (ST-Link) [actual firmware](https://github.com/pavelrevak/rt_soldering_pen/releases), firmware is still under active development.

## Powering

- supply pins are marked with GND or BLACK wire as negative pole and +12V or RED wire as positive pole.

### WARNING

**Be careful with connecting supply and always check it before turning ON!**

Although controller is protected for reverse voltage by diode, power part is not protected. **If is connected RT tip, with reversed voltage then will heat on maximum power and also MOSFET transistor will overheat.**

Also similar problem can happened **if RT tip is not fully inserted and then someone turn ON heating.** Protection for this will be fixed by SW in next release.

Do not solder something under voltage if is powered from same supply, because RT tip is connected with GND. (for example inside car when pen is powered from lighter connector, or some AC power supplies where is negative pole connected to ground conductor).

### Supply from AC power supply

Switching power supplies must be able to withstand high current pulses (12V/6A). These supplies has almost always connected negative pole with protective conductor.

Or you can use Transformer with good capacity and these supplies don't have connected minus pole to ground conductor.

### Supply from battery

Best batteries for supply RT soldering pen are hobbyist LIPO 3S, 4S or 2S (but not full output power) with capacity at least 1Ah (with continuous discharge current at least 5A).

From my practice 2.2Ah 3S LIPO battery can last for about 5 to 10 hours of soldering.

Also is possible to use small 3S LIPO battery about 0.5Ah / 20C and this battery will be continuously charged with small charger (about 0.5A charging current) - this battery will work as capacitor with very high capacity. and also is possible to work for some time without AC supply.

## Buttons

RT soldering pen has only two buttons: **UP** and **DOWN**. Firmware recognize different pressing states and combinations.

### Pressing states

- **PRESS** press button shortly (shorter than 1 sec) after release will be generated action
- **LONG** hold button longer than 1 sec, after 1 sec will be generated action "long"
- **HOLD** hold button and after 1 sec will be generated repeat actions

### General operating principles:

|           | **UP**                   | **DOWN**                 | **BOTH**                |
|-----------|--------------------------|--------------------------|-------------------------|
| **PRESS** | select, increase, scroll | select, decrease, scroll | heating off, exit menu  |
| **HOLD**  | edit                     | edit                     | enter menu, change item |
| **LONG**  | scroll, increase         | scroll, decrease         | -                       |

## Screens

Actually there are two screens.

### Main screen

#### Normal mode

![oled6]

Show very basic information

- preset temperatures and selected preset (with arrow)
- actual TIP temperature (if no TIP is attached, CPU temperature is shown)
- bar-graph - actual heating power.

#### Advanced mode

![oled3]

Show some verbose information:

- preset temperatures and selected preset (with arrow)
- actual TIP temperature (if no TIP is attached, CPU temperature is shown)
- consumed energy (this is restarted with power cycle)
- status
  - `NO RT TIP` - RT TIP is not attached (or TIP has broken temperature sensor)
  - `STANDBY` - standby mode (no heating), if blink: temperature is over 50°C
  - `IDLE` -  if during heating is not detected any work, after 5 sec is shown this message and after 30 sec is set standby mode
  - `BROKEN RT TIP!` - TIP has broken heating element (heating element resistance is more than 100 Ohm)
  - `SHORTED RT TIP!` - TIP has shorted heating element (heating element resistance is lower than 0.5 Ohm)
- actual heating power
- supply voltage
- supply voltage drop - show dropped voltage of power supply during heating, generally it depend on power supply resistance and resistance of wires

![oled1]
![oled2]
![oled4]

#### Left handed mode

Display is upside down, also with some rearrangements.

![oled7]
![oled8]

#### Editing preset temperatures

On **Main screen** are two (up and down) preset values, which you can easily change.
Editing is visible by blinking appropriate preset value.

**Entering edit mode:**

- **LONG** press **UP** or **DOWN** button of the appropriate preset temperature.

**Changing the edited preset temperature:**

- **UP** or **DOWN** button.

**Exiting edit preset value:**

- **PRESS** **BOTH** buttons.

### Menu screen

![oled5]
![oled9]

This screen show simple menu with:

- version information
- basic settings:
  - Advanced mode
  - Fahrenheit
  - Left handed
- some verbose information:
  - Total power
  - Heater power
  - Heater current
  - Heater resistance
  - CPU temperature
  - CPU supply
  - Current sensor error

**Entering menu screen:**

- in main screen **LONG** press of **BOTH** buttons

**Scrolling main screen**

-  **UP** or **DOWN** button

**Changing ON/OFF values:**

-  **LONG** press of **BOTH** buttons

**Exiting menu screen:**

-  **PRESS** **BOTH** buttons

*Exiting menu screen also store settings*

[oled1]: oled1.png "Screenshot"
[oled2]: oled2.png "Screenshot"
[oled3]: oled3.png "Screenshot"
[oled4]: oled4.png "Screenshot"
[oled5]: oled5.png "Screenshot"
[oled6]: oled6.png "Screenshot"
[oled7]: oled7.png "Screenshot"
[oled8]: oled8.png "Screenshot"
[oled9]: oled9.png "Screenshot"
