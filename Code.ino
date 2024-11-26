// Blynk Credentials
#define BLYNK_TEMPLATE_ID "TMPL6JUXCBgUY"
#define BLYNK_TEMPLATE_NAME "IoT Based Automated IV Bag"
#define BLYNK_AUTH_TOKEN "1KkzEIK80TfxBaXnwWRCXvx34BgJs6Eq"
#define DHTPIN D1   
#define DHTTYPE DHT11  
#define BUZZER_PIN D5
#define DOUT D2         // HX711 data pin
#define CLK D3  
#define SERVO_PIN D4 

  
#define RED D6
#define YELLOW D7
#define GREEN D8

#include <Servo.h>  
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include "HX711.h"

int i = 0;
int flag = 0;
DHT dht(DHTPIN, DHTTYPE);
#define BLYNK_PRINT Serial

char ssid[] = "Home";         // Your WiFi SSID
char pass[] = "22335577";     // Your WiFi Password


Servo myservo; 
HX711 scale;
float scale_factor; 

void setup() {
  Serial.begin(115200); 
  dht.begin();

  myservo.attach(SERVO_PIN);  // Attach the servo to the defined pin
  myservo.write(180);

  scale.begin(DOUT, CLK);

  pinMode(BUZZER_PIN, OUTPUT);  // Set buzzer pin as output
  digitalWrite(BUZZER_PIN, LOW);  // Turn buzzer off initially

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
    
  Serial.println("Taring scale... Please ensure no weight is on the scale.");
  delay(5000);
  scale.tare();
  Serial.println("Tare complete.");

  float known_weight = 0.510;  // Known calibration weight in kg
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Connecting to Blynk...");
  Blynk.logEvent("warning", "Place the known weight on the scale.");
  Serial.println("Place the known weight on the scale.");
 
  delay(5000);  // Wait for user to place weight
  long reading_with_weight = scale.read_average(10);
  long reading_without_weight = scale.get_offset();
  scale_factor = (float)(reading_with_weight - reading_without_weight) / known_weight;
  scale.set_scale(scale_factor);
  Serial.print("Scale factor: ");
  Serial.println(scale_factor);

}

void beep() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);  // Beep for 200 ms
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  Blynk.run();  // Run Blynk

  float weight_kg = scale.get_units(10) - 0.01;  // Adjust for offset
  Serial.print("Weight: ");
  Serial.print(weight_kg);
  Serial.println(" kg");
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();


    // Check if the DHT sensor is working correctly
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

    if(weight_kg >= 0.1){
      i = 0;
    }

    // Buzzer alerts
  if (weight_kg >= 0.05 && weight_kg <= 0.06) {  
      // IV bag is almost empty
      Blynk.logEvent("warning", "IV bag is Almost Empty");
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, HIGH);
      beep();
      digitalWrite(YELLOW, LOW);
  } 
  else if (weight_kg <= 0.02) {    

      // IV bag is empty
      for(; i <=2; i++ ){
        digitalWrite(YELLOW, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(RED, HIGH);
        beep();
        digitalWrite(RED, LOW);
        Blynk.logEvent("warning", "IV bag is Empty");
        myservo.write(0);    // Move the servo to 90 degrees
        delay(500);          // Wait for 1 second
        myservo.write(180);     // Move the servo back to 0 degrees
        delay(500);  
      }

      Blynk.logEvent("warning", "Please remove the cannula from the patient.");
  } 
  else {
      digitalWrite(YELLOW, LOW);
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
  }

  if(temperature >= 30 || temperature <= 16 || weight_kg <= 0.02){
        digitalWrite(YELLOW, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(RED, HIGH);
        delay(500);
        digitalWrite(RED, LOW);
  }



  // Print temperature and humidity to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity); 
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Send temperature and humidity to Blynk virtual pins
  Blynk.virtualWrite(V0, temperature);  // Virtual Pin V0 for temperature
  Blynk.virtualWrite(V1, humidity);    // Virtual Pin V1 for humidity
  Blynk.virtualWrite(V2, weight_kg);
  // Send notification if temperature exceeds 32°C
  if (temperature >= 30) {
    Serial.println("Temperature exceeds 32°C. Buzzer should beep.");
    Blynk.logEvent("warning", "Temperature is above comfort level.");
    beep();
  }else if(temperature <= 16){
    Serial.println("Temperature extremely low. Buzzer should beep.");
    Blynk.logEvent("warning", "Temperature is below comfort level.");
    beep();
  } 
  delay(1000);  // Delay before next reading
}
