#define _POSIX_SOURCE 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "init.h"
#include "contact.h"



int contact_h(Plateau *plateau,int i , int j, Carte Carte)
{
  int estEnContact;
  int peutSePlacer;

  peutSePlacer = 0;

  if((plateau->tab[i-1][j]) == NULL) /*Si la case en haut est vide */
    estEnContact=0;
  else if((i-1)<0) /* Si la case en haut n'existe pas , 1ere ligne du tableau */
    estEnContact=0;
  else
    estEnContact=1;
  
  
  if (estEnContact==1) {
    if (Carte.Haut==plateau->tab[i-1][j]->Bas)
      peutSePlacer=1;
    else
      peutSePlacer=0;
  }
  
  return peutSePlacer;
}

int contact_d(Plateau *plateau,int i , int j, Carte Carte)
{
  int estEnContact;
  int peutSePlacer;
  
  peutSePlacer = 0;

  if((plateau->tab[i][j+1])==NULL) /*Si la case à droite est vide  */
    estEnContact=0;
  else  if(j+1 > (plateau->largeur)-1) /*Si la case à droite n 'existe pas, dernière colonne du tableau*/
    estEnContact=0;
  else
    estEnContact=1;

  if (estEnContact==1) {
    if (Carte.Droite == plateau->tab[i-1][j]->Gauche)
      peutSePlacer=1;
    else
      peutSePlacer=0;
  }
  
  return peutSePlacer;
}


int contact_b(Plateau *plateau,int i , int j, Carte Carte)
{
  int estEnContact;
  int peutSePlacer;

  peutSePlacer = 0;

  if ((plateau->tab[i+1][j])==NULL) /* Si la case en bas est vide*/
    estEnContact=0; 
  else if (i+1 > plateau->hauteur-1) /* Si la case en bas n' existe pas , dernière ligne du tableau*/
    estEnContact=0;
  else
    estEnContact=1;
  
  if (estEnContact==1) {
    if (Carte.Bas==plateau->tab[i-1][j]->Haut)
      peutSePlacer=1;
    else
      peutSePlacer=0;
  }
  
  return peutSePlacer;
}


int contact_g(Plateau *plateau,int i, int j, Carte Carte)
{
  int estEnContact;
  int peutSePlacer;

  peutSePlacer = 0;

  if ((plateau->tab[i][j-1]) == NULL) /*Si la case à gauche est vide */
    estEnContact=0;
  else
    if (j-1 < 0) /*Si la cas à gauche n'exite pas , première colonne du tableau*/
      estEnContact=0;
    else
      estEnContact=1;
  
  if (estEnContact == 1) {
    if (Carte.Gauche==plateau->tab[i-1][j]->Droite)
      peutSePlacer=1;
    else
      peutSePlacer=0;
  }
  
  return peutSePlacer;
}


int cartePossible(Carte *carte,Plateau *plateau,int i , int j)
{
  /*int ret; */
  /* Si la carte courante ne correspond pas avec ses voisines alors on fait une rotation : si pas vrai alors on rentre dans le if */
  while (!(contact_h(plateau,i,j, *carte) ||
	   contact_d(plateau,i,j, *carte) ||
	   contact_b(plateau,i,j, *carte) ||
	   contact_g(plateau,i,j, *carte))) {
    printf("cartePossible: rotation courante %d (num carte : %d)\n", carte->rotated,carte->identifiant);
    rotation(carte,1);
    DBG;
    /* si on a fait un tour complet alors la carte n'est pas valide */
    if (carte->rotated == 4) break;
      
    /*return 0; */

    DBG;
    /*
      return cartePossible(carte,plateau,i,j);
    */
      
  }
  if (carte->rotated == 4) return 0;

  DBG;
  
  return 1;
}
