/* Point d'entree principal du programme */
#define _POSIX_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "contact.h"
#include "init.h"
#include "structs.h"
#include "backtrack.h"
#include "parser.h"
#include "chemin.h"
/* --no-swap --no-rotation */
int parse_args(int argc, char *argv[],
	       int *choix_parcours, int *swap,
	       int *rotate, int *quiet,
	       char** fichier)
{
  int i;
  for (i=1; i<argc; i++)
    if (!existe_fichier(argv[i])) {
      if (strcmp(argv[i], "--no-swap") == 0) *swap=0;
      if (strcmp(argv[i], "--no-rotate") == 0) *rotate=0;
      if (strcmp(argv[i], "--help") == 0) return -1;
      if (strcmp(argv[i], "--quiet") == 0) *quiet=1;
    }
    else {
      *fichier = strdup_intern(argv[i]);
      if (i+1 >= argc) return -1;
      *choix_parcours = atoi(argv[i+1]);
      i++;
    }
  return 0;
}

void print_help(char *nom_programme)
{
    printf("\nUsage: %s [FICHIER MODE] [OPTION ..]\n\n", nom_programme);
    printf("FICHIER etant un fichier avec les cartes et la taille du plateau a resoudre.\n");
    printf("MODE etant l'entier 1, 2 ou 3.\n");
    printf(" 1: resolution du puzzle en spirale a partir du centre\n");
    printf(" 2: resolution du puzzle en serpent a partir du coin superieur gauche\n");
    printf(" 3: resolution du puzzle en hybride (spirale+serpent)\n");
    printf("    Ceci sert surtout pour des plateaux rectangulaires.\n");
    printf(" 4: resolution du puzzle en serpentTwo\n\n");
    printf("Les OPTIONS sont\n");
    printf(" --no-swap : seule la premiere carte sera placee initialement.\n");
    printf("             Il n'y aura pas de placement possible des autres cartes disponibles\n");
    printf(" --no-rotate : la carte initialement placee ne subira pas de rotation initiale.\n");
    printf(" --quiet: on obtient un backtrack pas tres bavard.\n");
    printf(" --help : afficher ce message.\n");
    printf("Appel sans fichier: resolution d'un plateau deja donne dans le programme.\n\n");
}

