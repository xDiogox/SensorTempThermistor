# SensorTempThermistor

Temperature sensor working with NodeeMcu and MQTT.

Temperature sensor made with a 10k Thermistor , NodeMcu sends temperature values via MQTT to Home Assistant.





# Circuit <h1> 
![GitHub Logo](https://github.com/xDiogox/SensorTempThermistor/blob/master/Images/Setup.png)
  
Thermistor is connected to 3.3V and a 10k resistor , NodeMcu ADC read the value and the code inside the board convert the ADC value into a temperature value.

D0 and Reset pin are connected together because of ESP.deepsleep(1500000000). 

ESP board will wake up after 25 minutes and start the code again.




