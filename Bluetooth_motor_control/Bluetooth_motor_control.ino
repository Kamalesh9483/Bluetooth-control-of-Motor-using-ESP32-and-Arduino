
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

// setup for bluetooth app
int received;
char receivedChar;

const char speed1 = '1';
const char speed2 = '2';
const char speed3 = '3';
const char turnOFF = 'F';


// Motor A pin setup
const int IN_1 = 27;
const int IN_2 = 26;
const int EN_A = 14;

// PWM setup
int freq = 115200;
int pwmChannel = 0;
int resolution = 8;
int dutyCycle = 120;


void setup() {
 
  Serial.begin(115200);
  SerialBT.begin("Bluetooth_Motor_Control"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println("To run motor at speed1 type: 1 "); // print on serial monitor
  Serial.println("To run motor at speed2 type: 2  "); // print on serial monitor
  Serial.println("To run motor at speed3 type: 3 "); // print on serial monitor
  Serial.println("To off motor type: F "); // print on serial monitor

   // Motor pins
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(EN_A, OUTPUT);

  // PWM setup
  ledcSetup(pwmChannel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(EN_A, pwmChannel);
}

void loop() {
  receivedChar = (char) SerialBT.read();
  
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  
  if (SerialBT.available()) {
    SerialBT.print("Received"); // write the text in Bluetooth app
    SerialBT.println(receivedChar); // write the text in Bluetooth app
  
    Serial.print("Received"); // write the text in Serial monitor
    Serial.println(receivedChar); // write the text in serial monitor

  // speed1 conditional statement
    if(receivedChar == speed1)
      {
        SerialBT.println("Motor ON with dutyCycle:");
        SerialBT.println(dutyCycle);
        Serial.println("Motor ON with dutyCycle:");
        Serial.println(dutyCycle);
    
       // DC motor with speed1
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, LOW);          
        ledcWrite(pwmChannel, dutyCycle);      
      }

 // speed2 conditional statement
     else if(receivedChar == speed2)
      {
        SerialBT.println("Motor ON with dutyCycle:");
        SerialBT.println(dutyCycle+55);
        Serial.println("Motor ON with dutyCycle:");
        Serial.println(dutyCycle+55);
    
       // DC motor with speed1
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, LOW);          
        ledcWrite(pwmChannel, (dutyCycle+55)); 
      }

 // speed3 conditional statement
      else if(receivedChar == speed3)
      {
        SerialBT.println("Motor ON with dutyCycle:");
        SerialBT.println(dutyCycle+120);
        Serial.println("Motor ON with dutyCycle:");
        Serial.println(dutyCycle+120);
    
       // DC motor with speed1
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, LOW);          
        ledcWrite(pwmChannel, (dutyCycle+120)); 
      }

 // Motor OFF conditional statement
      else if(receivedChar == turnOFF)
      {
        SerialBT.println("Motor OFF");
        Serial.println("Motor OFF");
    
       // DC motor with speed1
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);          
      } 
  }
  delay(20);
}
