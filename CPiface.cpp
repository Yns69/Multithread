#include "CPiface.h"

CPiface::CPiface() {

	init(PIFACE);
	printf("Constructeur : Aucun paramètre\n");
}

CPiface::CPiface(unsigned int AdrBase) {

	init(AdrBase);
	InitPullUp();
	printf("Constructeur : Adresse PPIFACE en paramètre\n");
}

void CPiface::init(unsigned int AdrBase) {

	wiringPiSetupSys(); // Initialisation de la bibliothèque wiringPi.
	piFaceSetup(AdrBase); // Fixe l'adresse de base de la carte.

}

void CPiface::AllumerLed(unsigned int led) {

	if (led >= 1 && led <= 8)
	{
		digitalWrite((led - 1 + PIFACE), HIGH);
	}
}

void CPiface::EteindreLed(unsigned int led) {

	if (led >= 1 && led <= 8)
	{
		digitalWrite((led - 1 + PIFACE), LOW);
	}
}

void CPiface::RazLed() {

	for (int i = PIFACE; i <= PIFACE + 7; i++) {
		digitalWrite(i, LOW);
	}
}

void CPiface::AllLed() {

	for (int i = PIFACE; i <= PIFACE + 7; i++) {
		digitalWrite(i, HIGH);
	}
}

void CPiface::InitPullUp() {

	for (int i = 1; i <= 4; i++)
	{
		pullUpDnControl(PIFACE - 1 + i, PUD_UP);
	}
}

int CPiface::TestBouton() {

	int resultat = 0;

	for (int i = 0; i <= 3; i++)
		if (digitalRead(PIFACE + i) == LOW)
			resultat = i + 1;

	delay(200);
	return resultat;
}


CPiface::~CPiface() {

}