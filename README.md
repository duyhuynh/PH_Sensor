# Arduino DTH_PH_Sensor library
DTH_PH_Sensor is a library that provides functions to measure pH of water for Arduino.
## Functionality
The functions available in the library include
```c
begin(sensorPin, powerPin)	// start pH sensor with sensor pin number and power pin number.
readPH()			// read pH.
getVoltage()		// read the voltage from the pH sensor.
setSampe(sample)()	// Set the sample number to read the voltage from the pH sensor.
setPH4AcidVolt(volt)	// set reference voltage for pH 4
setPH7NeutralVolt(volt)	//set reference voltage for pH 7
setPH10BasicVolt(volt)	//set reference voltage for pH 10
```
## Examples
The DTH_PH_Sensor directory contains the DTH_PH_Sensor library and a example sketche
illustrating how to use the library:
- `read_pH.ino`- example of using pH library.  
