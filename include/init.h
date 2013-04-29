#ifndef INIT_H
#define INIT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

#include "structs.h"


/* Fonction determinant la case de depart pour un parcours en spirale */
Position caseDepart (int largeur, int hauteur);

/* Suivant => case suivant vide ou non */
int suivant (Plateau *plateau, Position courante);

/* Gestion de la rotation: rotation(carte, 1) tourne la carte une fois
   dans le sens des aiguilles d'une montre */
void rotation (Carte *carte,unsigned int nombre);

/* Affichage d'un plateau de taille arbitraire */
void affichage (Plateau *plateau);

/* Allocation d'un nouveau plateau de taille largeur*hauteur.
   La fonction initialise les cases du plateau a NULL. */
Plateau *nouveau_plateau(int hauteur, int largeur);

/* liberation du plateau */
void free_plateau(Plateau *plateau);

/* Echange la liste de carte. Sert a generer toutes les solutions */
void swap (Plateau *plateau,Carte tabCarte[]);

/* Nettoyage du plateau pour la fonction backtrack*/
void clean_plateau (Plateau *plateau);

/* fonction permettant de savoir si un fichier existe */
int existe_fichier(char *fichier);


void exporteur_magique(Plateau *plateau);

#endif
