#pragma once

// On lui passe en paramètre un tebleau de 2 cases, 1ere case : l'adresse de la PIFACE, 2 case : l'adresse des données partagées.
// C'est pour faire l'association entre la classe thread de gestion des boutons, avec les données partagées et la classe CPiface.

void* Thread_Bouton(void*);
void* Thread_clavier(void*);