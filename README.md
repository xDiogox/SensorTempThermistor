# SensorTempThermistor

Temperature sensor working with NodeeMcu and MQTT.

Temperature sensor made with a 10k Thermistor , NodeMcu sends temperature values via MQTT to Home Assistant.





## Circuit
<br>

![GitHub Logo](https://github.com/xDiogox/SensorTempThermistor/blob/master/Images/Setup.png)

<br>
 Thermistor is connected to 3.3V and a 10k resistor , NodeMcu ADC read the value and the code inside the board convert the ADC value into a temperature value.


 NodeMcu send the temperature value via MQTT to Home Assistant.

 D0 and Reset pin are connected together because of ESP.deepsleep(1500000000). 

 D0 after 25 minutes will send a LOW sinal to Reset pin , when the reset pin recieves a LOW sinal NodeMcu board will wake up and start the code.

<h1>


