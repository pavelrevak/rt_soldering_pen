# RT soldering pen MANUAL

## Buttons

RT soldering pen has only two buttons: *UP* and *DOWN*. Firmware recognize different pressing states and combinations.

### Pressing states

- *PRESS* press button shortly (shorter than 1 sec) after release will be generated action
- *LONG* hold button longer than 1 sec, after 1 sec will be generated action "long"
- *HOLD* hold button and after 1 sec will be generated repeat actions

### Pressing combinations

- *UP* press, long, hold
- *DOWN* press, long, hold
- *BOTH* press, long

### General operating principles:

##### *PRESS* *UP* or *DOWN*:

- select appropriate value (preset temperatures on main screen)
- scroll content on screen
- increase or decrease value

##### *LONG* *UP* or *DOWN*:

- enter edit mode of appropriate value (preset temperatures on main screen)

##### *HOLD* *UP* or *DOWN*:

(autorepeat)

- scroll content on screen
- increase or decrease value

##### *PRESS* *BOTH*:

- STOP heating
- go back from info screen (current implementation)
- select item in menu (planed implementation)

##### *LONG* *BOTH*:

- enter info screen (current implementation)
- enter menu (planed implementation)

## Screens

Actually there are two screens.

### Main screen

Show basic information:

- preset temperatures
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

#### Editing preset temperatures

On *Main screen* are two (up and down) preset values, which you can easily change.
Editing is visible by blinking appropriate preset value.

##### Entering edit mode:

*LONG* press *UP* or *DOWN* button of the appropriate preset temperature.

##### Changing the edited preset temperature:

*UP* or *DOWN* button.

##### Exiting edit preset value:

*PRESS* *BOTH* buttons.

### Info screen

This screen is actually in development status and their function will change in future.
Actually it show some basic measured information

##### Entering info screen:

in main screen *LONG* press of *BOTH* buttons

##### Scrolling info screen:

*UP* or *DOWN* button

##### Exiting info screen:

*PRESS* *BOTH* buttons
