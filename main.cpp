/*
* blink.c:
* Simple "blink" test for the PiFace interface board.
***********************************************************************
*/
#include <stdio.h>
#include <wiringPi.h>
#include <piFace.h>
#include "CPiface.h"
#include <iostream>
#include "Donnees_Partagees.h"
#include "Mthreads.h"
using namespace std;
 /*Use 200 as the pin-base for the PiFace board, and pick a pin
 for the LED that's not connected to a relay*/
#define PIFACE 200
#define LED (PIFACE+2)
int main(int argc, char* argv[])
{
	CPiface Piface(PIFACE);
	Donnees_Partagees DonnPartag;

	//*****Création d'un tableau d'entier contentant les adresses de nos deux objets associés au thread de gestion des boutons.*****
	int parametre[2];

	//*****On le remplie en fesant un transtypage (une adresse fait la taille d'un entier).******
	parametre[1] = (int)&Piface;
	parametre[0] = (int)&DonnPartag;

	pthread_t th_bouton, th_clavier; // On déclare deux ID de threads
	int bouton = 0;
	int numled = 1;
	int sens = DonnPartag.LitSens();
	int vitesse = DonnPartag.LitVitesse();
	pthread_create(&th_bouton, NULL, Thread_Bouton, (void*)parametre);
	pthread_create(&th_clavier, NULL, Thread_clavier, (void*)&DonnPartag);


	//**********Test du chenillard***********

	do {
		Piface.AllumerLed(numled);
		delay(vitesse);
		Piface.EteindreLed(numled);
		sens = DonnPartag.LitSens();
		vitesse = DonnPartag.LitVitesse();
		numled = numled + sens;
		if (sens == 1 && numled == 9) {
			numled = 1;
		}
		if (sens == -1 && numled == 0) {
			numled = 8;
		}

	} while ((sem_trywait(&DonnPartag.synchroFin) != 0)); // Tant que l'on ne peut pas prendre le sémaphore de synchro.

		//return 0;

	// Après cette boucle le thread est terminer, il à laché le sémaphore.

	pthread_join(th_bouton, NULL); // On attend la fin du thread boutton.
	pthread_join(th_clavier, NULL);
	return 0;



//**********Test du thread ThBoutton**********


//while (1)
//{
//	for (int i = 1; i <= 8; i++) // Si le sens est droite/gauche
//	{
//		Piface.AllumerLed(i);
//		delay(vitesse);
//		Piface.EteindreLed(i);
//	}
//	for (int i = 8; i >= 1; i--) // Si le sens est gauche/droite
//	{
//		Piface.AllumerLed(i);
//		delay(vitesse);
//		Piface.EteindreLed(i);
//	}
//}
//Test du chenillard
//while (1); // Jusqu'a appui sur le boutton quitter
//{
//	int numled = 1;
//	int sens = 1;
//	Piface.AllumerLed(numled);
//	delay(vitesse);
//	Piface.EteindreLed(numled);
//	numled = numled + sens; // Qui vaut +1 ou -1 selon le sens définie.
//	if (numled = 9)
//		numled = 1;
//	if (numled = 0)
//		numled = 8;

	// Autre solustion
	/*
	if (sens==1)
		numled=(numled==8)?1:numled+sens
	else numled='numled==1)?8:numled+sens
	*/
	//}
	/*Piface.InitPullUp();
	bttest = Piface.TestBouton();*/



	//printf("Raspberry Pi PiFace Blink\n");
	//printf("=========================\n");
	//// Always initialise wiringPi. Use wiringPiSys() if you don't need (or want) to run as root
	//wiringPiSetupSys();
	//// Setup the PiFace board
	//piFaceSetup(PIFACE);
	//for (;;)
	//{
	//	digitalWrite(LED, HIGH); // On
	//	// la fonction delay(int ms) permet de générer un délai en ms
	//	delay(500); // ms
	//	digitalWrite(LED, LOW); // Off
	//	delay(500);
	//}
	//return 0;
}