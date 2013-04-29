#ifndef PARSER_H
#define PARSER_H
#include "structs.h"

/*Checks if input char is EndOfLine*/
int isEndOfLine (char cara);

/*cara Char to be cast to integer*/
int charToInteger(char cara);

/*Input string lenght*/
int strLength(char* str);

/*str Input string to be parsed to integer*/
int stringToInteger(char* str);

/*char* Error Message*/
void error(char* errorMessage);

/*Read the card*/
int readCard(char* stringCard, Carte* current);

/*Carte** an array containing the cards that were parsed from the file*/
Carte* parseFile(char* filename,int* hauteur,int* largeur);

/*Carte** array of cards containing the cards to be exported*/
void export(char* filename, Plateau *plateau);

#endif
