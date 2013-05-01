/*
 * File: main.c
 * Author: 3203772
 *
 * Created on 5 mars 2013, 18:32
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structs.h"
#include "chemin.h"

int min(int a, int b)
{ 
	return a<b ? a:b;
}

int abs(int n)
{ 
	return n<0 ? -n:n;
}

Chemin* ajouteChemin(Chemin *liste, int x, int y)
/* Ajoute une coordonnee au chemin existant
 */
{
  Chemin *nvcell;
  nvcell = (Chemin *) malloc(sizeof(Chemin));
  assert(nvcell);
  nvcell->Suivant = liste;
    
  nvcell->x = x;
  nvcell->y = y;
  return nvcell;    
}

Chemin* nouveauChemin(int x, int y)
{
  return ajouteChemin(NULL,x,y);
}

Chemin* CheminEnS(Chemin* chemin, int n, int p, int xOffset, int yOffset)
{
	int i,k=0,temp;n--;
	for (i=p-1;i>=0;i--){
		chemin=ajouteLigneX(chemin, 
		k+xOffset, 
		n+xOffset, 
		i+yOffset);
		temp=k;
		k=n;n=temp;
	}
	return chemin;
}

Chemin* ajouteLigneX(Chemin* chemin, int xDepart, int xArrivee, int y)
/* Fonction de deplacement lineaire selon X.
 */
{
  int i, step= xDepart<xArrivee ? 1:-1;
  /*
   l'increm
  */
  for (i=0;step*(xArrivee-(xDepart+i))>=0;i+=step)
    chemin=ajouteChemin(chemin,xDepart+i,y);
  return chemin;
}

Chemin* ajouteLigneY(Chemin* chemin, int yDepart,int yArrivee,int x)
{
  int i, step= yDepart<yArrivee ? 1:-1;
  
  for (i=0;step*(yArrivee-(yDepart+i))>=0;i+=step)
    chemin=ajouteChemin(chemin,x,yDepart+i);
  return chemin;
}

Chemin* constCheminEnS(int n,int p)
/*
 * Petit alias pour se simplifier la construction dans le cas d'un chemin
 * non compose 
*/
{
  return CheminEnS(NULL,n,p,0,0);
}

Position get_pos(Chemin *chemin)
{
  Position pos;
  assert(chemin);
  pos.x = chemin->x;
  pos.y = chemin->y;
  
  return pos;
}

void print_chemin(Chemin *chemin)
{
  int i=0;
  Chemin *tmp;
  for (tmp = chemin; tmp != NULL; tmp = tmp->Suivant, i++)
    printf("%d: (%d, %d)\n", i, tmp->x, tmp->y);
}

Chemin* constCheminSpiraleDec(Chemin* chemin,int n, int p, int xOff, int yOff)
{
  /*
     La boucle for permet le calcul des coins de la spirale, c'est a dire les coordonnees
     des points pour lesquels on change de direction de deplacement
  */
  int k, x, y, prevX, prevY, sens=1;
  prevX=0, prevY=1;
  x=-1;
  y=0;
  
  for (k=0;k<min(n,p);k++) {
    x+=sens*(n-k);
    chemin=ajouteLigneX(chemin,prevX+xOff,x+xOff,y+yOff);
    y+=sens*(p-k-1);
    
    chemin=ajouteLigneY(chemin,prevY+yOff,y+yOff,x+xOff);
    sens=-sens;
/*
on oublie pas le decalage sur x et y selon le sens de deplacement
de façon a ne pas integrer le point d'arrivee precedent deux fois
dans le chemin
*/
    prevX=x+sens;
    prevY=y+sens;
  }
  return chemin;
}

Chemin* constCheminSpirale(int n,int p)
{
  return constCheminSpiraleDec(NULL,n,p,0,0);  
}

Chemin* constCompCheminSpirale(int n, int p)
/*Le mode de chemin hybride. Decoupage en spirale carree completee par un chemin en S
 * sur la portion restante.
 * Known issue: le S bugg en 5x7.
 */
{
  int s=min(n,p),x,y,xOff,yOff;
  Chemin *chemin = NULL;

  if (n!=p) {
    if (s==n) {
      x=s;
      y=p-s;
      xOff=0;
      yOff=s;
    }
    else {
      x=n-s;
      y=p;
      xOff=s;
      yOff=0;
    }
    chemin=CheminEnS(chemin,x,y,xOff,yOff);
    chemin=constCheminSpiraleDec(chemin,s, s,0,0);
    return chemin;
  }
  else return constCheminSpirale(s,s);
}

int main(int argc, char** argv) {
  Chemin *spirale = constCheminSpirale(5,5);
  print_chemin(spirale);
}

