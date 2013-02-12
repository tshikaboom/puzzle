#ifndef CONTACT_H
#define CONTACT_H

/*Fonctions*/

/*teste si la case est en contact en haut*/
int contact_h(Carte *plateau[][TAILLE],int i, int j, Carte Carte);

/*teste le contact à droite*/
int contact_d(Carte *plateau[][TAILLE],int i, int j,int largeur, Carte Carte);

/*teste le contact en bas */
int contact_b(Carte *plateau[][TAILLE],int i , int j, int hauteur, Carte Carte);

/*teste le contact à gauche*/
int contact_g(Carte *plateau[][TAILLE],int i, int j, Carte Carte);

/*test si la carte est positionnable a la postion donnee*/
int cartePossible(Carte *carte, Carte *plateau[][TAILLE],int i, int j, int largeur, int hauteur);
#endif
