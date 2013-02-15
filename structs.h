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

struct position {
  int x;
  int y;
};

struct plateau {
  struct carte **tab;  /* plateau == tableau a deux dimensions */
  int hauteur; /* hauteur du plateau */
  int largeur; /* largeur du plateau */
};




typedef struct carte Carte;
typedef struct position Position;
typedef struct plateau Plateau;




#endif
