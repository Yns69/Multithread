#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
using namespace std;
#include "Donnees_Partagees.h"
#include "CPiface.h"



void* Thread_clavier(void* data)
{
	// s'associer a la ZDC
	
	Donnees_Partagees* ptr_Donnees_Partagees = (Donnees_Partagees*)data; // Je lui passse l'adresse des données partagées contenue dans le tableau passé en paramètre.

	char touche;// numBouton;
	// on enleve le mode canonique du clavier
	// plus besoin de taper entrer apres l appui d'une touche
	system("stty -icanon min 1");
	// passe en non bloquant
	fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
	do {
		touche = getchar();
		cout << touche << endl;
		cout.flush();



		switch (touche)
		{
		case '0': break;
		case '1':ptr_Donnees_Partagees->PlusVite(); break;
		case '2':ptr_Donnees_Partagees->MoinsVite(); break;
		case '3':ptr_Donnees_Partagees->ChangeSens(); break;
		case '4': break;
		}
	} while ((touche != '4') && (sem_trywait(&ptr_Donnees_Partagees->synchroFin) != 0)); //
	if (touche == '4') {
		sem_post(&ptr_Donnees_Partagees->synchroFin); // On libère le sémaphore pour que le main puisse le prendre.
		sem_post(&ptr_Donnees_Partagees->synchroFin); // On libère le sémaphore pour que le main puisse le prendre.
	}
	cout << " fin thread clavier\n";
	
	// on remet le mode canonique sur le clavier et la lecture bloquante
	fcntl(0, F_SETFL, fcntl(0, F_GETFL) & ~O_NONBLOCK);
	system("stty icanon min 1");
	return NULL;
}