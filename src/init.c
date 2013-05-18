#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "parser.h"
#include "structs.h"
#include "init.h"

/* Fonction calculant la case depart pour le backtrack
   Elle n'est plus utilisee normalement
   Auteur: Benjamin Bielle */
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

/* Fonction determinant si une case est libre a proximite
   de la position
   Auteur: Benjamin Bielle */
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

/* Fonction rotation
   Auteur: Oskar Viljasaar
*/
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
      break;
    }
  }
}

/* Fonction d'affichage du plateau
   Prend juste le plateau en argument et fait des trucs plutot magiques pour l'affichage
   Auteur: Oskar Viljasaar
*/
void affichage(Plateau *plateau)
{
  int i, j;
  /* cas de l'affichage a 5 caracteres horizontaux
     == carte.identifiant ne depasse pas 9 */
  if (plateau->hauteur * plateau->largeur < 10) {
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
  else {
    for (j = 0; j < plateau->hauteur; j++) {
      for (i = 0; i < plateau->largeur; i++)
	printf("+------+");
      printf("\n");

      for (i = 0; i < plateau->largeur; i++)
	if (plateau->tab[i][j] == NULL) printf("|      |");
	else printf("|  %d   |", plateau->tab[i][j]->Haut);
      printf("\n");

      for (i = 0; i < plateau->largeur; i++)
	if (plateau->tab[i][j] == NULL) printf("|      |");
	else {
	  if (plateau->tab[i][j]->identifiant < 10)
	    printf("|%d %d  %d|",
		   plateau->tab[i][j]->Gauche,
		   plateau->tab[i][j]->identifiant,
		   plateau->tab[i][j]->Droite);
	  else
	    printf("|%d %d %d|",
		   plateau->tab[i][j]->Gauche,
		   plateau->tab[i][j]->identifiant,
		   plateau->tab[i][j]->Droite);
	}
      printf("\n");

      for (i = 0; i < plateau->largeur; i++)
	if (plateau->tab[i][j] == NULL) printf("|      |");
	else printf("|  %d   |", plateau->tab[i][j]->Bas);
      printf("\n");

      for (i = 0; i < plateau->largeur; i++)
	printf("+------+");
      printf("\n");
    }
  }
}

/* Fonction d'allocation d'un nouveau plateau
   rend un plateau contenant un tableau a 2dim dont les cases sont initialisees a NULL
   Auteur: Oskar Viljasaar
*/
Plateau *nouveau_plateau(int hauteur, int largeur)
{
  int i, j;
  Plateau *plateau;

  if (hauteur < 1 || largeur < 1) {
    printf("Hauteur ou largeur pas bons! Pas bon signe...\n");
    return NULL;
  }

  /*  printf("Allocation d'un tableau %dx%d\n", largeur, hauteur);*/


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

/* Fonction de liberation d'un plateau
   Auteur: Oskar Viljasaar */
void free_plateau(Plateau *plateau)
{
  int i;

  for (i=0; i<plateau->largeur; i++)
    free(plateau->tab[i]);

  free(plateau->tab);
  free(plateau);
}


void swap (Plateau *plateau,Carte tabCarte[])
{
  int i;
  Carte tmp;

  tmp = tabCarte[0];
  for (i=0; i<(plateau->largeur*plateau->hauteur)-1;i++)
    tabCarte[i] = tabCarte[i+1];

  tabCarte[plateau->largeur*plateau->hauteur-1] = tmp;
}

void clean_plateau (Plateau *plateau)
{
  int i,j;

  for (i=0; i<plateau->hauteur; i++)
    for(j=0; j<plateau->largeur; j++) {
      plateau->tab[j][i]->sur_plateau = 0;
      plateau->tab[j][i] = NULL;
    }
}

/* Fonction verifiant l'existence d'un fichier
   Auteur: Oskar Viljasaar */
int existe_fichier(char* fichier)
{
  FILE *fic = fopen(fichier, "r");
  if (fic) {
    /* le fichier existe */
    fclose(fic);
    return 1;
  }
  /* le fichier n'existe pas */
  return 0;
}

/* Fonction d'export de solutions
   Auteur: Oskar Viljasaar */
void exporteur_magique(Plateau *plateau)
/* Dans cette fonction, on fait l'hypothese que le plateau est
   bien rempli de cartes et non de pointeurs NULL. Normalement
   c'est le cas, comme on l'appelle seulement quand backtrack
   aura resolu le plateau. */
{
  int i=1;
  char buff[100]  = "sol0"; /* sera sol[n] */
  char folder[100];
  FILE *fichier;
  struct stat st;

  sprintf(folder, "./%dx%d/", plateau->hauteur, plateau->largeur);

  if (stat(folder, &st) == -1) {
    mkdir(folder, 0700);
    chmod(folder, 0700);
  }

  /* on change de dossier
     chdir(folder);*/
  /* on check si un fichier "soln" existe deja, n etant un entier.
     Donc la on fait en sorte un cast de int en char* (sprintf) */
  sprintf(buff, "%s/%s", folder, "sol0");
  do {
  sprintf(buff, "%s/sol%d", folder, i);
    i++;
  } while (existe_fichier(buff));


  /* apres la boucle, on en sera a un entier i dont le fichier soli
     n'existe pas. Donc on ecrit la solution */
  export(buff, plateau);

  /* on ecrit dans le fichier sol0 le nombre de solutions qu'on a
     pour l'instant. Le contenu d'avant est ecrase et ne nous sert pas */
  strcat(folder, "sol0");

  fichier = fopen(folder, "w");
  assert(fichier);
  fprintf(fichier, "%d\n", i-1);
  fclose(fichier);


  /* chdir(".."); */
}

char *strdup_intern(char *string)
{
    int n = strlen(string) + 1;
    char *dup = (char *) malloc(n*sizeof(char));
    assert(dup);
    strcpy(dup, string);

    return dup;
}
