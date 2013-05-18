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
  /*p=hauteur, n=largeur;
   */
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
    l'increment converge vers la valeur finale par valeurs positives ou negatives
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
    printf("%d: (%d, %d)\n", i+1, tmp->x, tmp->y);
}

Chemin* constCheminSpiraleDec(Chemin* chemin,int n, int p, int xOff, int yOff)
{
  /*p=hauteur, n=largeur;
    La boucle for permet le calcul des coins de la spirale, c'est a dire les coordonnees
    des points pour lesquels on change de direction de deplacement
  */
  int k, x, y, prevX, prevY, sens=1;
  prevX=0, prevY=0;
  x=-1;
  y=0;
  
  for (k=0;k<min(n,p);k++) {
    x+=sens*(n-k);
    if (prevX!=x) chemin=ajouteLigneX(chemin,prevX+xOff,x+xOff-sens,y+yOff);
    y+=sens*(p-k-1);
	
    if (prevY!=y) chemin=ajouteLigneY(chemin,prevY+yOff,y+yOff-sens,x+xOff);
    sens=-sens;
    prevX=x;
    prevY=y;
  }
  chemin=ajouteChemin(chemin,x+xOff,y+yOff);
  return chemin;
}

Chemin* serpentTwo(Chemin *chemin,int n,int p,int xOffset, int yOffset)
/*
  p=hauteur, n=largeur;
  Ce chemin suit un remplissage lineaire par rectangle de largeur 2 et les accole
*/
{
  int k,i;
  if (n%2==1){
    chemin=ajouteLigneY(chemin,yOffset,p-1+yOffset,n-1+xOffset);
    k=n-2;
  }
  else k=n-1;
  while (k>=0)
    {
      for (i=p-1;i>=0;i--) 
	chemin=ajouteLigneX(chemin,k+xOffset,k-1+xOffset,i+yOffset);
      k-=2;
    }
	
  return chemin;
}

Chemin* constCompCheminSpirale(int n, int p)
/*Le mode de chemin hybride. Decoupage en spirale carree completee par un chemin en lineaire
 * subdivise rectangles de largeur 2.
 p=hauteur, n=largeur;
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
    chemin=serpentTwo(chemin,x,y,xOff,yOff);
    chemin=constCheminSpiraleDec(chemin,s, s,0,0);
    return chemin;
  }
  else return constCheminSpirale(s,s);
}

/*
Fonctions Alias pour alleger les appels quand les offsets ne sont pas utiles
*/
Chemin* constCheminEnS(int n,int p)
/*p=hauteur, n=largeur;
 * Petit alias pour se simplifier la construction dans le cas d'un chemin
 * non compose 
 */
{
  return CheminEnS(NULL,n,p,0,0);
}

Chemin* constCheminSpirale(int n,int p)
/*p=hauteur, n=largeur;
 */
{
  return constCheminSpiraleDec(NULL,n,p,0,0);  
}

Chemin* serpentDeux(Chemin *chemin,int n,int p)
{
  return serpentTwo(chemin,n,p,0,0);
}