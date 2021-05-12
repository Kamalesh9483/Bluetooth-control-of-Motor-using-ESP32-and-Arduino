
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

// setup for bluetooth app
int received;
char receivedChar;

const char turnON = 'a';
const char turnOFF = 'b';

// Motor A pin setup
const int IN_1 = 27;
const int IN_2 = 26;
// const int EN_A = 14;

void setup() {
 
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println("To turn on motor type: a "); // print on serial monitor
  Serial.println("To turn off motor type: b "); // print on serial monitor

   // Motor pins
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  // pinMode(EN_A, OUTPUT);
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

    if(receivedChar == turnON)
      {
        SerialBT.println("Motor ON");
        Serial.println("Motor ON");
    
         // Move DC motor 
          digitalWrite(IN_1, HIGH);
          digitalWrite(IN_2, LOW);
      }

     else if(receivedChar == turnOFF)
      {
        SerialBT.println("Motor OFF");
        Serial.println("Motor OFF");
    
         // OFF the DC Motor

        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);   
      }
    
  }
  delay(20);
}
