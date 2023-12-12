#pragma once
#include <semaphore.h>
#include <pthread.h>

class Donnees_Partagees
{
private:
	int sens;
	int vitesse;
	pthread_mutex_t mutexVariablesPartagees;

protected:

public:
	sem_t synchroFin;

	Donnees_Partagees();
	~Donnees_Partagees();
	void ChangeSens();
	void PlusVite();
	void MoinsVite();
	int LitSens();
	int LitVitesse();

};

