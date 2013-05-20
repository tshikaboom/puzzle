#ifndef BACKTRACK_H
#define BACKTRACK_H
#include "chemin.h"
#include "structs.h"

/* Algorithme de backtracking */
int backtrack (Plateau *plateau,Carte tabCarte[],
	       Chemin *parcours,
	       long int nombre_de_carte, int quiet, int une_sol);
#endif
