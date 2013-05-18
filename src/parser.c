/* Module d'import/export puzzle/plateau/fichier
   Auteur principal: Sylvain Vigano */
#define _POSIX_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "structs.h"
#include "init.h"

#define MAX_BUFF 256
#define INT_OFFSET 48
#define IMPORT_MASK " %d_%1d%1d%1d%1d "
#define EXPORT_MASK "%d_%d%d%d%d\n"

/* Les commentaires datent d'une epoque ou j'avais l'habitude de coder en anglais
 * Nettoyer les erreurs avec du perror()
 */

int isEndOfLine(char cara)
{
  /**
   * checks if input char is EndOfLine.
   * @param char input
   * @return boolean value
   */
  switch (cara) {
  case '\0':
    return true;
    break;
  case '\n':
    return true;
    break;
  case '\r':
    return 1;
    break;
  default:
    return false;
    break;
  }
  return false;
}

void error(char* errorMessage)
{
  /**
   * @param char* Error Message
   */
  fprintf(stderr, "%s \n",errorMessage);
}

int readCard(char* stringCard, Carte* current)
{
  /**
   * @param char* input card from the filereader
   * @param Carte* pointer to current card for the parser
   * @return boolean, 1 if parsed successfully, 0 if not.
   */
  int id, top, bottom, left, right;
  int res;
  Carte* carte=current;

  res=sscanf(stringCard, IMPORT_MASK, &id, &top, &bottom, &left, &right);
  #ifdef DEBUG
  printf("Carte lue:\n");
  printf("%d %d %d %d %d\n", id, top, bottom, left, right);
  printf("res=%d\n",res);
  #endif
  
  if (res!=5) {
    error("Incorrect card format");
    return -1;
  }
  else {
    carte->identifiant = id;
    carte->Haut=top;
    carte->Bas=bottom;
    carte->Gauche=left;
    carte->Droite=right;
    carte->rotated=0;
    carte->sur_plateau=0;
    return 1;
  }
  error("Could not initiate card");
  return -1;
}

Carte *parseFile(char* filename,int* hauteur,int* largeur)
{
  /**
   * @param char* filename to be export
   * @param int* hauteur pointer to the hauteur from the filereader
   * @param int* largeur pointer to the largeur from the filereader
   * @return Carte** an array containing the cards that were parsed from the file
   */
  FILE *fp;
  char ligne[MAX_BUFF+1];
  int i=0, readedCard=0;
  Carte *stack = NULL;

  fp = fopen(filename, "r");
  
  if (fp) {
    /* lecture des dimensions pour l'allocation apres */
    fscanf(fp," %d\n", hauteur);
    fscanf(fp," %d\n", largeur);

    /* allocation du tableau de cartes et verification */
    stack = (Carte *) malloc(sizeof(Carte)*(*hauteur)*(*largeur));
    assert(stack);

    while (fgets(ligne, MAX_BUFF, fp)) {
      readedCard+=readCard(ligne,stack+i)>0 ? 1:0;
      /*      stack[i].identifiant=i; */
      i++;
      #ifdef DEBUG
      printf("nb cartes lues: %d\n",readedCard);
      #endif
    }
    fclose(fp);
    
    if (readedCard!=(*hauteur)*(*largeur)) {
      error("Number of readed card and dimensions does not match");
      free(stack);
    }
    
    return stack;
  }  
  else error("Error: file could not be opened or found");

  return NULL;
}

void export(char* filename, Plateau *plateau){
  /**
   *@param char* filename The name for the exported file
   *@param int hauteur height of the grid
   *@param largeur width of the grid
   *@param Carte** array of cards containing the cards to be exported
   */
  int i, j;
  FILE* fp;
  if ((fp=fopen(filename,"w"))) {
    fprintf(fp, "%d\n%d\n", plateau->hauteur, plateau->largeur);
    for (j=0; j<plateau->hauteur; j++)
      for (i=0; i<plateau->largeur; i++)
	fprintf(fp, EXPORT_MASK,
		plateau->tab[i][j]->identifiant,
		plateau->tab[i][j]->Haut,
		plateau->tab[i][j]->Bas,
		plateau->tab[i][j]->Gauche,
		plateau->tab[i][j]->Droite);
    fclose(fp);
  }
  else error("Can't write the filename");
}

