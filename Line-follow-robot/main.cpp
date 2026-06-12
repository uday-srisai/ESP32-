
#include <Arduino.h>

//pwm
const uint8_t ch1=0;
const uint8_t ch2=1;
const uint32_t frequency=5000;
const uint8_t resolution=8;


//motor pins
const uint8_t IN1=18;
const uint8_t IN2=19;

const uint8_t IN3=32;
const uint8_t IN4=33;

//pwm
const uint8_t ENA=26;
const uint8_t ENB=27;

//sensor pins
const uint8_t right_ir=22;
const uint8_t center_ir=23;
const uint8_t left_ir=25;



void forward()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);

    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
}

void stop_motor()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);

    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
}


void left()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);

    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
}

void right()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);

    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
}

void setup()
{
    Serial.begin(115200);
    //motor
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);

    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);

    // sensor
    pinMode(right_ir,INPUT);
    pinMode(center_ir,INPUT);
    pinMode(left_ir,INPUT);

    ledcSetup(ch1,frequency,resolution);
    ledcSetup(ch2,frequency,resolution);
    ledcAttachPin(ENA,ch1);
    ledcAttachPin(ENB,ch2);
    ledcWrite(ch1,180);
    ledcWrite(ch2,180);
}

void loop()
{
    
    int L=digitalRead(left_ir);
    int C=digitalRead(center_ir);
    int R=digitalRead(right_ir);

    Serial.print("L:");
    Serial.print(L);
    Serial.print(" ");

    Serial.print("C:");
    Serial.print(C);
    Serial.print(" ");

    Serial.print("R:");
    Serial.print(R);
    Serial.println(" ");
    
if(L==0 && C==1 && R==0)
{
    forward();
}
else if(L==1 && R==0)
{
    left();
}
else if(R==1 && L==0)
{
    right();
}
else if(L==1 && C==1 && R==1)
{
    forward();
}
else
{
    stop_motor();
}

}
