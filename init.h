#ifndef INIT_H
#define INIT_H

/*Structure d'une carte*/
struct carte {
  int identifiant;
  int Haut;
  int Bas;
  int Gauche;
  int Droite;
  unsigned int rotated;
  unsigned int sur_plateau; /* 0 = pas sur plateau et 1 = sur plateau */
};

typedef struct carte Carte;

struct position {
  int x;
  int y;
};
typedef struct position Position;

/*Fonctions*/

/*Case de  depart*/
Position caseDepart (int largeur, int hauteur);

/*Suivant => case suivant vide ou non*/
int suivant (int largeur, int hauteur, Carte *plateau[][],int x, int y);

/*Gestion de la rotation*/
void rotation (Carte *carte,unsigned int nombre);

/*Affichage*/
void affichage (Carte *plateau[][], int largeur, int hauteur);

#endif
