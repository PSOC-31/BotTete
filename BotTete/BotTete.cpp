#include "BotTete.h"
#include <Adafruit_NeoPixel.h>

BotTete::BotTete() {



}

void BotTete::initialisation() {

  pixels = Adafruit_NeoPixel(6, 4, NEO_GRB + NEO_KHZ800);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);



  while (!tcs.begin()) {
    //Serial.println("no sensor");
  }
     


 pinMode(A0, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(A1, INPUT); // Sets the echoPin as an INPUT


  serialgauche = new    SoftwareSerial(10, 11);;
  serialdroit = new   SoftwareSerial(12, 13);
  serialtestbox = new   SoftwareSerial(8, 9);


  Serial.begin(9600);
  //    while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  //  }

  serialgauche->begin(9600);
  serialdroit->begin(9600);
  serialtestbox->begin(9600);


  servoCou.attach(3);
  servoSourcilG.attach(5);
  servoSourcilD.attach(6);
  
pos=97;
servoCou.write(pos);
Serial.begin(9600);
  Serial.println("ok tete started2");

}

void BotTete::envoyerInfoCorps() {
  /*
    A objet present
    B objet rouge
    C objet vert
    D objet bleu
    E pass ok
    F pass ko
  */
  serialgauche->print(info);
  serialdroit->print(info);
  serialtestbox->print(info);

}

int BotTete::recevoirInfoBox()
{
  info = -1;
  //    Serial.println("in receive:");
  if (serialtestbox->available())
  {
    int _inf = (int)serialtestbox->read() - 48;
    if (_inf > -1 && _inf < 7)
      info = _inf;
    //      info=(int);
    Serial.println(_inf);
    Serial.println((int)info);
  }
  return info;
}

bool BotTete::objetPresent() {
if (distanceObjet()<distMin)
	return true;
else return false;

}

int BotTete::distanceObjet() {
	
	long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


	 digitalWrite(A0, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(A0, HIGH);
  delayMicroseconds(10);
  digitalWrite(A0, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(A1, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
return distance;

}

int BotTete::niveauRouge() {

  float red, green, blue;

  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);

  tcs.setInterrupt(true);  // turn off LED
  return (int(red));

}
int BotTete::niveauVert() {
  float red, green, blue;

  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);

  tcs.setInterrupt(true);  // turn off LED
  return (int(green));

}
int BotTete::niveauBleu() {
  float red, green, blue;

  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);

  tcs.setInterrupt(true);  // turn off LED
  return (int(blue));

}


bool BotTete::estRouge() {
  float red, green, blue;

  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);

  tcs.setInterrupt(true);  // turn off LED

  if ((int)red > 105 && (int)green < 105 && (int)blue < 105)
    return true;
  else return false;

}
bool BotTete::estVert() {
  float red, green, blue;

  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);

  tcs.setInterrupt(true);  // turn off LED

  if ((int)red < 105 && (int)green > 105 && (int)blue < 105)
    return true;
  else return false;

}
bool BotTete::estBleu() {
  float red, green, blue;

  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);

  tcs.setInterrupt(true);  // turn off LED

  if ((int)red < 105 && (int)green < 105 && (int)blue > 105)
    return true;
  else return false;
}

void BotTete::froncerSourcils() {
  servoSourcilG.attach(5);
  servoSourcilD.attach(6);
  delay(100);
  servoSourcilG.write(120);
  servoSourcilD.write(60);
  delay(1000);

  servoSourcilG.detach();
  servoSourcilD.detach();

}
void BotTete::sourcilsDroits() {
  servoSourcilG.attach(5);
  servoSourcilD.attach(6);
  delay(100); servoSourcilG.write(90);
  servoSourcilD.write(90);
  delay(1000);

  servoSourcilG.detach();
  servoSourcilD.detach();
}
void BotTete::sourcilsHeureux() {
  servoSourcilG.attach(5);
  servoSourcilD.attach(6);
  delay(100);
  servoSourcilG.write(60);
  servoSourcilD.write(120);
  delay(1000);

  servoSourcilG.detach();
  servoSourcilD.detach();
}
void BotTete::boucheRouge() {
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for (int i = 0; i < 6; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(150, 0, 0));


    //    delay(DELAYVAL); // Pause before next pass through loop
  }
  pixels.show();   // Send the updated pixel colors to the hardware.

}
void BotTete::boucheVerte() {
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for (int i = 0; i < 6; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));


    //    delay(DELAYVAL); // Pause before next pass through loop
  }
  pixels.show();   // Send the updated pixel colors to the hardware.

}
void BotTete::boucheBleue() {
  Serial.println("bleu");
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for (int i = 0; i < 6; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));


    //    delay(DELAYVAL); // Pause before next pass through loop
  }
  pixels.show();   // Send the updated pixel colors to the hardware.

}
void BotTete::boucheCustomisee(int rouge, int vert, int bleu) {
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for (int i = 0; i < 6; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(rouge, vert, bleu));


    //    delay(DELAYVAL); // Pause before next pass through loop
  }
  pixels.show();   // Send the updated pixel colors to the hardware.

}

void BotTete::tourneDroite() {
  for ( pos = pos; pos >= 60; pos -= 1) { // goes from 180 degrees to 0 degrees
    servoCou.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void BotTete::tourneGauche() {
 for ( pos = pos; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoCou.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
void BotTete::tourneFace() {
	if (pos<92)
	{
	for ( pos = pos; pos <= 97; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoCou.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }	
	}else if (pos>92)
	{
		 for ( pos = pos; pos >= 97; pos -= 1) { // goes from 180 degrees to 0 degrees
    servoCou.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
	}
	
}
void BotTete::tourne(int angle) {
  if (angle > 180)
    servoCou.write(180);
  else if (angle < 0)
    servoCou.write(0);
  else servoCou.write(angle);
}
