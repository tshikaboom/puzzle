/* Point d'entree principal du programme */
#define _POSIX_SOURCE 1

#include <stdio.h>
#include <stdlib.h>

#include "contact.h"
#include "init.h"
#include "structs.h"
#include "backtrack.h"
#include "parser.h"
#include "chemin.h"


int main(int argc, char *argv[])
{
  int choix_parcours, cpt;
  int hauteur, largeur; /* servent a initialiser la hauteur et la largeur du plateau */
  Carte carte1,carte2, carte3, carte4, carte5, carte6, carte7, carte8, carte9;
  Plateau *plateau;
  Carte *tabCarte;
  Chemin *parcours;

  if (argc > 3 || argc == 2) {
    printf("Usage: %s [FICHIER MODE]\n", argv[0]);
    printf("FICHIER etant un fichier avec les cartes et la taille du plateau a resoudre.\n");
    printf("MODE etant l'entier 1, 2 ou 3.\n");
    printf(" 1: resolution du puzzle en spirale a partir du centre\n");
    printf(" 2: resolution du puzzle en serpent a partir du coin superieur gauche\n");
    printf(" 3: resolution du puzzle en hybride (spirale+serpent)\n");
    printf("    Ceci sert surtout pour des plateaux rectangulaires.\n");
    printf("Appel sans argument: resolution d'un plateau deja donne dans le programme.\n");
    return EXIT_FAILURE;
  }

  /* programme appele avec un fichier */
  else if (argc == 3) {
    tabCarte = parseFile(argv[1], &hauteur, &largeur);


    if (atoi(argv[2]) == 1) {
      plateau = nouveau_plateau(hauteur, largeur);
      parcours = constCheminSpirale(largeur, hauteur);
      cpt=0;
      while (cpt < hauteur*largeur) {
	backtrack(plateau, tabCarte, parcours, hauteur*largeur, 0, 1);
	swap(plateau, tabCarte);
	cpt++;
	#ifdef DEBUG
	printf("main, parcours en spirale: swap %d sur %d\n", cpt, TAILLE*TAILLE);
	#endif
      }
    }
    else if (atoi(argv[2]) == 2) {
      plateau = nouveau_plateau(hauteur, largeur);
      parcours = constCheminEnS(largeur, hauteur);
      cpt=0;
      while (cpt < hauteur*largeur) {
	backtrack(plateau, tabCarte, parcours, hauteur*largeur, 0, 2);
	swap(plateau, tabCarte);
	cpt++;
       	#ifdef DEBUG
	printf("main, parcours en S: swap %d sur %d\n", cpt, TAILLE*TAILLE);
	#endif
      }
    }
    else if (atoi(argv[2]) == 3) {
      plateau = nouveau_plateau(hauteur, largeur);
      parcours = constCompCheminSpirale(largeur, hauteur);
      cpt=0;
      while (cpt<hauteur*largeur) {
	backtrack(plateau, tabCarte, parcours, hauteur*largeur, 0, 2);
	swap(plateau, tabCarte);
	cpt++;
	#ifdef DEBUG
	printf("main, parcours en S: swap %d sur %d\n", cpt, TAILLE*TAILLE);
	#endif
      }
    }
    else
      printf("Mode %s non supporte.\n", argv[2]);
  }

  /* programme appele sans fichier, on cree un plateau soi-meme */
  /* le macro TAILLE est defini dans "structs.h" */
  else {

  /* allocation et initialisation des cases du plateau a NULL */
  plateau = nouveau_plateau(TAILLE, TAILLE);
  tabCarte = (Carte *) malloc(TAILLE*TAILLE*sizeof(Carte));


  /* initialisation des cotes des cartes, avec ce set on a normalement une solution */
  carte1.Haut = 1;carte1.Bas = 3;carte1.Gauche = 2; carte1.Droite = 4;
  carte2.Haut = 1;carte2.Bas = 4;carte2.Gauche = 3; carte2.Droite = 2;
  carte3.Haut = 3;carte3.Bas = 1;carte3.Gauche = 2; carte3.Droite = 4;
  carte4.Haut = 1;carte4.Bas = 3;carte4.Gauche = 2; carte4.Droite = 4;
  carte5.Haut = 1;carte5.Bas = 3;carte5.Gauche = 2; carte5.Droite = 4;
  carte6.Haut = 3;carte6.Bas = 1;carte6.Gauche = 2; carte6.Droite = 4;
  carte7.Haut = 1;carte7.Bas = 3;carte7.Gauche = 4; carte7.Droite = 2;
  carte8.Haut = 3;carte8.Bas = 1;carte8.Gauche = 4; carte8.Droite = 2;
  carte9.Haut = 1;carte9.Bas = 3;carte9.Gauche = 2; carte9.Droite = 4;

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

  printf("*************************************************************************************************\n");
  printf("                                            PUZZLE                                               \n");
  printf("*************************************************************************************************\n\n");
  printf("Donner le choix de parcours de la grille : (1 pour en spirale (depart du centre) et 2 pour en S) -> entrer un autre chiffre pour quitter \n");

  /*scanf("%d",&choix_parcours);*/
  choix_parcours=1;

  if (choix_parcours == 1) {
    cpt=0;
    parcours = constCheminSpirale(TAILLE, TAILLE);
    printf("\n#== PARCOURS EN SPIRALE ==#\n");
    while (cpt != 9) {
      /* Test sur le parcours en spirale */
      backtrack(plateau, tabCarte, parcours, TAILLE*TAILLE, 0, 1);
      swap(plateau,tabCarte);
      cpt++;
      #ifdef DEBUG
      printf("main, parcours en serpent: swap %d sur %d\n", cpt, TAILLE*TAILLE);
      #endif
    }
  }
  else if (choix_parcours == 2) {
    cpt=0;
    parcours = constCheminEnS(TAILLE, TAILLE);
    printf("\n#== PARCOURS EN S ==#\n");
    while (cpt != 9) {
      /* Test sur le parcours en S */
      backtrack(plateau, tabCarte, parcours, TAILLE*TAILLE, 0, 2);
      swap(plateau,tabCarte);
      cpt++;
      #ifdef DEBUG
      printf("main, parcours en S: swap %d sur %d\n", cpt, TAILLE*TAILLE);
      #endif
    }
  }
  else {
      printf("*****************\n");
      printf("Mauvais numero !!\n");
      printf("*****************\n");
    }
  }
  return EXIT_SUCCESS;
}
