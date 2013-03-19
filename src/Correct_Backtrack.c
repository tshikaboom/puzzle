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
  int carte; /*numero de la carte -> identifiant de la carte*/
  Position position_case; /*position de la case courante*/
  int int_carte_possible;
  int ind_chemin = indice_chemin;

  int back;
  
  printf("\n");
  printf("#== Debut de backtrack, ndecartes : %d ==#\n", nombre_de_carte);
  
  /***************************************************************************************************/
  /*indice_chemin doit etre egal a -1 au depart sinon la fonction chemin ne donnera pas le bon chemin*/
  /***************************************************************************************************/
  position_case = chemin(indice_chemin,choix);
  nombre_de_solution = 0;
  
  /******************************************************************/
  /*Affichage pour verifier que le plateau est vide la premiere fois*/
  /******************************************************************/
  affichage(plateau);

  /******************/
  /*Fin du backtrack*/
  /******************/
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
  
  /***********************************************/
  /*Placement de la premiere carte sur le plateau*/
  /***********************************************/
  if (nombre_de_carte == (plateau->hauteur*plateau->largeur))
    {
      carte = 0;
      
      printf("#== Placement de la premiere carte ==#\n");
      plateau->tab[position_case.x][position_case.y] = tabCarte+carte;
      (tabCarte+carte)->sur_plateau = 1;
      affichage(plateau);
      
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
    
  printf("Position case : x=%d ET y=%d\n",position_case.x,position_case.y);
  printf("Nombre de cartes : %d\n",nombre_de_carte);
  printf("Nombre de solutions : %d\n\n",nombre_de_solution);
  
  /**********************************************************************/
  /* EN COURS*/
  /**********************************************************************/

  /*On cherche une carte pas sous le plateau*/
  while (tabCarte[carte].sur_plateau == 1 && carte < (plateau->largeur*plateau->hauteur))
    carte++;

  if (cartePossible(tabCarte+carte,plateau, position_case.x,position_case.y) == 1)
    {
      /*On dit qu'elle est sur le plateau*/
      tabCarte[carte].sur_plateau = 1;
      /*Position de la carte a la position courante*/
      plateau->tab[position_case.x][position_case.y] = tabCarte+carte;
      nombre_de_carte--;
      
      /*Appel a backtrack*/
      back = backtrack(plateau,tabCarte,nombre_de_carte,ind_chemin+1,choix);

      if ( back )
	{
	  return TRUE;
	}
      /*gestion des erreurs*/
    }
  /*si impossible*/
  else
    {
      return FALSE;
    }
  
  /**********************************************************************/
  /* A CORRIGER*/
  /**********************************************************************/
  
  printf("suppression de la carte %d a la position %d;%d\n", plateau->tab[position_case.x][position_case.y]->identifiant, position_case.x, position_case.y);
  plateau->tab[position_case.x][position_case.y]->sur_plateau = 0;
  plateau->tab[position_case.x][position_case.y]->rotated = 4;
  plateau->tab[position_case.x][position_case.y] = NULL; /*reinitialisation des valeurs fausses*/
  nombre_de_carte++;
  
  return FALSE;
}
