#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "init.h"
#include "contact.h"
#include "backtrack.h"


/*Algorithme de backtracking*/
void backtrack (Carte *plateau[][],Carte tabCarte[], int largeur, int hauteur, int nombre_de_carte)
{
  int nombre_de_solution;
  int carte;
  Position position_case;
  
  
  nombre_de_solution = 0;
  
  if (nombre_de_carte == 0)
    {
      nombre_de_solution++; /*Incrementation du nombre de solutions*/
      affichage (plateau[][],largeur,hauteur); /*affichage de la solution*/
      
      position_case = caseDepart(largeur,hauteur); /*Placement optimal*/

      if ( (plateau[pos.x][pos.y] == ((largeur*hauteur)-1)) && (tabCarte[(largeur*hauteur)-1].rotated == 4) )
	return TRUE;
    }

  for (carte = 0; carte < (largeur*largeur); carte++)
    {
      if ( (tabCarte[carte].sur_plateau != 0) && (cartePossible()) )

