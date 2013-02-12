#ifndef STRUCT_H
#define STRUCT_H
#define TAILLE 3


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



#endif
