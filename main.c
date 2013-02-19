#include <stdio.h>
#include <stdlib.h>

#include "contact.h"
#include "init.h"
#include "structs.h"
#include "backtrack.h"

int main()
{
  int i,j;
  Carte carte1, carte2, carte3, carte4, carte5, carte6, carte7, carte8, carte9;
  Plateau *plateau;
  Carte tabCarte[9];

  
  plateau = (Plateau *) malloc(sizeof(Plateau));
  plateau->tab = (Carte ***) malloc(TAILLE*sizeof(Carte **));
  for (i=0; i<TAILLE; i++)
    plateau->tab[i] = (Carte **) malloc(TAILLE*sizeof(Carte *));

  plateau->largeur = TAILLE;
  plateau->hauteur = TAILLE;

   
  carte1.Haut = carte2.Haut = carte3.Haut = carte4.Haut = carte5.Haut = carte6.Haut = carte7.Haut = carte8.Haut = carte9.Haut = 1;
  carte1.Bas = carte2.Bas = carte3.Bas = carte4.Bas = carte5.Bas = carte6.Bas = carte7.Bas = carte8.Bas = carte9.Bas = 2;
  carte1.Gauche = carte2.Gauche = carte3.Gauche = carte4.Gauche = carte5.Gauche = carte6.Gauche = carte7.Gauche = carte8.Gauche = carte9.Gauche = 3;
  carte1.Droite = carte2.Droite = carte3.Droite = carte4.Droite = carte5.Droite = carte6.Droite = carte7.Droite = carte8.Droite = carte9.Droite = 4;
  carte1.sur_plateau =  carte2.sur_plateau =  carte3.sur_plateau =  carte4.sur_plateau =  carte5.sur_plateau =  carte6.sur_plateau =  carte7.sur_plateau =  carte8.sur_plateau =  carte9.sur_plateau = 0;
  carte1.rotated =  carte2.rotated =  carte3.rotated =  carte4.rotated =  carte5.rotated =  carte6.rotated =  carte7.rotated =  carte8.rotated =  carte9.rotated = 0;
  carte1.identifiant = 1;
  carte2.identifiant = 2;
  carte3.identifiant = 3;
  carte4.identifiant = 4;
  carte5.identifiant = 5;
  carte6.identifiant = 6;
  carte7.identifiant = 7;
  carte8.identifiant = 8;
  carte9.identifiant = 9;
  
  tabCarte[0] = carte1;
  tabCarte[1] = carte2;
  tabCarte[2] = carte3;
  tabCarte[3] = carte4;
  tabCarte[4] = carte5;
  tabCarte[5] = carte6;
  tabCarte[6] = carte7;
  tabCarte[7] = carte8;
  tabCarte[8] = carte9;
		
  
  /*
  plateau->tab[0][0] = &carte1;
  plateau->tab[1][0] = &carte2;
  plateau->tab[2][0] = &carte3;
  plateau->tab[0][1] = &carte4;
  plateau->tab[1][1] = &carte5;
  plateau->tab[2][1] = &carte6;
  plateau->tab[0][2] = &carte7;
  plateau->tab[1][2] = &carte8;
  plateau->tab[2][2] = &carte9;

  affichage(plateau);
			  */
  for (i=0; i<TAILLE;i++)
    {
      for(j=0; j<TAILLE;j++){plateau->tab[i][j] = NULL;}}
  
  backtrack(plateau, tabCarte, 9, -1, 1);
  


  
  return 0;

}
