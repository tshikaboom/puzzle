#ifndef INIT_H
#define INIT_H
#include "structs.h"


/*Fonctions*/

/*Case de  depart*/
Position caseDepart (int largeur, int hauteur);

/*Suivant => case suivant vide ou non*/
int suivant (Plateau *plateau, Position courante);

/*Gestion de la rotation*/
void rotation (Carte *carte,unsigned int nombre);

/*Affichage*/
void affichage (Plateau *plateau);

/* allocation d'un nouveau plateau de taille largeur*hauteur */
Plateau *nouveau_plateau(int hauteur, int largeur);

/*Echange la liste de carte -> sert a parcourirs toutes les solutions*/
void swap (Plateau *plateau,Carte tabCarte[]);

#endif
