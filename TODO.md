### SW:
- ~~control display brightness~~
- ~~turn off display after long inactivity~~
- detect broken current sensor
- not fully inserted tip protection
- use current sensor magnetometer to enter sleep mode (magnet near the current sensor will enlarge offset error)
- use thermocouple type D curve to calculate tip temperature (it increases temperature measuring accuracy)
- standby should not blink if raw tip temperature is less than 10°C although tip temperature is higher than WARN_HOT_TIP_TEMP (50°C)
- overheating detection by temperature sensor
- in Fahrenheits mode increment by 5°F and round current temperature to 5°F
- I2C Read support
  - use temperature sensor in accelerometer instead sensor in CPU (HW v1.0)
  - use accelerometer to WAKE-UP (HW v1.0)
  - use accelerometer to detect free fall to turn OFF (HW v1.0)
- menu settings allow edit values
  - move PID and other constants to settings menu
  - configure maximum power output
- create screen "INFO" and move all information values there
- tool to tune PID regulation
- improve IDLE detection
- room to improve PID
- under voltage for LiPO protection
- screen saver ?

### HW:
- fix wrong connection to current sensor
