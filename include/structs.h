#ifndef STRUCTS_H
#define STRUCTS_H

#define TAILLE 3 /* le cote du plateau carre, on a donc TAILLE*TAILLE cases */
#define DBG printf("%s : %d\n",__FILE__,__LINE__); /* sert au debogage */

/*Structure d'une carte*/
struct carte {
  int identifiant;      /* L'identifiant de la carte */
  int Haut;             /* valeur se trouvant sur le haut de la carte */
  int Bas;              /* valeur du bas de la carte */
  int Gauche;           /* valeur de la gauche de la carte */
  int Droite;           /* valeur de la droite de la carte */
  unsigned int rotated; /* indice de rotation */
  /* La rotation de la carte varie entre 0 et 4. Les valeurs 0 et 4 sont equivalents,
     la difference etant qu'on sait que la carte a deja effectue une rotation complete
     avec la valeur 4. Des qu'une rotation aura ete effectuee, la carte ne pourra
     plus avoir la valeur 0. (sert pour la fonction rotation)
     La rotation d'une carte signifie qu'elle est tournee dans le sens des aiguilles
     d'une montre. La variable est alors incrementee de 1. */     
  unsigned int sur_plateau; /* 0 = pas sur plateau et 1 = sur plateau */
};



/* Structure de position */
struct position {
  int x;
  int y;
};

/* Structure du plateau */
struct plateau {
  struct carte ***tab;  /* plateau == tableau a deux dimensions de pointeurs */
  int hauteur; /* hauteur du plateau */
  int largeur; /* largeur du plateau */
};

/* structure du chemin, revient a une liste chainee en pratique
   x et y sont les coordonnees sur le plateau */
struct chemin {
    int x;
    int y;
    struct chemin *Suivant;
};

typedef struct coordonnee Coordonnee;
typedef struct chemin Chemin;
typedef struct carte Carte;
typedef struct position Position;
typedef struct plateau Plateau;

#endif
