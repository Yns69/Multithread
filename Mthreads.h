#pragma once

// On lui passe en param�tre un tebleau de 2 cases, 1ere case : l'adresse de la PIFACE, 2 case : l'adresse des donn�es partag�es.
// C'est pour faire l'association entre la classe thread de gestion des boutons, avec les donn�es partag�es et la classe CPiface.

void* Thread_Bouton(void*);
void* Thread_clavier(void*);