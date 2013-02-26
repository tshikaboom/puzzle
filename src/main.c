#define _POSIX_SOURCE 1

#include <stdio.h>
#include <stdlib.h>

#include "contact.h"
#include "init.h"
#include "structs.h"
#include "backtrack.h"
#include "parser.h"


int main()
{
  int i,j,choix_parcours,cpt;
  Carte carte1, carte2, carte3, carte4, carte5, carte6, carte7, carte8, carte9;
  Plateau *plateau;
  Carte tabCarte[9];
  
  system("clear");
  
  plateau = (Plateau *) malloc(sizeof(Plateau));
  plateau->tab = (Carte ***) malloc(TAILLE*sizeof(Carte **));
  for (i=0; i<TAILLE; i++)
    plateau->tab[i] = (Carte **) malloc(TAILLE*sizeof(Carte *));

  plateau->largeur = TAILLE;
  plateau->hauteur = TAILLE;

   
  carte1.Haut = 1;carte1.Bas = 1;carte1.Gauche = 1; carte1.Droite = 1;
  carte2.Haut = 2;carte2.Bas = 2;carte2.Gauche = 2; carte2.Droite = 2;
  carte3.Haut = 3;carte3.Bas = 3;carte3.Gauche = 3; carte3.Droite = 3;
  carte4.Haut = 4;carte4.Bas = 4;carte4.Gauche = 4; carte4.Droite = 4;
  carte5.Haut = 5;carte5.Bas = 5;carte5.Gauche = 5; carte5.Droite = 5;
  carte6.Haut = 6;carte6.Bas = 6;carte6.Gauche = 6; carte6.Droite = 6;
  carte7.Haut = 7;carte7.Bas = 7;carte7.Gauche = 7; carte7.Droite = 7;
  carte8.Haut = 8;carte8.Bas = 8;carte8.Gauche = 8; carte8.Droite = 8;
  carte9.Haut = 9;carte9.Bas = 9;carte9.Gauche = 9; carte9.Droite = 9;

  carte1.sur_plateau =  carte2.sur_plateau =  carte3.sur_plateau =  carte4.sur_plateau =  carte5.sur_plateau =  carte6.sur_plateau =  carte7.sur_plateau =  carte8.sur_plateau =  carte9.sur_plateau = 0;
  carte1.rotated =  carte2.rotated =  carte3.rotated =  carte4.rotated =  carte5.rotated =  carte6.rotated =  carte7.rotated =  carte8.rotated =  carte9.rotated = 0;
  carte1.identifiant = 1;
  carte2.identifiant = 2;
  carte3.identifiant = 3;
  carte4.identifiant = 4;
  carte5.identifiant = 5;
  carte6.identifiant = 6;
  carte7.identifiant = 7;
  carte8.identifiant = 8;
  carte9.identifiant = 9;
  
  tabCarte[0] = carte1;
  tabCarte[1] = carte2;
  tabCarte[2] = carte3;
  tabCarte[3] = carte4;
  tabCarte[4] = carte5;
  tabCarte[5] = carte6;
  tabCarte[6] = carte7;
  tabCarte[7] = carte8;
  tabCarte[8] = carte9;
  
  
  /*
  plateau->tab[0][0] = &carte1;
  plateau->tab[1][0] = &carte2;
  plateau->tab[2][0] = &carte3;
  plateau->tab[0][1] = &carte4;
  plateau->tab[1][1] = &carte5;
  plateau->tab[2][1] = &carte6;
  plateau->tab[0][2] = &carte7;
  plateau->tab[1][2] = &carte8;
  plateau->tab[2][2] = &carte9;

  affichage(plateau);
  */
  for (i=0; i<TAILLE;i++)
    {
      for(j=0; j<TAILLE;j++){plateau->tab[i][j] = NULL;}}
  
  
  printf("*************************************************************************************************\n");
  printf("                                            PUZZLE                                               \n");
  printf("*************************************************************************************************\n\n");
  printf("Donner le choix de parcours de la grille : (1 pour en spirale (depart du centre) et 2 pour en S) -> entrer un autre chiffre pour quitter \n");
  scanf("%d",&choix_parcours);
  
  if (choix_parcours == 1)
    {
      cpt=0;
      while (cpt != 9)
	{
	  /*Test sur le parcours en spirale*/
	  printf("\n#== PARCOURS EN SPIRALE ==#\n");
	  backtrack(plateau, tabCarte, 9, -1, 1);
	  swap(plateau,tabCarte);
	  cpt++;
	}
    }
  else if (choix_parcours == 2)
    {
      /*Test sur le parcours en S*/
      printf("\n#== PARCOURS EN S ==#\n");
      backtrack(plateau, tabCarte, 9, -1, 2);
    }
  else
    {
      printf("*****************\n");
      printf("Mauvais numero !!\n");
      printf("*****************\n");
    }
  
  return EXIT_SUCCESS;
}
