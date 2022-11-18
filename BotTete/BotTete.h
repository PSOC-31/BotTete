#ifndef BOTTETE_H_
#define BOTTETE_H_

#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"
/*

capteurs:
yeux=distance=HC-SR04
nez=couleurs=TCS34725

actionneurs:
sourcils=servos
bouche=ruban leds adressables
cou=servo

comm:
softwareSerial pour les bras et la box test sanitaire

*/

	#define presenceObjet 1
	#define objetRouge 2
	#define objetVert 3 
	#define objetBleu 4 
	#define passOK 5
	#define passKO 6

class BotTete {
	
	private :
	
	protected: 
	
	Servo servoSourcilG;
	Servo servoSourcilD;
	Servo servoCou;
	
	Adafruit_NeoPixel pixels;//(6, 2, NEO_GRB + NEO_KHZ800);

	//(14,15);  // Initialize sensor that uses digital pins 13 and 12.
	// set to false if using a common cathode LED

	bool commonAnode=true;


	// our RGB -> eye-recognized gamma color

	byte gammatable[256];

	Adafruit_TCS34725 tcs; // = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


	int pos;

	int info;
	int distMin=4;
	SoftwareSerial * serialgauche;
	SoftwareSerial * serialdroit;
	SoftwareSerial * serialtestbox;
	
	public:
	
	//@tete
	//@bloc texte=nouvelle tete png=achanger.png
	BotTete();

	//@bloc texte=reveiller la tete png=achanger.png
	void initialisation();
	
	
	
	
	//@communication
	//@bloc texte=envoyer les infos aux bras png=achanger.png
	void envoyerInfoCorps();
	//@bloc texte=recevoir les infos de la testbox info png=achanger.png
	int recevoirInfoBox();
	
	//@capteurs
	//@bloc texte=detecter un objet png=achanger.png
	bool objetPresent();
	//@bloc texte=detecter un objet png=achanger.png
	int distanceObjet();
	
	//@bloc texte=niveau de rouge png=achanger.png
	int niveauRouge();
	//@bloc texte=niveau de vert png=achanger.png
	int niveauVert();
	//@bloc texte=niveau de bleu png=achanger.png
	int niveauBleu();
	
	
	//@bloc texte=renvoie vrai si l'objet est rouge png=achanger.png
	bool estRouge();
	//@bloc texte=renvoie vrai si l'objet est vert png=achanger.png
	bool estVert();
	//@bloc texte=renvoie vrai si l'objet est bleu png=achanger.png
	bool estBleu();
	
	//@actionneurs
	//@bloc texte= froncer les sourcils png=achanger.png
	void froncerSourcils();
	//@bloc texte= sourcils droits png=achanger.png
	void sourcilsDroits();
	//@bloc texte= sourcils heureux png=achanger.png
	void sourcilsHeureux();
	
	//@bloc texte= bouche rouge png=achanger.png
	void boucheRouge();
	//@bloc texte= bouche verte png=achanger.png
	void boucheVerte();
	//@bloc texte= bouche bleue png=achanger.png
	void boucheBleue();
	//@bloc texte= bouche customisee unie png=achanger.png
	void boucheCustomisee(int rouge, int vert, int bleu);
	//@bloc texte= tourner la tete a gauche png=achanger.png
	void tourneGauche();
	//@bloc texte= tourner la tete a droite png=achanger.png
	void tourneDroite();
	//@bloc texte= tourner la tete a droite png=achanger.png
	void tourneFace();
		//@bloc texte= tourner la tete png=achanger.png
	void tourne(int angle);

	
	
};

#endif