#define _POSIX_SOURCE 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "init.h"
#include "contact.h"

/* La carte du haut est sur le plateau
   La carte du bas est donnee en argument
   i et j correspondent a l'endroit ou l'on voudrait mettre notre carte
   donc on teste la carte qui est en haut par rapport a nous sur le plateau
   donc on teste la correspondance Carte(Haut) == plateau[i][j-1](Bas)
*/
int contact_h(Plateau *plateau, int i, int j, Carte Carte)
{
  int estEnContact;
  int peutSePlacer = 0;

  if (j-1 < 0) /* Si la case en haut n'existe pas , 1ere ligne du tableau */
    estEnContact=0;
  else if (plateau->tab[i][j-1] == NULL) /*Si la case en haut est vide */
    estEnContact=0;
  else
    estEnContact=1;
  
  
  if (estEnContact) {
    if (Carte.Haut == plateau->tab[i][j-1]->Bas)
      peutSePlacer=1;
    else
      peutSePlacer=0;
  }
  
  return peutSePlacer;
}

/* La carte de droite est sur le plateau
   La carte de gauche est donnee en argument
   i et j correspondent a l'endroit ou l'on voudrait mettre notre carte
   donc on teste la carte qui est a droite par rapport a nous sur le plateau
   donc on teste la correspondance Carte(Droite) == plateau[i+1][j](Gauche)
*/
int contact_d(Plateau *plateau, int i, int j, Carte Carte)
{
  int estEnContact;
  int peutSePlacer = 0;
  
  if (i+1 > (plateau->largeur) - 1) /*Si la case à droite n'existe pas, derniere colonne du tableau*/
    estEnContact=0;
  else if ((plateau->tab[i+1][j]) == NULL) /*Si la case à droite est vide  */
    estEnContact=0;
  else
    estEnContact=1;

  if (estEnContact) {
    if (Carte.Droite == plateau->tab[i+1][j]->Gauche)
      peutSePlacer=1;
    else
      peutSePlacer=0;
  }
  
  return peutSePlacer;
}

/* La carte du bas est sur le plateau
   La carte du haut est donnee en argument
   i et j correspondent a l'endroit ou l'on voudrait mettre notre carte
   donc on teste la carte qui est en bas par rapport a nous sur le plateau
   donc on teste la correspondance Carte(Bas) == plateau[i][j+1](Haut)
*/
int contact_b(Plateau *plateau, int i, int j, Carte Carte)
{
  int estEnContact;
  int peutSePlacer;

  peutSePlacer = 0;

  if (j+1 > plateau->hauteur-1) /* Si la case en bas n' existe pas , dernière ligne du tableau*/
    estEnContact=0; 
  else  if ((plateau->tab[i][j+1])==NULL) /* Si la case en bas est vide*/
    estEnContact=0;
  else
    estEnContact=1;
  
  if (estEnContact==1) {
    if (Carte.Bas==plateau->tab[i][j+1]->Haut)
      peutSePlacer=1;
    else
      peutSePlacer=0;
  }
  
  return peutSePlacer;
}

/* La carte de gauche est sur le plateau
   La carte de droite est donnee en argument
   i et j correspondent a l'endroit ou l'on voudrait mettre notre carte
   donc on teste la carte qui est en bas par rapport a nous sur le plateau
   donc on teste la correspondance Carte(Gauche) == plateau[i-1][j](Droite)
*/
int contact_g(Plateau *plateau,int i, int j, Carte Carte)
{
  int estEnContact;
  int peutSePlacer;

  peutSePlacer = 0;
  
  if (j-1 < 0) /*Si la cas à gauche n'exite pas , première colonne du tableau*/
    estEnContact=0;
  else  if ((plateau->tab[i][j-1]) == NULL) /*Si la case à gauche est vide */
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

/* fonction recursive
   on teste s'il y a possibilite de placement de carte dans une position autour d'elle-meme
   retourne 1 si possible
   sinon fait rotation sur la carte et se rappelle
   max nombre d'appels sur une carte+position donnees: 4
 */
int cartePossible(Carte *carte,Plateau *plateau,int i , int j)
{

  /* Si la carte courante ne correspond pas avec ses voisines alors on fait une rotation : si pas vrai alors on rentre dans le if */

  printf("cartePossible: rotation courante %d sur la carte %d\n", carte->rotated,carte->identifiant);
  /* test si le placement de la carte est possible */
  if ((contact_h(plateau,i,j, *carte) ||
       contact_d(plateau,i,j, *carte) ||
       contact_b(plateau,i,j, *carte) ||
       contact_g(plateau,i,j, *carte)))
    return 1;
  else {
    rotation(carte,1);
    DBG;
    /* si on a fait un tour complet alors la carte n'est pas valide */
    if (carte->rotated == 4) return 0;

    return cartePossible(carte, plateau, i, j);
    
    /*return 0; */

    DBG;
    /*
      return cartePossible(carte,plateau,i,j);
    */
      
  }


  DBG;
  
  return 1;
}
