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

int suivant (int largeur, int hauteur, Carte *plateau[][], Position courante)
{
  if ((courante.x+1 < largeur) && (plateau[courante.x+1][courante.y] == NULL)) // on teste à droite
    return 1; // case libre à droite
  if ((courante.y+1 < hauteur) && (plateau[courante.x][courante.y+1] == NULL)) // on teste en bas
    return 2; // case libre en bas
  if ((courante.x-1 >= 0) && (plateau[courante.x-1][courante.y] == NULL)) // on teste à gauche
    return 3; // case libre à gauche
  if ((courante.y-1 >= 0) && (plateau[courante.x][courante.y-1] == NULL)) // on teste en haut
    return 4; // case libre en haut
  else
    return 0; // rien de libre trouvé
}

void rotation (Carte *carte, unsigned int nombre)
{
  int i, swap;
  carte->rotated = carte->rotated + nombre;

  for (i = 0; i < nombre; i++) {
    swap = carte->Haut;
    carte->Haut = carte->Gauche;
    carte->Gauche = carte->Bas;
    carte->Bas = carte->Droite;
    carte->Droite = swap;
  }
  if (carte->rotated == 4) carte->rotated = 0; /*On a tout testé !!*/
}
      
void affichage(Carte *plateau[][TAILLE], int largeur, int hauteur)
{
  printf("+---++---++---+\n");
  printf("| %d || %d || %d |\n", plateau[0][0]->Haut, plateau[1][0]->Haut, plateau[2][0]->Haut);
  printf("|%d%d%d||%d%d%d||%d%d%d|\n", plateau[0][0]->Gauche, plateau[0][0]->identifiant, plateau[0][0]->Droite, plateau[1][0]->Gauche, plateau[1][0]->identifiant,   plateau[1][0]->Droite, plateau[2][0]->Gauche, plateau[2][0]->identifiant,  plateau[2][0]->Droite);
  printf("| %d || %d || %d |\n", plateau[0][0]->Bas, plateau[1][0]->Bas, plateau[2][0]->Bas);
  printf("+---++---++---+\n");
  printf("+---++---++---+\n");  
  printf("| %d || %d || %d |\n",  plateau[0][1]->Haut, plateau[1][1]->Haut, plateau[2][1]->Haut);
  printf("|%d %d||%d %d||%d %d|\n",  plateau[0][1]->Gauche, plateau[0][1]->Droite, plateau[1][1]->Gauche, plateau[1][1]->Droite, plateau[2][1]->Gauche, plateau[2][1]->Droite);
  printf("| %d || %d || %d |\n",  plateau[0][1]->Bas, plateau[1][1]->Bas, plateau[2][1]->Bas);
  printf("+---++---++---+\n");
  printf("+---++---++---+\n");
  printf("| %d || %d || %d |\n",   plateau[0][2]->Haut, plateau[1][2]->Haut, plateau[2][2]->Haut);
  printf("|%d %d||%d %d||%d %d|\n", plateau[0][2]->Gauche, plateau[0][2]->Droite, plateau[1][2]->Gauche, plateau[1][2]->Droite, plateau[2][2]->Gauche, plateau[2][2]->Droite);
  printf("| %d || %d || %d |\n",  plateau[0][2]->Bas, plateau[1][2]->Bas, plateau[2][2]->Bas);
  printf("+---++---++---+\n");
}
