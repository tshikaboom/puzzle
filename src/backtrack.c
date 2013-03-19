#define _POSIX_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "structs.h"
#include "init.h"
#include "contact.h"
#include "chemin.h"
#include "backtrack.h"


#define TRUE 1 /*SI VRAI*/
#define FALSE 0 /*SI FAUX*/

/****************************/
/*Algorithme de backtracking*/
/****************************/
void affichage_minimaliste(Plateau *plateau)
{
  int i, j;
  for (i = 0; i < plateau->hauteur; i++) {
    for (j = 0; j < plateau->largeur; j++)
      if (plateau->tab[i][j] == NULL)
	printf(" ");
      else
	printf("%d", plateau->tab[i][j]->identifiant);
    printf("\n");
  }
}


int backtrack (Plateau *plateau ,Carte tabCarte[], int nombre_de_carte,int indice_chemin,int choix)
{
  int nombre_de_solution;
  int carte=0; /*numero de la carte -> identifiant de la carte*/
  Position position_case; /*position de la case courante*/
  int int_carte_possible;
  int ind_chemin = indice_chemin;
  /*DBG*/;
  printf("\n");
  printf("Debut de fct btrack, ndecartes %d\n", nombre_de_carte);
  /*indice_chemin doit etre egal a -1 au depart sinon la fonction chemin ne donnera pas le bon chemin*/
  position_case = chemin(indice_chemin,choix);
  nombre_de_solution = 0;

  /*DBG*/;

  /* affichage_minimaliste(plateau); */
  affichage(plateau);
  sleep (1);
  /*Placement de la premiere carte sur le plateau*/
  if (nombre_de_carte == (plateau->hauteur*plateau->largeur/*-1*/))
    {
      printf("Placement de la premiere carte\n");
      plateau->tab[position_case.x][position_case.y] = tabCarte+carte;
      (tabCarte+carte)->sur_plateau = 1;
      affichage(plateau);
      return backtrack(plateau,tabCarte,nombre_de_carte-1,ind_chemin+1,choix);
      /*Identifiant premiere carte posée sur le plateau*/
      if (choix == 1)
	{
	  printf("Identifiant: %d\n",plateau->tab[1][1]->identifiant);
	}
      else if (choix == 2)
	{
	  printf("Identifiant: %d\n",plateau->tab[0][0]->identifiant);
	}

    }

  if (nombre_de_carte == 0)
    {
      nombre_de_solution++; /*Incrementation du nombre de solutions*/
      printf("\n#== Solution(s) Trouvée(s) : %d ==#\n",nombre_de_solution);
      affichage (plateau); /*affichage de la solution*/
      
      /*Reinitialisation du tableau de carte*/
      for (carte = 0; carte < (plateau->largeur*plateau->hauteur); carte++)
	{
	  tabCarte[carte].sur_plateau = 0;
	}
      return -1;
    }
  
  printf("Position case : x=%d ET y=%d\n",position_case.x,position_case.y);
  printf("Nombre de cartes : %d\n",nombre_de_carte);
  printf("Nombre de solutions : %d\n",nombre_de_solution);
  
  /*DBG*/;
  printf("\n");
  /*sleep(1)*/; /*On fait un sleep de 1 seconde pour mieux voir l' execution de l'Algorithme*/

  for (carte = 0; carte < (plateau->largeur*plateau->hauteur); carte++)
    {
      printf("#== Position courante : %d;%d ==#\n", position_case.x, position_case.y);
      /*DBG*/;
      printf("%d) Sur plateau : %d \n",carte+1,tabCarte[carte].sur_plateau);
      int_carte_possible = cartePossible(tabCarte+carte,plateau, position_case.x,position_case.y);
      printf("#=====================   CARTE POSSIBLE : %d \n", int_carte_possible);
           
      if ( (tabCarte[carte].sur_plateau != 1) /*&& int_carte_possible*/ &&(cartePossible(tabCarte+carte,plateau, position_case.x,position_case.y) == 1) )
	{
	  /*DBG*/;
	  printf("************************************\n");

	  tabCarte[carte].sur_plateau = 1;/*On dit qu'elle est sur le plateau*/
	  plateau->tab[position_case.x][position_case.y] = tabCarte+carte; /*Position de la carte a la position courante*/
	  /*  printf("tabcarte: %d\nplateau->tab: %d\n", tabCarte[carte].identifiant, plateau->tab[position_case.x][position_case.y]->identifiant); */ nombre_de_carte--;
	  /*plateau->tab->position_case.y = tabCarte[carte];*/
	  /*tabCarte[carte].y = position_case.y; idem */
	    
	  /*DBG*/;

	  if ( backtrack(plateau,tabCarte,nombre_de_carte,ind_chemin+1,choix) )
	    {
	      /*DBG*/;
	      return TRUE;
	    }
	  else
	    {
	      /*DBG*/;
	      printf("suppression de la carte %d a la position %d;%d\n", plateau->tab[position_case.x][position_case.y]->identifiant, position_case.x, position_case.y);
	      plateau->tab[position_case.x][position_case.y]->sur_plateau = 0;
	      plateau->tab[position_case.x][position_case.y]->rotated = 4;
	      plateau->tab[position_case.x][position_case.y] = NULL; /*reinitialisation des valeurs fausses*/
	      /*      tabCarte[carte].sur_plateau = 0; */
	      /*on l'enleve du plateau*/
	      /*      tabCarte[carte].rotated = 4; */
	      /*reinitialisation de la rotation de la carte a zero*/
	      nombre_de_carte++;
	    }
	}
    }

  DBG;
  /*  affichage(plateau);*/
  return FALSE;
}
