#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "init.h"
#include "contact.h"
#include "chemin.h"
#include "backtrack.h"



#define TRUE 1 /*SI VRAI*/
#define FALSE 0 /*SI FAUX*/

/*Algorithme de backtracking*/
/*
  int backtrack (Carte *plateau[][TAILLE],Carte tabCarte[], int largeur, int hauteur, int nombre_de_carte,int indice_chemin,int choix)
*/
int backtrack (Plateau *plateau ,Carte tabCarte[], int nombre_de_carte,int indice_chemin,int choix)
{
  int nombre_de_solution;
  int carte=0; /*numero de la carte*/
  Position position_case; /*position de la case courante*/

  DBG;
  
  /*indice_chemin doit etre egal a -1 au depart sinon la fonction chemin ne donnera pas le bon chemin*/
  position_case = chemin(indice_chemin,choix);
  nombre_de_solution = 0;

  printf("Position case : x=%d ET y=%d\n",position_case.x,position_case.y);
  printf("Nombre de carte : %d\n",nombre_de_carte);
  printf("Nombre de solution : %d\n",nombre_de_solution);
  DBG;

  /*Placement de la premiere carte sur le plateau*/
  if (nombre_de_carte == 8)
    {
      printf("Placement de la premiere carte\n");
      plateau->tab[position_case.x][position_case.y] = tabCarte+carte;
      printf("Identifiant: %d\n",plateau->tab[1][1]->identifiant);
      /*sleep(1)*/;
    }
  
  if (nombre_de_carte == 0)
    {
      nombre_de_solution++; /*Incrementation du nombre de solutions*/
      printf("#== Nombre de solution : %d ==#\n",nombre_de_solution);
      printf("%p\n", plateau->tab[0][0]);
      printf("%p\n", plateau->tab[0][1]);
      printf("%p\n", plateau->tab[0][2]);
      printf("%p\n", plateau->tab[1][0]);
      printf("%p\n", plateau->tab[1][1]);
      printf("%p\n", plateau->tab[1][2]);
      printf("%p\n", plateau->tab[2][0]);
      printf("%p\n", plateau->tab[2][1]);
      printf("%p\n", plateau->tab[2][2]);
      affichage (plateau); /*affichage de la solution*/
      
      /* position_case = caseDepart(largeur,hauteur);               Placement optimal -> On le fera dans le main pour permettre a backtrack d'etre plus libre !!*/
      printf("**********************************************************\n");
      position_case = chemin(-1,choix); /*retourne a la position initiale*/
      sleep (2);
      
      if ( (plateau->tab[position_case.x][position_case.y] == NULL) /*((plateau->largeur*plateau->hauteur)-1))*/ && (tabCarte[(plateau->largeur*plateau->hauteur)-1].rotated == 4) )
	return TRUE;
    }
  
  DBG;
  printf("*******************************\n");
  sleep(1);
  
  for (carte = 0; carte < (plateau->largeur*plateau->hauteur); carte++)
    {
      DBG;
      printf("****************\n");
      /*sleep(1)*/;
  
      printf("%d) Sur plateau : %d\n",carte,tabCarte[carte].sur_plateau);
      /*sleep(1)*/;
      
      if ( (tabCarte[carte].sur_plateau != 1) /*&& (cartePossible(tabCarte+carte,plateau, position_case.x,position_case.y))*/ )
	{
	  DBG;
	  printf("************************************\n");
	  /*sleep(1)*/;
  
	  tabCarte[carte].sur_plateau = 1;/*On dit qu'elle est sur le plateau*/
	  plateau->tab[position_case.x][position_case.y] = tabCarte+carte; /*Position de la carte a la position courante*/
	  /*plateau->tab->position_case.y = tabCarte[carte];*/
	  /*tabCarte[carte].y = position_case.y; idem */
	  printf("************************************\n");
	  /*sleep(1)*/;
  
	  DBG;
	  
	  if ( backtrack(plateau,tabCarte,nombre_de_carte-1,indice_chemin+1,choix) )
	    {
	      DBG;
	      return TRUE;
	    }

	  DBG;
	  
	  plateau->tab[position_case.x][position_case.y] = NULL; /*reinitialisation des valeurs fausses*/
	  tabCarte[carte].sur_plateau = 0; /*on l'enleve du plateau*/
	  tabCarte[carte].rotated = 4;/*reinitialisation de la rotation de la carte a zero*/
	  nombre_de_carte++;	    
	}
    }

  DBG;
  
  return FALSE;
}
