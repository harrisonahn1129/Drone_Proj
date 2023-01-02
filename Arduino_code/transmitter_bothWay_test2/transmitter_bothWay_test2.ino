// Last Update: Going to change the model of the encoder next week to other [need to remove all the current encoder code and implement the new one].

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>

// Testing the transmission of both rec and tra w/ joystick

const byte address[][6] = {"00001","00002"};

RF24 radio(7, 8); // CE, CSN

// data = X value, Y value, Height, 0
int data [4] = {0, 0, 0, 0};
int item [4] = {2, 2, 2, 2};

int VRx = A0;
int VRy = A1;
int xPosition = 0;
int yPosition = 0;
int mapX = 0;
int mapY = 0;

// Height
int zPosition = 0;

// potentiometer read
int pot = A3;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[1]);
  radio.setPALevel(RF24_PA_MIN);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(pot, INPUT);
}

void loop() {
  send();
}

void send() {
  delay(5);
  radio.stopListening();
  joystick();
  potentiometer();
  data[0] = mapX;
  data[1] = mapY;
  data[2] = zPosition;
  radio.write(&data, sizeof(data));

// Testing
//  for (int i=0;i<4;i++){
//    Serial.print("[");
//    Serial.print(data[i]);
//    Serial.print("] ");
//  }
//  Serial.println();

  getting();
}

void getting() {
  delay(10);
  radio.startListening();
  radio.read(&item, sizeof(item));

// Testing code
//  for (int i=0;i<4;i++){
//   Serial.print(item[i]);
//  }
//  Serial.println();
}

void joystick() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);

  mapX = map(xPosition, -512, 512, -512, 512);
  mapY = map(yPosition, -512, 512, -512, 512);

// Testing code
//  Serial.print("X: ");
//  Serial.print(mapX);
//  Serial.print(" | Y: ");
//  Serial.print(mapY);
//  Serial.println();
}

void potentiometer() {
  zPosition = analogRead(pot);
}
