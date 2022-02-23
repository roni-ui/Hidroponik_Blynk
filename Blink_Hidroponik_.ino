// #define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// #include <SimpleTimer.h>
#include <DHT.h>

//Lux Sensor
#include <Wire.h>
#include <BH1750.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "iBPq8xOwOiK6dQ6yABHysMevuVnVMx_N"; //Enter the Auth code which was send by Blink

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Useless";  //Enter your WIFI Name
char pass[] = "tahundepanjadibos2";  //Enter your WIFI Password

#define DHTPIN 2          // Digital pin 4

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

//Lux Sensor
BH1750 lightMeter;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(true); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  //Lux Sensor
  Wire.begin();
  lightMeter.begin();
  

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  // Serial.print("Humidity: "); 
  // Serial.print(h);
  // Serial.print(" %\t");
  // Serial.print("Temperature: "); 
  // Serial.print(t);
  // Serial.println(" *C");

  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer

  //lux Sensor
  float lux = lightMeter.readLightLevel();
  Serial.print("Light Meter: ");
  Serial.print(lux);
  Serial.println(" lx");
  Blynk.virtualWrite(V2, lux);
  delay(1000);
}
