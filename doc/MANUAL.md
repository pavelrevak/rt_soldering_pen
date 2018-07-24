# RT soldering pen MANUAL

## Buttons

RT soldering pen has only two buttons: **UP** and **DOWN**. Firmware recognize different pressing states and combinations.

### Pressing states

- **PRESS** press button shortly (shorter than 1 sec) after release will be generated action
- **LONG** hold button longer than 1 sec, after 1 sec will be generated action "long"
- **HOLD** hold button and after 1 sec will be generated repeat actions

### Pressing combinations

- **UP** press, long, hold
- **DOWN** press, long, hold
- **BOTH** press, long

### General operating principles:

##### **PRESS** **UP** or **DOWN**:

- select appropriate value (preset temperatures on main screen)
- scroll content on screen
- increase or decrease value

##### **LONG** **UP** or **DOWN**:

- enter edit mode of appropriate value (preset temperatures on main screen)

##### **HOLD** **UP** or **DOWN**:

(autorepeat)

- scroll content on screen
- increase or decrease value

##### **PRESS** **BOTH**:

- STOP heating
- exit menu screen

##### **LONG** **BOTH**:

- enter menu screen
- change item in menu

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

##### Entering edit mode:

**LONG** press **UP** or **DOWN** button of the appropriate preset temperature.

##### Changing the edited preset temperature:

**UP** or **DOWN** button.

##### Exiting edit preset value:

**PRESS** **BOTH** buttons.

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

**Exiting main screen:**

-  **PRESS** **BOTH** buttons

*This also save settings*

[oled1]: oled1.png "Screenshot"
[oled2]: oled2.png "Screenshot"
[oled3]: oled3.png "Screenshot"
[oled4]: oled4.png "Screenshot"
[oled5]: oled5.png "Screenshot"
[oled6]: oled6.png "Screenshot"
[oled7]: oled7.png "Screenshot"
[oled8]: oled8.png "Screenshot"
