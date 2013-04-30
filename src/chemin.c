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
  if (a<b) return a;
  else return b;
}

int abs(int n)
{ if (n<0) return -n;
  else return n;
}

Chemin* ajouteChemin(Chemin *liste, int x, int y)
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
  int i;
  Chemin* ret;
  if (chemin==NULL) ret = nouveauChemin(n-1+xOffset,p-1+yOffset);
  else ret=chemin;
  for (i=n*p-2;i>=0;i--){
	ret=ajouteChemin(ret,
			abs((n-1)*(-(i/n)%2)+(i%n))+xOffset,
			(i/n)+yOffset);
  }
  return ret;
}

Chemin* ajouteLigneX(Chemin* chemin, int xDepart, int xArrivee, int y)
{
  int i, step;
  if (xDepart<xArrivee) step=1;
  else step=-1;
  
  for (i=0;xDepart+i!=xArrivee;i+=step)
    chemin=ajouteChemin(chemin,xDepart+i,y);
  return chemin;
}

Chemin* ajouteLigneY(Chemin* chemin, int yDepart,int yArrivee,int x)
{
  int i, step;
  if (yDepart<yArrivee) step=1;
  else step=-1;
  
  for (i=0;yDepart+i!=yArrivee;i+=step)
    chemin=ajouteChemin(chemin,x,yDepart+i);
  return chemin;
}

Chemin* constCheminEnS(int n,int p)
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
    La fonction calcule une somme par coins c'est a dire la case a
    partir de laquelle on doit changer de direction.
  */
  int k, x, y, prevX, prevY, sens=1;
  prevX=0, prevY=0;
  x=-1;
  y=0;
  
  for (k=0;k<min(n,p);k++) {
    x+=sens*(n-k);
    
    chemin=ajouteLigneX(chemin,prevX+xOff,x+xOff,y+yOff);
    y+=sens*(p-k-1);
    
    chemin=ajouteLigneY(chemin,prevY+yOff,y+yOff,x+xOff);
    sens=-sens;
    prevX=x;
    prevY=y;
  }
  chemin=ajouteChemin(chemin,x,y);
  return chemin;
}

Chemin* constCheminSpirale(int n,int p)
{
  return constCheminSpiraleDec(NULL,n,p,0,0);  
}

Chemin* constCompCheminSpirale(int n, int p)
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
  }
  else return constCheminSpirale(s,s);
}

int main(int argc, char** argv) {
  Chemin *spirale = constCompCheminSpirale(5,3);
  print_chemin(spirale);
}
