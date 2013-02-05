#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "struct.h"
#include "init.h"
#include "contact.h"


int contact_h(Carte *plateau[][],int i , int j )
{
  int estEnContact;
  int peutSePlacer;

  peutSePlacer = 0;

  if((plateau[i-1][j])==NULL) /*Si la case en haut est vide */
    estEnContact=0;
  else if((i-1)<0) /* Si la case en haut n'existe pas , 1ere ligne du tableau */
    estEnContact=0
    else
      estEnContact=1;
  
  
  if (estEnContact==1)
    {
      if (Carte.Haut==plateau[i-1][j]->Bas)
	peutSePlacer=1;
      else
	peutSePlacer=0;
    }

  return peutSePlacer;
}
    

int contact_d(Carte *plateau[][],int i , int j, int largeur  )
{
  int estEnContact;
  int peutSePlacer;

  peutSePlacer = 0;

  if((plateau[i][j+1])==NULL) /*Si la case à droite est vide  */
    estEnContact=0;
  else  if((j+1)>largeur-1) /*Si la case à droite n 'existe pas, dernière colonne du tableau*/
    estEnContact=0
      else
	estEnContact=1;

  if (estEnContact==1)
    {
      if (Carte.Droite==plateau[i-1][j]->Gauche)
	peutSePlacer=1;
      else
	peutSePlacer=0;
    }

  return peutSePlacer;
}


int contact_b(Carte *plateau[][],int i , int j, int hauteur)
{
  int estEnContact;
  int peutSePlacer;

  peutSePlacer = 0;

  if((plateau[i+1][j])==NULL) /* Si la case en bas est vide*/
    estEnContact=0; 
  else if((i+1)>hauteur-1) /* Si la case en bas n' existe pas , dernière ligne du tableau*/
    estEnContact=0;
    else
      estEnContact=1;
  
if (estEnContact==1)
    {
      if (Carte.Bas==plateau[i-1][j]->Haut)
	peutSePlacer=1;
      else
	peutSePlacer=0;
    }

  return peutSePlacer;
}


int contact_g(Carte *plateau[][],int i, int j )
{
  int estEnContact;
  int peutSePlacer;

  peutSePlacer = 0;

  if((plateau[i][j-1])==NULL) /*Si la case à gauche est vide */
    estEnContact=0;
  else
    if((j-1)<0)) /*Si la cas à gauche n'exite pas , première colonne du tableau*/
    estEnContact=0;
    else 
      estEnContact=1;

if (estEnContact==1)
    {
      if (Carte.Gauche==plateau[i-1][j]->Droite)
	peutSePlacer=1;
      else
	peutSePlacer=0;
    }

  return peutSePlacer;
}


int cartePossible(Carte *carte, carte *plateau[][],int i , int j, int largeur, int hauteur)
{
  /*  int placementPossible;
  placementPossible=0;

  if( )
    placementPossible=1;
  */
  return (contact_h(plateau[][],i,j,carte) && contact_d(plateau[][],i,j,largeur,carte) && contact_b(plateau[][],i,j,hauteur,carte) && contact_g(plateau[][],i,j,carte))
}

