#ifndef CONTACT_H
#define CONTACT_H

#include "structs.h"

/* Ces fonctions sont centrees sur la carte du point de vue des coordonnees
   voir src/contact.c pour plus de precisions
*/

/* teste si la carte est positionnable avec la carte deja posee en haut de (i, j)
   sur le plateau */
int contact_h(Plateau *plateau, int i, int j, Carte Carte);

/* idem pour la droite */
int contact_d(Plateau *plateau, int i, int j, Carte Carte);

/* idem pour le bas */
int contact_b(Plateau *plateau, int i, int j, Carte Carte);

/* idem pour la gauche*/
int contact_g(Plateau *plateau, int i, int j, Carte Carte);

/* Teste si la carte est positionnable a la postion donnee.
   Utilise les 4 fonctions precedemment definies. */
int cartePossible(Carte *carte, Plateau *plateau,int i, int j);

#endif
