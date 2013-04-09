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
  if (j-1 < 0)
    return 1;
  else
    if (plateau->tab[i][j-1] == NULL)
      return 1;
    else
      if (Carte.Haut == plateau->tab[i][j-1]->Bas)
	return 1;
      else
	return 0;
}


/* La carte de droite est sur le plateau
   La carte de gauche est donnee en argument
   i et j correspondent a l'endroit ou l'on voudrait mettre notre carte
   donc on teste la carte qui est a droite par rapport a nous sur le plateau
   donc on teste la correspondance Carte(Droite) == plateau[i+1][j](Gauche)
*/
int contact_d(Plateau *plateau, int i, int j, Carte Carte)
{
  if (i+1 > plateau->largeur-1)
    return 1;
  else
    if (plateau->tab[i+1][j] == NULL)
      return 1;
    else
      if (Carte.Droite == plateau->tab[i+1][j]->Gauche)
	return 1;
      else
	return 0;
}


/* La carte du bas est sur le plateau
   La carte du haut est donnee en argument
   i et j correspondent a l'endroit ou l'on voudrait mettre notre carte
   donc on teste la carte qui est en bas par rapport a nous sur le plateau
   donc on teste la correspondance Carte(Bas) == plateau[i][j+1](Haut)
*/
int contact_b(Plateau *plateau, int i, int j, Carte Carte)
{
  /*DBG*/;
  if (j+1 > plateau->hauteur-1)
    return 1;
  else
    if (plateau->tab[i][j+1] == NULL)
      return 1;
    else
      if (Carte.Bas==plateau->tab[i][j+1]->Haut)
	return 1;
      else
	return 0;
}


/* La carte de gauche est sur le plateau
   La carte de droite est donnee en argument
   i et j correspondent a l'endroit ou l'on voudrait mettre notre carte
   donc on teste la carte qui est en bas par rapport a nous sur le plateau
   donc on teste la correspondance Carte(Gauche) == plateau[i-1][j](Droite)
*/
int contact_g(Plateau *plateau, int i, int j, Carte Carte)
{

  if (i-1 < 0)
    return 1;
  else
    if (plateau->tab[i-1][j] == NULL)
      return 1;
    else
      if (Carte.Gauche==plateau->tab[i-1][j]->Droite)
	return 1;
      else
	return 0;
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
  if ((contact_h(plateau,i,j, *carte) &&
       contact_d(plateau,i,j, *carte) &&
       contact_b(plateau,i,j, *carte) &&
       contact_g(plateau,i,j, *carte))) {

    printf("=> Placement Possible\n");
    return 1;
  }

  
  /* le else est ici */
  rotation(carte,1);

  /* si on a fait un tour complet alors la carte n'est pas valide */
  /* dans notre cas, la variable rotated 4 == 0, la difference etant que
     l'on sait si la carte a ete tournee (4) ou pas (0) */
  if (carte->rotated == 4) return 0;

  return cartePossible(carte, plateau, i, j);
}
