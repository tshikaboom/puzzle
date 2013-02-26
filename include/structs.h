#ifndef STRUCT_H
#define STRUCT_H
#define TAILLE 3
#define DBG printf("%s : %d\n",__FILE__,__LINE__);

/*Structure d'une carte*/
struct carte {
  int identifiant; /*identifiant d'une carte*/
  int Haut; /*valeur se trouvant sur en haut de la carte*/
  int Bas; /*idem mais pour le bas de la carte*/
  int Gauche; /*idem mais pour la gauche de la carte*/
  int Droite; /*idem mais pour la droite de la carte*/
  unsigned int rotated; /*indice de rotation*/
  unsigned int sur_plateau; /* 0 = pas sur plateau et 1 = sur plateau */
};

/*Structure de position*/
struct position {
  int x;
  int y;
};

/*Structure du plateau*/
struct plateau {
  struct carte ***tab;  /* plateau == tableau a deux dimensions */
  int hauteur; /* hauteur du plateau */
  int largeur; /* largeur du plateau */
};

typedef struct carte Carte;
typedef struct position Position;
typedef struct plateau Plateau;

#endif
