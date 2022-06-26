#include "DHT.h"        
#define dhtPin 12   
#define dhtType DHT11   



DHT dht(dhtPin, dhtType);  
float humidityVal;           // humidity
float tempValC;              // temperature in degrees Celcius
float tempValF;              // temperature in degrees Fahrenheit
float heatIndexC;            // windchill in degrees Celcius
float heatIndexF;            // windchill in degrees Fahrenheit

int Moisture_signal = A0; //Define the Analog pin# on the Arduino for the soil moisture sensor signal
 
void setup() {
  Serial.begin(9600); // Start the serial communication
  dht.begin();  
}
 
void loop() {
  int Moisture = analogRead(Moisture_signal);
  humidityVal = dht.readHumidity();        // get the humidity from the DHT sensor
  tempValC = dht.readTemperature();        // get the temperature in degrees Celcius from the DHT sensor
  tempValF = dht.readTemperature(true); 


  if (isnan(humidityVal) || isnan(tempValC) || isnan(tempValF)) {
    Serial.println("Reading DHT sensor failed!");
    return;
  }

  heatIndexC = dht.computeHeatIndex(tempValC, humidityVal, false);
  heatIndexF = dht.computeHeatIndex(tempValF, humidityVal);

  Serial.print("Humidity: ");
  Serial.print(humidityVal);
  Serial.print(" %\t");

  Serial.print("Temperature: ");
  Serial.print(tempValC);
  Serial.print(" °C ");
  Serial.print(tempValF);
  Serial.println(" °F\t");

  Serial.print("Windchill: ");
  Serial.print(heatIndexC);
  Serial.print(" °C ");
  Serial.print(heatIndexF);
  Serial.println(" °F");

  
  Serial.print("Soil Moisture Level: ");
  Serial.println(Moisture);
  Serial.println();
  delay(2000);
}
