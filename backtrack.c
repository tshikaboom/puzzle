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
  int carte; /*numero de la carte*/
  Position position_case; /*position de la case courante*/
  
  /*indice_chemin doit etre egal a -1 au depart sinon la fonction chemin ne donnera pas le bon chemin*/
  position_case = chemin(indice_chemin,choix);
  nombre_de_solution = 0;
  
  if (nombre_de_carte == 0)
    {
      nombre_de_solution++; /*Incrementation du nombre de solutions*/
      affichage (plateau[][TAILLE],largeur,hauteur); /*affichage de la solution*/
      
      /* position_case = caseDepart(largeur,hauteur);               Placement optimal -> On le fera dans le main pour permettre a backtrack d'etre plus libre !!*/
      position_case = chemin(-1,choix); /*retourne a la position initiale*/
      
      if ( (plateau->tab[position_case.x][position_case.y] == ((plateau->largeur*plateau->hauteur)-1)) && (tabCarte[(plateau->largeur*plateau->hauteur)-1].rotated == 4) )
	return TRUE;
    }

  for (carte = 0; carte < (plateau->largeur*plateau->hauteur); carte++)
    {
      if ( (tabCarte[carte].sur_plateau != 1) && (cartePossible(tabCarte[carte],plateau, position_case.x,position_case.y)) )
	{
	  tabCarte[carte].sur_plateau = 1;/*On dit qu'elle est sur le plateau*/
	  tabCarte[carte].x = position_case.x; /*Position de la carte a la position courante*/
	  tabCarte[carte].y = position_case.y; /* idem */

	  if ( backtrack(plateau,tabCarte[],nombre_de_carte-1,indice_chemin+1,choix) )
	    {
	      return TRUE;
	    }

	  plateau->tab[position_case.x][position_case.y] = NULL; /*reinitialisation des valeurs fausses*/
	  tabCarte[carte].sur_plateau = 0; /*on l'enleve du plateau*/
	  tabCarte[carte].rotated = 4;/*reinitialisation de la rotation de la carte a zero*/
	  nombre_de_carte++;	    
	}
    }
  return FALSE;
}
