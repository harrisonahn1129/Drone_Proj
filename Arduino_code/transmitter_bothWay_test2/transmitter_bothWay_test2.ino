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
//RF24 radio(11, 12, 13); //MO, MI, SCK

int data [4] = {0, 0, 0, 0};
int item [4] = {2, 2, 2, 2};

int VRx = A0;
int VRy = A1;

int xPosition = 0;
int yPosition = 0;
//int SW_state = 0;
int mapX = 0;
int mapY = 0;

int CLK = 6; // pin6 for clk
int DT = 5; // pin5 for DT
int rot_position = 0;
int rotation;
int value;
boolean LeftRight;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[1]);
  radio.setPALevel(RF24_PA_MIN);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  rotation = digitalRead(CLK);
}

void loop() {
  send();
}

void send() {
  delay(5);
  radio.stopListening();
  joystick();
  encoder();
  data[0] = rot_position;
  data[1] = mapX;
  data[2] = mapY;
  radio.write(&data, sizeof(data));

  for (int i=0;i<4;i++){
    Serial.print("[");
    Serial.print(data[i]);
    Serial.print("] ");
  }
  Serial.println();

  getting();
}

void getting() {
  delay(10);
  radio.startListening();
  radio.read(&item, sizeof(item));

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

//  Serial.print("X: ");
//  Serial.print(mapX);
//  Serial.print(" | Y: ");
//  Serial.print(mapY);
//  Serial.println();
}

void encoder() {
  value = digitalRead(CLK);

  if ( value != rotation){
    if ( digitalRead(DT) != value){
      rot_position++;
      delay(5);
    }
    else{
      rot_position--;
      if (rot_position < 0){
        rot_position = 0;
      }
      delay(5);
    }
  }
  rotation = value;
}
