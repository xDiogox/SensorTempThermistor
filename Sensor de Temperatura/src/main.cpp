#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <math.h>


const char* ssid = "****";
const char* password = "****";
const char* mqtt_server = "****";

WiFiClient espClient;
PubSubClient client(espClient);


//Variaveis Sensor ------------------------------

const double VCC = 3.3;             // NodeMCU on board 3.3v vcc
const double R2 = 10000;            // 10k ohm series resistor
const double adc_resolution = 1023; // 10-bit adc

const double A = 0.001129148;   // thermistor equation parameters
const double B = 0.000234125;
const double C = 0.0000000876741; 


//----------------------------------------------------



void setup_wifi() 
{

  delay(10);

  Serial.println();
  Serial.print("A conectar a  ");
  Serial.println(ssid);

  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("WiFi connected : ");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("ESP Temp" , "testemqtt","1234"))
    {
      Serial.println("Conexão Efetuada ao MQTT");
      // Once connected, publish an announcement...
      client.publish("sensor/ligar", "Ligado");
    } 
    else 
    {
      Serial.println("\nFalha na comunicação");
      Serial.println("Tentativa de conexão em 5 segundos\n");
      
      delay(5000);
    }
  }
}

void setup() 
{
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
}

double LerADC()
{
    double soma=0;

    for (int i = 0; i < 20; i++)
    {
      soma += analogRead(A0);
      delay(100);
    }
    
    return (soma/20.0);

}

double LerTemperatura()
{


  double Vout, Rth, temperature, adc_value; 

  adc_value = LerADC();
  Vout = (adc_value * VCC) / adc_resolution;
  Rth = (VCC * R2 / Vout) - R2;


  temperature = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)),3))));   // Temperature in kelvin

  temperature = temperature - 273.15;  // Temperature in degree celsius


  Serial.print("Temperatura : ") ;
  Serial.println(temperature); 

  return temperature;
}



void loop() 
{
   if (!client.connected()) 
   {
      reconnect();
   }

    client.loop();

    client.publish("****" , String(LerTemperatura(),1).c_str(),true);

    delay(1000);

    ESP.deepSleep(1500000000);
}




