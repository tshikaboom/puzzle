#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "init.h"

Position caseDepart (int largeur, int hauteur)
{
  Position pos;
  if (largeur % 2) /* largeur du plateau impair? */
    pos.x = largeur/2+1;
  else
    pos.x = largeur/2;

  if (hauteur % 2) /* hauteur du plateau impair? */
    pos.y = hauteur/2+1;
  else
    pos.y = hauteur/2;

  return pos;
}

int suivant (Plateau *plateau, Position courante)
{
  if ((courante.x+1 < plateau->largeur) &&
      (plateau->tab[courante.x+1][courante.y] == NULL)) /* on teste a droite */
    return 1; /* case libre a droite */
  if ((courante.y+1 < plateau->hauteur) &&
      (plateau->tab[courante.x][courante.y+1] == NULL)) /* on teste en bas */
    return 2; /* case libre en bas */
  if ((courante.x-1 >= 0) &&
      (plateau->tab[courante.x-1][courante.y] == NULL)) /* on teste a gauche */
    return 3; /* case libre a gauche */
  if ((courante.y-1 >= 0) &&
      (plateau->tab[courante.x][courante.y-1] == NULL)) /* on teste en haut */
    return 4; /* case libre en haut */
  else
    return 0; /* rien de libre trouve */
}

void rotation (Carte *carte, unsigned int nombre)
{
  unsigned int i, swap;
  carte->rotated = carte->rotated + nombre;

  /* gros swap pour effectuer la rotation de la carte */
  for (i = 0; i < nombre; i++) {
    swap = carte->Haut;
    carte->Haut = carte->Gauche;
    carte->Gauche = carte->Bas;
    carte->Bas = carte->Droite;
    carte->Droite = swap;

    if (carte->rotated > 4) {
      carte->rotated = carte->rotated-4;
      printf("SORTIE : %d \n",carte->identifiant);
      break;
    }
  }
}

/* Fonction d'affichage du plateau
   Prend juste le plateau en argument et fait des trucs plutot magiques pour l'affichage
*/
void affichage(Plateau *plateau)
{
  int i, j;

  for (j = 0; j < plateau->hauteur; j++) {
    for (i = 0; i < plateau->largeur; i++)
      printf("+---+");
    printf("\n");

    for (i = 0; i < plateau->largeur; i++)
      if (plateau->tab[i][j] == NULL) printf("|   |");
      else printf("| %d |", plateau->tab[i][j]->Haut);
    printf("\n");
    
    for (i = 0; i < plateau->largeur; i++)
      if (plateau->tab[i][j] == NULL) printf("|   |");
      else printf("|%d%d%d|",
		  plateau->tab[i][j]->Gauche,
		  plateau->tab[i][j]->identifiant,
		  plateau->tab[i][j]->Droite);
    printf("\n");
    
    for (i = 0; i < plateau->largeur; i++)
      if (plateau->tab[i][j] == NULL) printf("|   |");
      else printf("| %d |", plateau->tab[i][j]->Bas);
    printf("\n");

    for (i = 0; i < plateau->largeur; i++)
      printf("+---+");
    printf("\n");
  }
}

/* Fonction d'allocation d'un nouveau plateau
   rend un plateau contenant un tableau a 2dim dont les cases sont initialisees a NULL
*/
Plateau *nouveau_plateau(int hauteur, int largeur)
{
  int i, j;
  Plateau *plateau;

  if (hauteur < 1 || largeur < 1) {
    printf("Hauteur ou largeur pas bons! Pas bon signe...\n");
    return NULL;
  }

  printf("Allocation d'un tableau %dx%d\n", largeur, hauteur);
  

  plateau = (Plateau *) malloc(sizeof (Plateau));
  if (plateau == NULL) {
    printf("Allocation du plateau echouee!\n");
    return NULL;
  }

  plateau->tab = (Carte ***) malloc(largeur*sizeof(Carte **));
  if (plateau == NULL) {
    printf("Allocation des abscisses du plateau echouee!\n");
    return NULL;
  }

  for (i=0; i<largeur; i++) {
    plateau->tab[i] = (Carte **) malloc(hauteur*sizeof(Carte *));
    if (plateau->tab[i] == NULL) {
      printf("Allocation des ordonnees d'abscisse %d du plateau echouee!\n", i);
      return NULL;
    }
  }
  
  for (i=0; i<largeur; i++)
    for (j=0; j<hauteur; j++)
      plateau->tab[i][j] = NULL;
  
  plateau->largeur = largeur;
  plateau->hauteur = hauteur;

  return plateau;
}


void swap (Plateau *plateau,Carte tabCarte[])
{
  int i;
  Carte tmp;

  tmp = tabCarte[0]; 
  for (i=0; i<plateau->largeur*plateau->hauteur-1;i++)
    tabCarte[i] = tabCarte[i+1];

  tabCarte[plateau->largeur*plateau->hauteur-1] = tmp;
}
