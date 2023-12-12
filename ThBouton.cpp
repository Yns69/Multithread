#include <stdio.h>
#include "Mthreads.h"
#include "Donnees_Partagees.h"
#include "CPiface.h"

void* Thread_Bouton(void* arg) {

	int* ptr = (int*)arg; // D�pointeur de int.

	// Association avec le Piface et les donn�es partag�es

	CPiface* ptr_Piface = (CPiface*)ptr[1]; // Je lui passse l'adresse de la Piface contenue dans le tableau pass� en param�tre.
	Donnees_Partagees* ptr_Donnees_Partagees = (Donnees_Partagees*)ptr[0]; // Je lui passse l'adresse des donn�es partag�es contenue dans le tableau pass� en param�tre.

	int bouton;

	do {

		bouton = ptr_Piface->TestBouton();
		switch (bouton)
		{
		case 0: break;
		case 1:ptr_Donnees_Partagees->PlusVite(); break;
		case 2:ptr_Donnees_Partagees->MoinsVite(); break;
		case 3:ptr_Donnees_Partagees->ChangeSens(); break;
		case 4: break;
		}

	} while ((bouton != 4) && (sem_trywait (&ptr_Donnees_Partagees->synchroFin) != 0));

	if (bouton == 4)
	{
	sem_post(&ptr_Donnees_Partagees->synchroFin); // On lib�re le s�maphore pour que le main puisse le prendre.
	sem_post(&ptr_Donnees_Partagees->synchroFin); // On lib�re le s�maphore pour que le main puisse le prendre.
	}

	
}

