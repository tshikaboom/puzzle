/*
 * File:   main.c
 * Author: 3203772
 *
 * Created on 5 mars 2013, 18:32
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structs.h"
#include "nvchemin.h"

Chemin *nouveau_chemin(int x, int y)
{
    Chemin *cellule_initiale;
    cellule_initiale = (Chemin *) malloc(sizeof(Chemin));
    /* a faire: check du malloc */
    cellule_initiale->Suivant = NULL;
    
    cellule_initiale->x = x;
    cellule_initiale->y = y;

    return cellule_initiale;    
}

Chemin *rajoute_chemin(Chemin *liste, int x, int y)
{
    Chemin *nvcell;
    nvcell = (Chemin *) malloc(sizeof(Chemin));
    /* a faire: check du malloc */
    nvcell->Suivant = liste;
    
    nvcell->x = x;
    nvcell->y = y;

    /* donc la si on veut elargir la liste on prend [[ liste = rajoute_chemin(liste, x, y); ]] */
    return nvcell;
    
}

int min(int a,int b){
    if (a<b) return a;
    else return b;
}

int abs(int n){
if (n<0) return -n;
else return n;
}

Chemin* constCheminEnS(int n,int p){
    int i;
    Chemin* chemin = nouveau_chemin(n-1,p-1);
    for (i=n*p-1;i>0;i--) chemin=rajoute_chemin(chemin,abs(i%(2*n)-n),i/n);
    
    printf("chemin en S: premier element %d, %d\n", chemin->x, chemin->y);
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

Chemin* constCheminSpirale(int n, int p)
{
  /*
    La fonction calcule une somme par coins c'est a dire la case a
 partir de laquelle on doit changer de direction.
  */
    int pas,k,x=n,y=1;
    int sens=1,j;
    
    Chemin* chemin = nouveau_chemin(0,0);
    
    for (j=2;j!=n;j+=sens) chemin=rajoute_chemin(chemin,j-1,y-1);
    
    for(k=1;k<=min(n,p)-1;k++){
        
        pas=sens*(p-k);

        for (j=y;j!=y+pas;j+=sens) chemin=rajoute_chemin(chemin,x-1,j-1);
        y+=pas;
        sens=-sens;

        pas=sens*(n-k);
        for (j=x;j!=x+pas;j+=sens) chemin=rajoute_chemin(chemin,j-1,y-1);

        x+=pas;
    }
    chemin=rajoute_chemin(chemin,x-1,y-1);
    return chemin;
}

/*
int main(int argc, char** argv) {

    Chemin *spirale = constCheminEnS(5,4);
    Chemin *tmp = spirale;
    while(tmp) {
        printf("(%d,%d)\n",tmp->x,tmp->y);
        tmp = tmp->Suivant;
    }

}

*/
