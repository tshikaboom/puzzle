#ifndef CONTACT_H
#define CONTACT_H

/*Fonctions*/

/*teste si la case est en contact en haut*/
int contact_h(Carte *plateau[][],int i, int j, Carte *carte);

int contact_d(Carte *plateau[][],int i, int j,int largeur, Carte *carte);/*teste le contact à droite*/

int contact_b(Carte *plateau[][],int i , int j, int hauteur, Carte *carte);/*teste le contact en bas */

int contact_g(Carte *plateau[][],int i, int j, Carte *carte);/*teste le contact à gauche*/

int cartePossible(Carte *carte, Carte *plateau[][]);
#endif
