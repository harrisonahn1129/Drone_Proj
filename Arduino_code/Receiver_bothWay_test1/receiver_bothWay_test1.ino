#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address [][6] = {"00001","00002"};
int data [4] = {0, 0, 0, 0};
int item [4] = {9, 9, 9, 9};


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.openWritingPipe(address[1]);
  radio.openReadingPipe(1, address[0]);
}

void loop() {
  send();
}

void send() {
  delay(5);
  radio.stopListening();
  radio.write(&item, sizeof(item));

//  for (int i=0;i<4;i++){
//    Serial.print(item[i]);
//  }
//  Serial.println();

  getting();
}

//receiving data
void getting() {
  delay(10);
  radio.startListening();
  radio.read(&data, sizeof(data));

  for (int i=0;i<4;i++){
    Serial.print("[");
    Serial.print(data[i]);
    Serial.print("] ");
  }
  Serial.println();
  
}
