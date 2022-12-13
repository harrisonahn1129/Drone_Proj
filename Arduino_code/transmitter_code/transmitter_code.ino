#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const byte address[6] = "00001";
unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000;


RF24 radio(7, 8); // CE, CSN
int VRx = A0;
int VRy = A1;
int xPosition = 0;
int yPosition = 0;
//int SW_state = 0;
int mapX = 0;
int mapY = 0;

int data [4] = {0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  radio.begin();
//  radio.setDataRate(RF24_250KBPS);
//  radio.enableAckPayload();
//  radio.setRetries(5, 5);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
}

void loop() {
//  Tested transmittion of integer array (suc)
//  currentMillis = millis();
//  if (currentMillis - prevMillis >= txIntervalMillis) {
//    send();
//  }
  delay(5);
  send();
}

void send() {
//  bool result;
//  result = (radio.write(&data, sizeof(data)));
//  if (result) {
//    if(radio.isAckPayloadAvailable()){
//      int battery[1]= {0};
//      radio.read(&battery, sizeof(battery));
//      Serial.print(battery[0]);
//      Serial.println();
//    }
//    radio.write(&data, sizeof(data));
//  }
//
//  prevMillis = millis();


   joy();
   data[0] = mapX;
   data[1] = mapY;
   
   radio.write(&data, sizeof(data));

//  for (int i=0;i<4;i++){
//      Serial.print(data[i]);
//    }
//  Serial.println();
}

void joy() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);

  mapX = map(xPosition, -512, 512, -512, 512);
  mapY = map(yPosition, -512, 512, -512, 512);

  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.println();
}
