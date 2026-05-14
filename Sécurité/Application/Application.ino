
/*
 #include <SoftwareSerial.h>


//Adress of HC-05: 98:D3:51:FF:08:5E
sudo rfcomm release 0
sudo rfcomm connect 0 98:D3:51:FF:08:5E 1
echo "H" | sudo tee /dev/rfcomm0 
sudo screen /dev/rfcomm0 9600

Rien qui marche, un vrai problème. Linux arrive à parler avec la module, ou je me connecte bien avec le module. 
Mais dès que j'essaye de retrouver le message ou string envoyé par l'environnement Linux, rien s'affiche dans le serial monitor
Faut rechercher plus, jsp. Parler avec Acco peut-etre. Faut que je regarde auusi sur un oscillo pour juste voir si quelque bits arrive ou quoi
*/

/*
#define RX 14 //D5
#define TX  12 //D6

SoftwareSerial mySer(RX,TX);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);


while(!Serial){};
Serial.println("Testing here!");
mySer.begin(9600);
mySer.println("Testing 2!");

}

void loop() {

//Serial.println("H");
delay(2000);

//Reponse sur l'oscillo:
//111111111000 01001010 101001 10100011 011010001101101011111011010101100001001010000 11111111111111

// 000 010010101 010011

// Message envoyé: Hello = 01001000 01100101 01101100 01101100 01101111 00100000


//Bare "H": 01001000
// h MED LSB til venstre: 00010010
// Envoyé: 0 _00010010_ 10101100001001010000 /Hva nå enn dette er, ingen peiling...
  
  if(mySer.available()){
    Serial.write(mySer.read());
  }
  if(Serial.available()){
    mySer.write(Serial.read());
}

}
*/
// ça marche avec Serial Bluetooth Terminal

//Discovery board RX(PB11), TX(PB10)

#include <SoftwareSerial.h>

#define BTouVESC 3


#define RXBT 14  // D5
#define TXBT 12  // D6

#define RX2_VESC 16  //D0 RX ESP8266 / PB10 TX Discovery
#define TX2_VESC 5   //D1 TX ESP8266 / PB11 RX Discovery


#if BTouVESC == 1
SoftwareSerial mySer(RXBT, TXBT);

void setup() {
  Serial.begin(9600);  // Serial Monitor
  mySer.begin(9600);   // HC-05
  Serial.println("ESP8266 ready!");
}

void loop() {
  // Bluetooth → Serial Monitor
  while (mySer.available()) {
    char c = mySer.read();
    Serial.print(c);
  }

  // Serial Monitor → Bluetooth
  while (Serial.available()) {
    char c = Serial.read();
    mySer.print(c);
    mySer2.write(c);
  }
  
}

#elif BTouVESC == 0
SoftwareSerial mySerVesc(RX2_VESC, TX2_VESC);

void setup() {
  Serial.begin(9600);     // Serial Monitor
  mySerVesc.begin(9600);  // HC-05
  Serial.println("ESP8266 ready!");
}

void loop() {
  // Bluetooth → Serial Monitor
  while (mySerVesc.available()) {
    char c = mySerVesc.read();
    Serial.print(c);
  }

  // Serial Monitor → Bluetooth
  while (Serial.available()) {
    char c = Serial.read();
    mySerVesc.print(c);
  }
}

#elif BTouVESC == 3 

// BT on SoftwareSerial
SoftwareSerial BT(RXBT, TXBT);

void setup() {
  Serial.begin(115200);     // USB debug
  BT.begin(9600);           // HC-05
  Serial1.begin(115200);    // TX only (GPIO2) maybe to VESC
}

void loop() {
  while (BT.available()) {
    char c = BT.read();
    Serial.write(c);
    Serial1.write(c);   // to VESC
  }

  while (Serial.available()) {
    char c = Serial.read();
    BT.write(c);
  }
}


#endif
