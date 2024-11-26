# **IoT-Based Automated IV Bag Monitoring System**

This repository contains the code and documentation for an **IoT-Based Automated IV Bag Monitoring System**. The system is designed to enhance patient care by automating IV fluid monitoring and providing real-time alerts for critical conditions. It integrates sensors, actuators, and the Blynk IoT platform to notify caregivers promptly, ensuring timely intervention and efficient healthcare management.

---

## **Features**
- **Real-Time IV Bag Monitoring**: Continuously measures the IV bag weight using an HX711 load cell.
- **Room Environment Monitoring**: Tracks temperature and humidity using a DHT11 sensor.
- **Automated IV Tube Control**: Employs a servo motor to stop IV fluid flow when the bag is empty.
- **Visual and Audio Alerts**: Provides alerts using LEDs and a buzzer for critical conditions.
- **IoT Integration**: Sends real-time notifications to caregivers via the Blynk IoT platform.
- **Threshold Alerts**:
  - Weight thresholds: Normal, Almost Empty, Empty.
  - Temperature thresholds: High (>32°C) and Low (<16°C).

---

## **Hardware Requirements**
1. **Microcontroller**: NodeMCU ESP8266  
2. **Sensors**:
   - HX711 Load Cell (weight measurement)
   - DHT11 (temperature and humidity measurement)  
3. **Actuators**:
   - Servo motor (automated IV tube control)
   - Buzzer (audio alerts)
   - LEDs (visual alerts: Green, Yellow, Red)  
4. **Power Supply**: 3.3V/5V power source  
5. **Additional Components**:
   - Breadboard and jumper wires
   - Resistors (for LEDs)

---

## **Software Requirements**
- **Arduino IDE**: For writing and uploading the code.
- **Blynk IoT Platform**: For real-time notifications and remote monitoring.
- **Libraries**:
  - `Servo.h`: For controlling the servo motor.
  - `DHT.h`: For reading DHT11 sensor data.
  - `HX711.h`: For interfacing with the load cell.
  - `BlynkSimpleEsp8266.h`: For connecting the ESP8266 to the Blynk IoT platform.

---

## **Pin Connections**
| Component           | Pin (ESP8266) |
|----------------------|---------------|
| HX711 Load Cell      | D2 (DT), D3 (CLK) |
| DHT11 Sensor         | D1 (DATA) |
| Buzzer               | D5 |
| Red LED              | D6 |
| Yellow LED           | D7 |
| Green LED            | D8 |
| Servo Motor          | D4 |

---

## **Installation Steps**
1. **Hardware Setup**:
   - Connect the sensors and actuators to the NodeMCU ESP8266 as per the pin connections table.
   - Power the NodeMCU with a suitable power supply.

2. **Software Setup**:
   - Install the required libraries in the Arduino IDE.
   - Open the provided Arduino sketch and update the following credentials:
     ```cpp
     char ssid[] = "YourWiFiSSID";
     char pass[] = "YourWiFiPassword";
     #define BLYNK_AUTH_TOKEN "YourBlynkAuthToken"
     ```
   - Upload the code to the NodeMCU ESP8266.

3. **Blynk Configuration**:
   - Set up a Blynk template with Virtual Pins:
     - V0: Temperature
     - V1: Humidity
     - V2: Weight
   - Enable notifications for critical alerts (e.g., low IV bag weight, high temperature).

---

## **Usage**
1. Power on the system.
2. Calibrate the load cell using a known weight.
3. Place the IV bag on the load cell.
4. Monitor the IV bag weight and room conditions in real-time via the Blynk dashboard.
5. Respond to audio-visual alerts and notifications as needed.

---

## **Limitations**
1. Servo mechanism requires precise calibration for effective IV tube control.
2. System operation depends on stable internet connectivity.
3. Fixed thresholds may need customization for specific patient needs.

---

## **Future Enhancements**
- **Improved Automation**: Enhance servo control for more reliable IV fluid cutoff.
- **Additional Sensors**: Include patient health sensors like heart rate monitors.
- **Customizable Thresholds**: Enable user-defined alert limits for better adaptability.
- **Offline Functionality**: Add local data storage and offline alert systems.
- **Battery Backup**: Ensure uninterrupted operation during power outages.

---

## **Screenshots**

**Blynk Dashboard**
  ![image](https://github.com/user-attachments/assets/d42f99b3-ef7a-431f-83b4-8fd98cd40774)

**Hardware Setup**

  ![Circuit_Design](https://github.com/user-attachments/assets/2a949121-b46b-4827-82d2-83d97548cbad)

**Notifications**
  
  ![WhatsApp Image 2024-11-19 at 4 56 44 PM](https://github.com/user-attachments/assets/fa03c2c9-f3a7-406e-b855-0b150d59b96e)


---

## **Contributors**
- Aktaruzzaman
- Abdullah Al Mamun  
- Rummon islam
- Md. Nazmul Parves
- Naim Hoshain Pranto

Feel free to fork, modify, and improve this project! Contributions are always welcome.

---

## **License**
This project is licensed under the MIT License. See the `LICENSE` file for details.
