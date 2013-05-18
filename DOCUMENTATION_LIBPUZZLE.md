DOCUMENTATION DE LA BIBLIOTHEQUE PUZZLE
=======================================


STUCTURES DE DONNEES
--------------------

__Structure d'une carte__	


    struct carte {
        int identifiant;      -> L'identifiant de la carte 
        int Haut;             -> valeur se trouvant sur le haut de la carte
        int Bas;              -> valeur du bas de la carte
        int Gauche;           -> valeur de la gauche de la carte
        int Droite;           -> valeur de la droite de la carte
        unsigned int rotated; -> indice de rotation
  
> La rotation de la carte varie entre 0 et 4. Les valeurs 0 et 4 sont equivalents, 
> la difference etant qu'on sait que la carte a deja effectue une rotation complete
> avec la valeur 4. Des qu'une rotation aura ete effectuee, la carte ne pourra		
> plus avoir la valeur 0. (sert pour la fonction rotation)  
> La rotation d'une carte signifie qu'elle est tournee dans le sens des aiguilles	
> d'une montre. La variable est alors incrementee de 1. */     
  
        unsigned int sur_plateau; -> 0 = pas sur plateau ET 1 = sur plateau 
    };

__Structure de Position__	

    struct position{
        int x;
        int y;
    };

__Structure du plateau__

    struct plateau {
      struct carte ***tab;  -> plateau == tableau a deux dimensions de pointeurs
      int hauteur;          -> hauteur du plateau
      int largeur;          -> largeur du plateau
    };

    typedef struct carte Carte;
    typedef struct position Position;
    typedef struct plateau Plateau;

__Structure du chemin, revient à une liste chainée en pratique où x et y sont les coordonnées du plateau__

    struct chemin {
        int x;
        int y;
        struct chemin *Suivant;
    };

    typedef struct coordonnee Coordonnee;
    typedef struct chemin Chemin;
 
BACKTRACK.H
-----------

> _Algorithme de backtracking._   
    `int backtrack (Plateau *plateau,Carte tabCarte[], Chemin *parcours, int nombre_de_carte);`

CHEMIN.H
--------

> _Initialisation d'une liste chainee._  
    `Chemin* nouveauChemin(int x, int y);`

> _Ajout d'un element dans la liste._  
    `Chemin* ajouteChemin(Chemin *liste, int x, int y);`

> _minimum entre deux nombres._  
    `int min(int a,int b);`

> _valeur absoluee d'un nombre._  
    `int abs(int n);`

> _Accesseur des coordonnees de la premiere cellule de la liste._  
    `Position get_pos(Chemin *chemin);`

> _Affichage minimaliste d'un chemin en (x, y)._  
    `void print_chemin(Chemin *chemin);`

> _Fonctions creant les chemins pour un plateau de taille arbitraire et retournent une liste avec les coordonnees necessaires._  
     
     
    `Chemin* constCompCheminSpirale(int n, int p);`  
    `Chemin* ajouteLigneX(Chemin* chemin, int xDepart, int xArrivee, int y);`  
    `Chemin* ajouteLigneY(Chemin* chemin, int yDepart,int yArrivee,int x);`  
    `Chemin* constCheminSpiraleDec(Chemin* chemin,int n, int p, int xOff, int yOff);`  
    `Chemin* serpentTwo(Chemin *chemin,int n,int p,int xOffset, int yOffset);`  

>_Fonctions dites allias, n'utilisant pas d'offset
	`Chemin* constCheminEnS(int n,int p);`
	`Chemin* constCheminSpirale(int n, int p);` 
	`Chemin* serpentDeux(Chemin *chemin,int n,int p);`

CONTACT.H
---------

> _teste si la carte est positionnable avec la carte deja posee en haut de (i, j) sur le plateau._  
    `int contact_h(Plateau *plateau, int i, int j, Carte Carte);`

> _idem pour la droite._  
    `int contact_d(Plateau *plateau, int i, int j, Carte Carte);`

> _idem pour le bas._   
    `int contact_b(Plateau *plateau, int i, int j, Carte Carte);`

> _idem pour la gauche._   
    `int contact_g(Plateau *plateau, int i, int j, Carte Carte);`

> _Teste si la carte est positionnable a la postion donnee. Utilise les 4 fonctions precedemment definies._   
    `int cartePossible(Carte *carte, Plateau *plateau,int i, int j);`

INIT.H
------

> _Fonction determinant la case de depart pour un parcours en spirale._   
    `Position caseDepart (int largeur, int hauteur);`

> _Suivant => case suivant vide ou non._   
    `int suivant (Plateau *plateau, Position courante);`

> _Gestion de la rotation: rotation(carte, 1) tourne la carte une fois dans le sens des aiguilles d'une montre._   
    `void rotation (Carte *carte,unsigned int nombre);`

> _Affichage d'un plateau de taille arbitraire._  
    `void affichage (Plateau *plateau);`

> _Allocation d'un nouveau plateau de taille largeur*hauteur. La fonction initialise les cases du plateau a NULL._   
    `Plateau *nouveau_plateau(int hauteur, int largeur);`

> _liberation du plateau._  
    `void free_plateau(Plateau *plateau);`

> _Echange la liste de carte. Sert a generer toutes les solutions._  
    `void swap (Plateau *plateau,Carte tabCarte[]);`

> _Nettoyage du plateau pour la fonction backtrack._  
    `void clean_plateau (Plateau *plateau);`

> _fonction permettant de savoir si un fichier existe._  
    `int existe_fichier(char *fichier);`

> _Renvoie un fichier contenant la solution du puzzle._  
    `void exporteur_magique(Plateau *plateau);`

> _Copie un string dans un pointeur de char (revient à un malloc et strcpy)._   
    `char *strdup_intern(char *string);`

PARSER.H
--------

> _Checks if input char is EndOfLine._  
    `int isEndOfLine (char cara);`

> _char* Error Message._  
    `void error(char* errorMessage);`

> _Read the card._  
    `int readCard(char* stringCard, Carte* current);`

> _Carte** reads a puzzle file and stores the data into the defined structure_  
    `Carte* parseFile(char* filename,int* hauteur,int* largeur);`

> _Carte** exports the current puzzle to a text file._  
    `void export(char* filename, Plateau *plateau);`

