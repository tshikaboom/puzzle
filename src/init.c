#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "init.h"

Position caseDepart (int largeur, int hauteur)
{
  Position pos;
  if (largeur % 2) /*Cas Impair*/
    pos.x = largeur/2+1;
  else
    pos.x = largeur/2;

  if (hauteur % 2) /*Cas Impair*/
    pos.y = hauteur/2+1;
  else
    pos.y = hauteur/2;

  return pos;
}

int suivant (Plateau *plateau, Position courante)
{
  if ((courante.x+1 < plateau->largeur) && (plateau->tab[courante.x+1][courante.y] == NULL)) /* on teste a droite */
    return 1; /* case libre a droite */
  if ((courante.y+1 < plateau->hauteur) && (plateau->tab[courante.x][courante.y+1] == NULL)) /* on teste en bas */
    return 2; /* case libre en bas */
  if ((courante.x-1 >= 0) && (plateau->tab[courante.x-1][courante.y] == NULL)) /* on teste a gauche */
    return 3; /* case libre a gauche */
  if ((courante.y-1 >= 0) && (plateau->tab[courante.x][courante.y-1] == NULL)) /* on teste en haut */
    return 4; /* case libre en haut */
  else
    return 0; /* rien de libre trouve */
}

void rotation (Carte *carte, unsigned int nombre)
{
  unsigned int i, swap;
  carte->rotated = carte->rotated + nombre;

  for (i = 0; i < nombre; i++) {
    swap = carte->Haut;
    carte->Haut = carte->Gauche;
    carte->Gauche = carte->Bas;
    carte->Bas = carte->Droite;
    carte->Droite = swap;
    DBG;
    if (carte->rotated == 4) {carte->rotated = 0;printf("SORTIE : %d \n",carte->identifiant);break;}
  }
  /*if (carte->rotated == 4) carte->rotated = 0;*/
  printf("ROTATION : %d\n",carte->rotated);
}
      
void affichage(Plateau *plateau)
{
  printf("+---++---++---+\n");
  printf("| %d || %d || %d |\n", plateau->tab[0][0]->Haut, plateau->tab[1][0]->Haut, plateau->tab[2][0]->Haut);
  printf("|%d%d%d||%d%d%d||%d%d%d|\n", plateau->tab[0][0]->Gauche, plateau->tab[0][0]->identifiant, plateau->tab[0][0]->Droite, plateau->tab[1][0]->Gauche, plateau->tab[1][0]->identifiant,   plateau->tab[1][0]->Droite, plateau->tab[2][0]->Gauche, plateau->tab[2][0]->identifiant,  plateau->tab[2][0]->Droite);
  printf("| %d || %d || %d |\n", plateau->tab[0][0]->Bas, plateau->tab[1][0]->Bas, plateau->tab[2][0]->Bas);
  printf("+---++---++---+\n");
  printf("+---++---++---+\n");  
  printf("| %d || %d || %d |\n",  plateau->tab[0][1]->Haut, plateau->tab[1][1]->Haut, plateau->tab[2][1]->Haut);
  printf("|%d %d||%d %d||%d %d|\n",  plateau->tab[0][1]->Gauche, plateau->tab[0][1]->Droite, plateau->tab[1][1]->Gauche, plateau->tab[1][1]->Droite, plateau->tab[2][1]->Gauche, plateau->tab[2][1]->Droite);
  printf("| %d || %d || %d |\n",  plateau->tab[0][1]->Bas, plateau->tab[1][1]->Bas, plateau->tab[2][1]->Bas);
  printf("+---++---++---+\n");
  printf("+---++---++---+\n");
  printf("| %d || %d || %d |\n",   plateau->tab[0][2]->Haut, plateau->tab[1][2]->Haut, plateau->tab[2][2]->Haut);
  printf("|%d %d||%d %d||%d %d|\n", plateau->tab[0][2]->Gauche, plateau->tab[0][2]->Droite, plateau->tab[1][2]->Gauche, plateau->tab[1][2]->Droite, plateau->tab[2][2]->Gauche, plateau->tab[2][2]->Droite);
  printf("| %d || %d || %d |\n",  plateau->tab[0][2]->Bas, plateau->tab[1][2]->Bas, plateau->tab[2][2]->Bas);
  printf("+---++---++---+\n");
}
