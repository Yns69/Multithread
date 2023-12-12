#include "Donnees_Partagees.h"

Donnees_Partagees::Donnees_Partagees() {

	sens = 1; // On initialise le sens de la la led inf�rieur vers a led sup�rieur � la construction.
	vitesse = 1000; // On initialise la vitesse.
	pthread_mutex_init(&mutexVariablesPartagees, NULL); // On initialise notre muteux comme NULL.
	sem_init(&synchroFin, 0, 0); // Le s�maphore de sychronisation de fin est cr�e � 0, (comme d�ja pris).
}

Donnees_Partagees::~Donnees_Partagees() {

	pthread_mutex_destroy(&mutexVariablesPartagees);
	sem_destroy(&synchroFin);
}

void Donnees_Partagees::ChangeSens() {
	pthread_mutex_lock(&mutexVariablesPartagees);
	sens = -sens;
	pthread_mutex_unlock(&mutexVariablesPartagees);
}

void Donnees_Partagees::PlusVite() {
	pthread_mutex_lock(&mutexVariablesPartagees);
	vitesse = vitesse - 100;
	pthread_mutex_unlock(&mutexVariablesPartagees);
}

void Donnees_Partagees::MoinsVite() {
	pthread_mutex_lock(&mutexVariablesPartagees);
	vitesse = vitesse + 100;
	pthread_mutex_unlock(&mutexVariablesPartagees);
}

int Donnees_Partagees::LitSens() {
	return sens;
}

int Donnees_Partagees::LitVitesse() {
	return vitesse;
}