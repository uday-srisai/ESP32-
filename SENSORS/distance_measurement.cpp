/*
Ultrasonic Distance Measurement System using ESP32

Components Used:
1. ESP32
2. HC-SR04 Ultrasonic Sensor
3. Jumper Wires
4. Breadboard

Output:
- Measures distance using ultrasonic sensor
- Serial Monitor displays distance in centimeters
- Displays "Out of Range" when distance exceeds sensor limit
*/
#include <Arduino.h>

const uint8_t trig_pin = 18;
const uint8_t echo_pin = 23;

long duration;
float distance_cm;

void setup()
{
    Serial.begin(115200);

    pinMode(trig_pin,OUTPUT);
    pinMode(echo_pin,INPUT);
}

void loop()
{
    //Clear trigger pin
    digitalWrite(trig_pin,LOW);
    delayMicroseconds(2);

    //Send 10 microsecond pulse
    digitalWrite(trig_pin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin,LOW);

    //Measure echo pulse duration
    duration = pulseIn(echo_pin, HIGH);

    //Calculate distance
    distance_cm =(duration * 0.034)/2;

    if(distance_cm>400)
    {
        Serial.println("out of range");
    }
    else
    {
    //Print distance
    Serial.print("Distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
    }

    delay(500);
}