int main(int argc, char *argv[])
{
  int choix_parcours, cpt, rotated_real, opt_swap=1, opt_rotate=1, i, j, silence=0;
  int hauteur, largeur; /* servent a initialiser la hauteur et la largeur du plateau */
  Carte carte1,carte2, carte3, carte4, carte5, carte6, carte7, carte8, carte9;
  Carte backup;
  Plateau *plateau;
  Carte *tabCarte=NULL;
  Chemin *parcours=NULL;
  char *fichier=NULL;
  char buff[100];

  /* initialisation possible, mais pas sur
     - du choix de parcours
     - si on veut swapper
     - si on veut tourner la carte initialement placee
     - si on veut manger un puzzle d'un fichier (donc on initialise fichier) */
  if (parse_args(argc, argv,
		 &choix_parcours,
		 &opt_swap,
		 &opt_rotate,
		 &silence,
		 &fichier) == -1) {
    print_help(argv[0]);
    exit(EXIT_SUCCESS);
  }

  /* Programme appele avec un fichier, on parse le puzzle */
  if (fichier)
    tabCarte = parseFile(fichier, &hauteur, &largeur);

  /* Programme appele sans fichier, on cree un puzzle soi-meme
     Le macro TAILLE est defini dans "structs.h" */
  else {
    hauteur = TAILLE;
    largeur = TAILLE;
    /* allocation du tableau de cartes */
    tabCarte = (Carte *) malloc(TAILLE*TAILLE*sizeof(Carte));
    assert(tabCarte);

    /* initialisation des cotes des cartes, puzzle de reference */
    carte1.Haut = -1; carte1.Bas = -2; carte1.Gauche = 3; carte1.Droite = 4;
    carte2.Haut = -3; carte2.Bas = -2; carte2.Gauche = 1; carte2.Droite = 4;
    carte3.Haut = -2; carte3.Bas = -4; carte3.Gauche = 1; carte3.Droite = 3;
    carte4.Haut = -4; carte4.Bas = -3; carte4.Gauche = 3; carte4.Droite = 1;
    carte5.Haut = -4; carte5.Bas = -2; carte5.Gauche = 1; carte5.Droite = 2;
    carte6.Haut = -1; carte6.Bas = -2; carte6.Gauche = 1; carte6.Droite = 4;
    carte7.Haut = -1; carte7.Bas = -4; carte7.Gauche = 3; carte7.Droite = 2;
    carte8.Haut = -3; carte8.Bas = -4; carte8.Gauche = 3; carte8.Droite = 2;
    carte9.Haut = -4; carte9.Bas = -3; carte9.Gauche = 1; carte9.Droite = 3;

    /* initialisation en masse des cartes avec les memes valeurs initiales */
    carte1.sur_plateau = carte2.sur_plateau = carte3.sur_plateau = carte4.sur_plateau =
      carte5.sur_plateau = carte6.sur_plateau = carte7.sur_plateau = carte8.sur_plateau =
      carte9.sur_plateau = 0;
    carte1.rotated = carte2.rotated = carte3.rotated = carte4.rotated = carte5.rotated =
      carte6.rotated = carte7.rotated = carte8.rotated = carte9.rotated = 0;

    /* initialisation des identifiants */
    carte1.identifiant = 1;
    carte2.identifiant = 2;
    carte3.identifiant = 3;
    carte4.identifiant = 4;
    carte5.identifiant = 5;
    carte6.identifiant = 6;
    carte7.identifiant = 7;
    carte8.identifiant = 8;
    carte9.identifiant = 9;

    /* remplissage du tableau de cartes */
    tabCarte[0] = carte1;
    tabCarte[1] = carte2;
    tabCarte[2] = carte3;
    tabCarte[3] = carte4;
    tabCarte[4] = carte5;
    tabCarte[5] = carte6;
    tabCarte[6] = carte7;
    tabCarte[7] = carte8;
    tabCarte[8] = carte9;

    print_help(argv[0]);
    choix_parcours=-1;
    while (choix_parcours < 0 || choix_parcours > 4) {
      printf("Donner le choix de parcours de la grille:\n");
      printf(" 1: spirale (depart du centre)\n");
      printf(" 2: S\n");
      printf(" 3: hybride\n");
      printf(" 4: serpentTwo\n");
      printf(" 0: Quitter\n");
      printf(">> ");
      scanf("%d",&choix_parcours);
    }
    if (choix_parcours == 0) exit(EXIT_SUCCESS);
  }

  switch (choix_parcours)  {
  case 1:
    #ifdef DEBUG
    printf("Generation d'une spirale %dx%d\n", hauteur, largeur);
    #endif
    parcours = constCheminSpirale(largeur, hauteur);
    break;
  case 2:
    #ifdef DEBUG
    printf("Generation d'un S %dx%d\n", hauteur, largeur);
    #endif
    parcours = constCheminEnS(largeur, hauteur);
    break;
  case 3:
    #ifdef DEBUG
    printf("Generation d'un chemin hybride %dx%d\n", hauteur, largeur);
    #endif
    parcours = constCompCheminSpirale(largeur, hauteur);
    break;
  case 4:
    #ifdef DEBUG
    printf("Generation d'un serpentTwo %dx%d\n", hauteur, largeur);
    #endif
    parcours = serpentTwo(NULL, largeur, hauteur, 0, 0);
    break;
  default:
    printf("Mode %d non supporte.\n", choix_parcours);
    exit(EXIT_FAILURE);
  }


  /* initialisation des bornes des boucles selon les arguments de main() */

  if (opt_swap) opt_swap=hauteur*largeur;
  /* si opt_swap==1 alors on swappe normalement */
  else opt_swap=1;
  /* si opt_swap==0 alors on ne swappe pas */

  /* meme principe pour opt_rotate */
  if (opt_rotate) opt_rotate=4;
  else opt_rotate=1;


  plateau = nouveau_plateau(hauteur, largeur);

  /* Debut de la partie principale du programme.
     Regles pour la carte initiale:
     - elle est swappee hauteur*largeur fois
     - avant chaque swap (donc "pendant" un swap), elle est
     aussi tournee 3 fois pour la rotation initiale
     Donc on teste hauteur*largeur*4 situations initiales

     .. sauf arguments indiquant le contraire
  */
  for (cpt=0; cpt<opt_swap; cpt++) {
    backup = tabCarte[0];
    for (rotated_real=0; rotated_real<opt_rotate; rotated_real++) {
      #ifdef DEBUG
      printf("backtrack: carte initiale %d, rotation reelle %d\n",
	     tabCarte[0].identifiant, rotated_real);
      #endif
      backtrack(plateau, tabCarte, parcours, hauteur*largeur, silence);
      rotation(tabCarte, 1); /* nouvelle rotation initiale */
      tabCarte[0].rotated = 0; /* 0 car la carte "tournee" a maintenant une nouvelle
				  "rotation initiale" */
    }
    tabCarte[0] = backup;
    swap(plateau, tabCarte);
  }

  if (fichier) {
    sprintf(buff, "cp %s ./%dx%d/puzzle", fichier, plateau->hauteur, plateau->largeur);
    system(buff);
  }
  else {
    for (j=0; j<plateau->hauteur; j++)
      for (i=0; i<plateau->largeur; i++)
	plateau->tab[i][j] = tabCarte+i+j;

    sprintf(buff, "./%dx%d/puzzle", plateau->hauteur, plateau->largeur);
    export(buff, plateau);
  }
  return EXIT_SUCCESS;
}
