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
  
> La rotation de la carte varie entre 0 et 4. Les valeurs 0 et 4 sont équivalents, 
> la différence étant qu'on sait que la carte a déja subit une rotation complète
> avec la valeur 4. Dès qu'une rotation aura été effectuée, la carte ne pourra		
> plus avoir la valeur 0. (utile pour la fonction rotation)  
> La rotation d'une carte signifie qu'elle est tournée dans le sens des aiguilles	
> d'une montre. La variable est alors incrémentée de 1. */     
  
        unsigned int sur_plateau; -> 0 = pas sur plateau ET 1 = sur plateau 
    };

__Structure de Position__	

    struct position{
        int x;
        int y;
    };

__Structure du plateau__

    struct plateau {
      struct carte ***tab;  -> plateau == tableau à deux dimensions de pointeurs
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

> _Initialisation d'une liste chainée._  
    `Chemin* nouveauChemin(int x, int y);`

> _Ajout d'un élément dans la liste._  
    `Chemin* ajouteChemin(Chemin *liste, int x, int y);`

> _minimum entre deux nombres._  
    `int min(int a,int b);`

> _valeur absolue d'un nombre._  
    `int abs(int n);`

> _Accesseur des coordonnées de la première cellule de la liste._  
    `Position get_pos(Chemin *chemin);`

> _Affichage minimaliste d'un chemin en (x, y)._  
    `void print_chemin(Chemin *chemin);`

> _Fonctions pemettant la création de chemins._  
     
     
    `Chemin* constCompCheminSpirale(int n, int p);`  
    `Chemin* ajouteLigneX(Chemin* chemin, int xDepart, int xArrivee, int y);`  
    `Chemin* ajouteLigneY(Chemin* chemin, int yDepart,int yArrivee,int x);`  
    `Chemin* constCheminSpiraleDec(Chemin* chemin,int n, int p, int xOff, int yOff);`  
    `Chemin* serpentTwo(Chemin *chemin,int n,int p,int xOffset, int yOffset);`  

> _Fonctions dites allias, n'utilisant pas d'offset
	`Chemin* constCheminEnS(int n,int p);`
	`Chemin* constCheminSpirale(int n, int p);` 
	`Chemin* serpentDeux(Chemin *chemin,int n,int p);`

CONTACT.H
---------

> _Teste si la carte est positionnable avec la carte déjà posée en haut de (i, j) sur le plateau._  
    `int contact_h(Plateau *plateau, int i, int j, Carte Carte);`

> _Idem pour la droite._  
    `int contact_d(Plateau *plateau, int i, int j, Carte Carte);`

> _Idem pour le bas._   
    `int contact_b(Plateau *plateau, int i, int j, Carte Carte);`

> _Idem pour la gauche._   
    `int contact_g(Plateau *plateau, int i, int j, Carte Carte);`

> _Teste si la carte est positionnable à la postion donnée. Utilise les 4 fonctions précédemment définies._   
    `int cartePossible(Carte *carte, Plateau *plateau,int i, int j);`

INIT.H
------

> _Suivant => case suivant vide ou non._   
    `int suivant (Plateau *plateau, Position courante);`

> _Gestion de la rotation: rotation(carte, 1) tourne la carte une fois dans le sens des aiguilles d'une montre._   
    `void rotation (Carte *carte,unsigned int nombre);`

> _Affichage d'un plateau de taille arbitraire._  
    `void affichage (Plateau *plateau);`

> _Allocation d'un nouveau plateau de taille largeur*hauteur. La fonction initialise les cases du plateau à NULL._   
    `Plateau *nouveau_plateau(int hauteur, int largeur);`

> _Libération du plateau._  
    `void free_plateau(Plateau *plateau);`

> _Échange la liste de carte. Pour générer toutes les solutions, on fait passer la carte de la tête de liste en fin de liste_  
    `void swap (Plateau *plateau,Carte tabCarte[]);`

> _Nettoyage du plateau pour la fonction backtrack._  
    `void clean_plateau (Plateau *plateau);`

> _Fonction permettant de savoir si un fichier existe._  
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
