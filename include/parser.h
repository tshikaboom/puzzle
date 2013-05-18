#ifndef PARSER_H
#define PARSER_H
#include "structs.h"

/*Checks if input char is EndOfLine*/
int isEndOfLine (char cara);

/*char* Error Message*/
void error(char* errorMessage);

/*Read the card*/
int readCard(char* stringCard, Carte* current);

/*Carte** an array containing the cards that were parsed from the file*/
Carte* parseFile(char* filename,int* hauteur,int* largeur);

/*Carte** array of cards containing the cards to be exported*/
void export(char* filename, Plateau *plateau);

#endif
