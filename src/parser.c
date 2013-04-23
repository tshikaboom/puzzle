#define _POSIX_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>


#include "structs.h"
#include "init.h"

#define MAX_BUFF 256
#define INT_OFFSET 48
#define IMPORT_MASK " %1d%1d%1d%1d"
#define EXPORT_MASK "%d%d%d%d\n"

/*
 * Nettoyer les erreurs avec du perror()
 */

int isEndOfLine(char cara){
  /**
   * checks if input char is EndOfLine.
   * @param char input
   * @return boolean value
   */
  switch (cara){
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

int charToInteger(char cara){
  /**
   * @param cara Char to be cast to integer
   * @return int result of cast
   */
  return cara-INT_OFFSET;
}

int strLength(char* str){
  /**
   * @param char* str String to be analyzed
   * @return Input string lenght
   */
  int i=0;
  while(!isEndOfLine(str[i])) i++;
  return i;
}

int stringToInteger(char* str){
  /**
   * @param str Input string to be parsed to integer
   * @return int Resulting integer
   */
  int res=0,i,lim;
  lim=strLength(str);
  for(i=0;!isEndOfLine(str[i]);i++) res+=charToInteger(str[i])*pow(10,lim-i-1);
  return res;
}



void error(char* errorMessage){
  /**
   * @param char* Error Message
   */
  fprintf(stderr, "%s \n",errorMessage);
}

int readCard(char* stringCard, Carte* current){
  /**
   * @param char* input card from the filereader
   * @param Carte* pointer to current card for the parser
   * @return boolean, 1 if parsed successfully, 0 if not.
   */
  int top,bottom,left,right;
  int res;
  Carte* carte=current;

  res=sscanf(stringCard,IMPORT_MASK,&top,&bottom,&left,&right);
  /*Remplacement possible si on d�cide de se passer de la fonction interm�diaire readChar
    Carte* carte=current;
    res=fscanf(fp,IMPORT_MASK,&carte->Haut,&carte->Bas,&carte->Gauche,&carte->Droite);

  */
  /*
    top=charToInteger(top);
    bottom=charToInteger(bottom);
    left=charToInteger(left);
    right=charToInteger(right);
  */
  if (res!=4){
    error("Incorrect card format");
    return EXIT_FAILURE;
  }
  else{
    carte->Haut=top;
    carte->Bas=bottom;
    carte->Gauche=left;
    carte->Droite=right;
    carte->rotated=0;
    carte->sur_plateau=0;
    return 1;
  }
  error("Could not initiate card");
  return EXIT_FAILURE;
}

Carte *parseFile(char* filename,int* hauteur,int* largeur) {
  /**
   * @param char* filename to be export
   * @param int* hauteur pointer to the hauteur from the filereader
   * @param int* largeur pointer to the largeur from the filereader
   * @return Carte** an array containing the cards that were parsed from the file
   */
  FILE *fp;
  char ligne[MAX_BUFF+1];
  int i=0,readedCard=0;
  /*int hauteur=0,largeur=0;*/
  Carte* stack;

  fp = fopen(filename, "r");

  if (fp){
    fscanf(fp," %d\n",&(*hauteur));
    fscanf(fp," %d\n",&(*largeur));

    /*
      fgets(ligne,MAX_BUFF,fp);
      if (strLength(ligne)==1) *hauteur=charToInteger(ligne[0]);
      fgets(ligne,MAX_BUFF,fp);
      if (strLength(ligne)==1) *largeur=charToInteger(ligne[0]);
    
    *Modif du type de sortie du parseur ! */
     stack = (Carte *) malloc(sizeof(Carte)*(*hauteur)*(*largeur));
	/*
    / stack=(Carte**) malloc(sizeof(Carte)*(*hauteur)*(*largeur));
    */
    while(fgets(ligne,MAX_BUFF,fp)){
      /* stack[i]=(Carte*) malloc(sizeof(Carte)); */
      readedCard+=readCard(ligne,stack+i);
      stack[i].identifiant=i;
      i++;
    }
    fclose(fp);
    if (readedCard!=(*hauteur)*(*largeur)) {
      error("Number of readed card and dimensions does not match");
      free(stack);
    }
    return stack;
  }
  else{
    error("Error: file could not be opened or found");
  }
  return NULL;
}

void export(char* filename,int hauteur,int largeur,Carte* stack){
  /**
   *@param char* filename The name for the exported file
   *@param int hauteur height of the grid
   *@param largeur width of the grid
   *@param Carte** array of cards containing the cards to be exported
   */
  int i;
  FILE* fp;
  if((fp=fopen(filename,"w"))){
    fprintf(fp,"%d\n%d\n",hauteur,largeur);
    for (i=0;i<hauteur*largeur;i++)
      fprintf(fp,EXPORT_MASK,stack[i].Haut,stack[i].Bas,stack[i].Gauche,stack[i].Droite);
    fclose(fp);
  }
  else error("cant't write the filename");
}

