#define _POSIX_SOURCE 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "init.h"
#include "contact.h"

/* La carte du haut est sur le plateau
   La carte du bas est donnee en argument
   i et j correspondent a l'endroit ou l'on voudrait mettre notre carte, donc
   - on teste la carte qui est en haut par rapport a nous sur le plateau
   - on teste la correspondance Carte(Haut) == plateau[i][j-1](Bas)
*/
int contact_h(Plateau *plateau, int i, int j, Carte Carte)
{
  /* depasse-t-on le plateau? si oui, on peut poser la carte */
  if (j-1 < 0)
    return 1;
  else
    /* le plateau a-t-il une carte en (i, j-1)? Si non, on peut poser la carte */
    if (plateau->tab[i][j-1] == NULL)
      return 1;
    else
      /* le plateau a une carte en haut. Est-ce qu'elle matche avec la carte
	 qu'on veut poser? */
      if (Carte.Haut == plateau->tab[i][j-1]->Bas)
	return 1;
      else
	return 0;
}


/* La carte de droite est sur le plateau
   La carte de gauche est donnee en argument
   i et j correspondent a l'endroit ou l'on voudrait mettre notre carte, donc
   - on teste la carte qui est a droite par rapport a nous sur le plateau
   - on teste la correspondance Carte(Droite) == plateau[i+1][j](Gauche)
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
   i et j correspondent a l'endroit ou l'on voudrait mettre notre carte, donc
   - on teste la carte qui est en bas par rapport a nous sur le plateau
   - on teste la correspondance Carte(Bas) == plateau[i][j+1](Haut)
*/
int contact_b(Plateau *plateau, int i, int j, Carte Carte)
{
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
   i et j correspondent a l'endroit ou l'on voudrait mettre notre carte, donc
   - on teste la carte qui est en bas par rapport a nous sur le plateau
   - on teste la correspondance Carte(Gauche) == plateau[i-1][j](Droite)
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

/* Fonction recursive.
   On teste s'il y a possibilite de placement de carte dans une position autour d'elle-meme
   - retourne 1 si possible
   Sinon fait rotation sur la carte et se rappelle
   Nombre maximum d'appels sur une carte+position donnees: 4
*/
int cartePossible(Carte *carte,Plateau *plateau,int i , int j)
{
  /* test si le placement de la carte est possible */
  if ((contact_h(plateau,i,j, *carte) &&
       contact_d(plateau,i,j, *carte) &&
       contact_b(plateau,i,j, *carte) &&
       contact_g(plateau,i,j, *carte))) {

    return 1;
  }

  
  /* Si la carte courante ne correspond pas avec ses voisines alors on fait une rotation */
  rotation(carte,1);

  /* Si on a fait un tour complet alors la carte n'est pas valide.
     Dans notre cas, la variable rotated 4 == 0, la difference etant que
     l'on sait si la carte a ete tournee (4) ou pas (0). */
  if (carte->rotated == 4) return 0;

  return cartePossible(carte, plateau, i, j);
}
