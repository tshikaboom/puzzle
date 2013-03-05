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

int backtrack (Plateau *plateau ,Carte tabCarte[], int nombre_de_carte,int indice_chemin,int choix)
{
  int nombre_de_solution;
  int carte=0; /*numero de la carte -> identifiant de la carte*/
  Position position_case; /*position de la case courante*/

  /*DBG*/;
  printf("\n");

  /*indice_chemin doit etre egal a -1 au depart sinon la fonction chemin ne donnera pas le bon chemin*/
  position_case = chemin(indice_chemin,choix);
  nombre_de_solution = 0;

  /*DBG*/;
  
  /*Placement de la premiere carte sur le plateau*/
  if (nombre_de_carte == (TAILLE*TAILLE/*-1*/))
    {
      printf("Placement de la premiere carte\n");
      plateau->tab[position_case.x][position_case.y] = tabCarte+carte;
      
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
      
      /*Affichage des valeurs des pointeurs sur les cartes*/
      /*printf("%p\n", plateau->tab[0][0]);
      printf("%p\n", plateau->tab[0][1]);
      printf("%p\n", plateau->tab[0][2]);
      printf("%p\n", plateau->tab[1][0]);
      printf("%p\n", plateau->tab[1][1]);
      printf("%p\n", plateau->tab[1][2]);
      printf("%p\n", plateau->tab[2][0]);
      printf("%p\n", plateau->tab[2][1]);
      printf("%p\n", plateau->tab[2][2]);*/
      
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
  sleep(1); /*On fait un sleep de 1 seconde pour mieux voir l' execution de l'Algorithme*/
  
  for (carte = 0; carte < (plateau->largeur*plateau->hauteur); carte++)
    {
      /*DBG*/;
      printf("%d) Sur plateau : %d \n",carte,tabCarte[carte].sur_plateau);
           
      if ( (tabCarte[carte].sur_plateau != 1) /*&& (cartePossible(tabCarte+carte,plateau, position_case.x,position_case.y))*/ )
	{
	  /*DBG*/;
	  printf("************************************\n");
	    
	  tabCarte[carte].sur_plateau = 1;/*On dit qu'elle est sur le plateau*/
	  plateau->tab[position_case.x][position_case.y] = tabCarte+carte; /*Position de la carte a la position courante*/
	  /*plateau->tab->position_case.y = tabCarte[carte];*/
	  /*tabCarte[carte].y = position_case.y; idem */
	    
	  /*DBG*/;
	    
	  if ( backtrack(plateau,tabCarte,nombre_de_carte-1,indice_chemin+1,choix) )
	    {
	      /*DBG*/;
	      return TRUE;
	    }

	  /*DBG*/;
	    
	  plateau->tab[position_case.x][position_case.y] = NULL; /*reinitialisation des valeurs fausses*/
	  tabCarte[carte].sur_plateau = 0; /*on l'enleve du plateau*/
	  tabCarte[carte].rotated = 4;/*reinitialisation de la rotation de la carte a zero*/
	  nombre_de_carte++;    
	}
    }

  /*DBG*/;
  
  return FALSE;
}
