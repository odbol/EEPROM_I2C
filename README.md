EEPROM_I2C
==========

Simple EEPROM I2C library for using external EEPROMS with Arduino Due, like the 24LC series.

This library is actually stolen from the Robot_Control library included in the Arduino source, with these improvements:
    
* Removed hardcoded address, made work for any address.
* Added test sketch, with page read/write test.

NOTE: This requires some fixes to the Wire library included in Arduino. See https://github.com/arduino/Arduino/pull/1994 for details.
