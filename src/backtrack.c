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

/*
  Algorithme de backtracking
  Auteur: Benjamin Bielle
*/

int backtrack (Plateau *plateau ,Carte tabCarte[],
	       Chemin *parcours,
	       int nombre_de_carte, int quiet, int une_sol)
{
  #ifdef DEBUG
  int i; /* compteur generique */
  #endif
  int nombre_de_solution;
  int carte=0; /*numero de la carte -> identifiant de la carte*/
  Position position_case; /*position de la case courante*/
  int back;

  if (parcours)
    position_case = get_pos(parcours);

  nombre_de_solution = 0;

  /******************************************************************/
  /*Affichage pour verifier que le plateau est vide la premiere fois*/
  /******************************************************************/
  if (quiet==0) {
  system("clear");
  affichage(plateau);
  }
  /******************/
  /*Fin du backtrack*/
  /******************/
  if (nombre_de_carte == 0)
    {
      if (quiet == 0) {
      system("clear");
      }
      nombre_de_solution++; /*Incrementation du nombre de solutions*//*
      printf("\n#== Solution(s) Trouvée(s) : %d ==#\n",nombre_de_solution);
      affichage (plateau); *//*affichage de la solution*/

      /*Reinitialisation du tableau de carte*/
      for (carte = 0; carte < (plateau->largeur*plateau->hauteur); carte++)
	{
	  tabCarte[carte].sur_plateau = 0;
	}
      exporteur_magique(plateau);
      /* used only for benchmarks
	 exit(EXIT_SUCCESS);*/
      if (une_sol) exit(EXIT_SUCCESS);

      clean_plateau(plateau);

      return -1;
    }

  /***********************************************/
  /*Placement de la premiere carte sur le plateau*/
  /***********************************************/
  if (nombre_de_carte == (plateau->hauteur*plateau->largeur))
    {
      #ifdef DEBUG
      printf("-- Liste des cartes traitees\n");
      printf("idCarte\tH B G D\n");
      for (i=0; i<plateau->hauteur*plateau->largeur; i++)
	printf("%d\t%d %d %d %d\n",
	       tabCarte[i].identifiant,
	       tabCarte[i].Haut,
	       tabCarte[i].Bas,
	       tabCarte[i].Gauche,
	       tabCarte[i].Droite);
      #endif

      carte = 0;

      plateau->tab[position_case.x][position_case.y] = tabCarte/*+carte*/;
      (tabCarte+carte)->sur_plateau = 1;
      nombre_de_carte--;
      if (quiet == 0) affichage(plateau);

    }

  /*position a la case suivante*/
  position_case = get_pos(parcours->Suivant);

  /**********************************************************************/
  /* BACKTRACK                                                          */
  /**********************************************************************/

  for (carte = 0; carte < (plateau->largeur*plateau->hauteur) ; carte++)
    {
      /*Si carte n'est pas deja posee*/
      if (tabCarte[carte].sur_plateau == 0)
	{
	  /*Si carte est posable sur le plateau*/
	  if ( cartePossible(tabCarte+carte,plateau, position_case.x,position_case.y) == 1)
	    {
	      /*On dit qu'elle est sur le plateau*/
	      tabCarte[carte].sur_plateau = 1;

	      /*Position de la carte a la position courante*/
	      plateau->tab[position_case.x][position_case.y] = tabCarte+carte;

	      /*Decrementation du nombre de carte*/
	      nombre_de_carte--;

	      /*Appel a backtrack*/
	      back = backtrack(plateau,tabCarte, parcours->Suivant,
			       nombre_de_carte, quiet, une_sol);

	      if ( back )
		{
		  return TRUE;
		}
	      else
		{
		  /*On dit qu'elle n'est pas sur le plateau*/
		  tabCarte[carte].sur_plateau = 0;

		  /*Position courante du plateau mise a NULL*/
		  plateau->tab[position_case.x][position_case.y] = NULL;

		  /*Incrementation du nombre de carte*/
		  nombre_de_carte++;
		}
	    }
	}
    }

  return FALSE;
}
