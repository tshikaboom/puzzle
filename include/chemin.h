#ifndef _NVCHEMIN_H_
#define _NVCHEMIN_H_

#define _POSIX_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "init.h"
#include "contact.h"

/* initialisation d'une liste chainee */
Chemin* nouveauChemin(int x, int y);

/* rajout d'un element dans la liste */
Chemin* ajouteChemin(Chemin *liste, int x, int y);

/* minimum entre deux nombres */
int min(int a,int b);

/* valeur absoluee d'un nombre */
int abs(int n);

/* accesseur des coordonnees de la premiere cellule de la liste */
Position get_pos(Chemin *chemin);

/* affichage minimaliste d'un chemin en (x, y) */
void print_chemin(Chemin *chemin);

/* Fonctions creant les chemins pour un plateau de taille arbitraire
   Retournent une liste avec les coordonnees necessaires */
Chemin* constCheminEnS(int n,int p);
Chemin* constCheminSpirale(int n, int p);
Chemin* constCompCheminSpirale(int n, int p);

Chemin* constCheminSpiraleDec(Chemin* chemin,int n, int p, int xOff, int yOff);

#endif
