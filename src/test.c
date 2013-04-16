/*
 * File:   main.c
 * Author: 3203772
 *
 * Created on 5 mars 2013, 18:32
 */

#include <stdio.h>
#include <stdlib.h>
/*
 *
 */

struct coordonnee{
    int x;
    int y;
};

struct chemin{
    struct coordonnee point;

    struct chemin *Suivant;
};

typedef struct coordonnee Coordonee;
typedef struct chemin Chemin;

void ligne(int x, int y, Chemin c)
{
    Coordonnee point= (Coordonnee*) malloc(sizeof(Coordonnee));
    point->x=x;
    point->y=y;
    c->Suivant=point;
}

int min(int a,int b){
    if (a<b) return a;
    else return b;
}

void initPosition(int n, int p)
{
  /*
    La fonction calcule une somme par coins c'est a dire la case a
 partir de laquelle on doit changer de direction.
  */
    int pas,k,x=n,y=1;
    int sens=1,j;

    for(k=1;k<=min(n,p)-1;k++){
        printf("+(%d,%d)\n",x,y);
        pas=sens*(p-k);

        for (j=y;j!=y+pas;j+=sens) printf("%d,%d\n",x,j);
        y+=pas;
        sens=-sens;
        printf("-(%d,%d)\n",x,y);

        pas=sens*(n-k);
        for (j=x;j!=x+pas;j+=sens) printf("--%d,%d\n",j,y);

        x+=pas;
    }
}

int main(int argc, char** argv) {
    initPosition(5,4);
//    initPosition(7,3);
//    initPosition(3,3);
}

