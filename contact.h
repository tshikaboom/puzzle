#ifndef CONTACT_H
#define CONTACT_H

#include "structs.h"
/*Fonctions*/

/*teste si la case est en contact en haut*/
int contact_h(Plateau *plateau, int i, int j, Carte Carte);

/*teste le contact à droite*/
int contact_d(Plateau *plateau, int i, int j, Carte Carte);

/*teste le contact en bas */
int contact_b(Plateau *plateau, int i, int j, Carte Carte);

/*teste le contact à gauche*/
int contact_g(Plateau *plateau, int i, int j, Carte Carte);

/*test si la carte est positionnable a la postion donnee*/
int cartePossible(Carte *carte, Plateau *plateau,int i, int j, int largeur, int hauteur);

#endif
