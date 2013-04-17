/*
 * File:   main.c
 * Author: 3203772
 *
 * Created on 5 mars 2013, 18:32
 */

#include <stdio.h>
#include <stdlib.h>

struct chemin {
    int x;
    int y;
    struct chemin *Suivant;
};

typedef struct coordonnee Coordonnee;
typedef struct chemin Chemin;


Chemin *nouveauChemin(int x, int y)
{
/*
Todo check des mallocs
*/
    Chemin *cellule_initiale;
    cellule_initiale = (Chemin *) malloc(sizeof(Chemin));

    cellule_initiale->Suivant = NULL;

    cellule_initiale->x = x;
    cellule_initiale->y = y;

    return cellule_initiale;
}

Chemin *ajoutePointChemin(Chemin *liste, int x, int y)
{
/*
Todo check des mallocs
*/
    Chemin *nvcell;
    nvcell = (Chemin *) malloc(sizeof(Chemin));

    nvcell->Suivant = liste;
    nvcell->x = x;
    nvcell->y = y;

    return nvcell;
}

int min(int a,int b){
    if (a<b) return a;
    else return b;
}

Chemin* constCheminSpirale(int n, int p)
{
  /*
   A reoptimiser
  */
    int pas,k,x=n,y=1;
    int sens=1,j;

    Chemin* chemin = nouveauChemin(0,0);

    for (j=2;j!=n;j+=sens) chemin=ajoutePointChemin(chemin,j-1,y-1);

    for(k=1;k<=min(n,p)-1;k++){

        pas=sens*(p-k);

        for (j=y;j!=y+pas;j+=sens) chemin=ajoutePointChemin(chemin,x-1,j-1);
        y+=pas;
        sens=-sens;

        pas=sens*(n-k);
        for (j=x;j!=x+pas;j+=sens) chemin=ajoutePointChemin(chemin,j-1,y-1);

        x+=pas;
    }
    chemin=ajoutePointChemin(chemin,x-1,y-1);
    return chemin;
}

int abs(int n){
if (n<0) return -n;
else return n;
}

Chemin* constCheminEnS(int n,int p){
/*
j'ai juste un peu craque le %n et le /n sont hyper gourmants mais c'etait pour relever le defi d'Oskaar (en une ligne avec un truc completement louffoque)
Une solution avec de l'operateur ternaire a debugger qui marche presque
*/
    int i;
    Chemin* chemin = nouveauChemin(0,p-1);
    
        for (i=n*p-2;i>=0;i--) chemin=ajoutePointChemin(chemin,abs((n-1)*(-(i/n)%2)+(i%n)),i/n);
    /*
        for(i=0;i<p*n;i++) chemin = ajoutePointChemin(chemin,((i/n)%2) ? (n-1)-(i%n) : i%n,(i/n));
     */
    return chemin;
}

int main(int argc, char** argv) {
/*
    Chemin *spirale = constCheminSpirale(5,4);
*/
    Chemin *spirale = constCheminEnS(5,4);
    Chemin *tmp = spirale;
    while(tmp) {
        printf("(%d,%d)\n",tmp->x,tmp->y);
        tmp = tmp->Suivant;
    }
    //initPosition(5,4);
//    initPosition(7,3);
//    initPosition(3,3);
}
