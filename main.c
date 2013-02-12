

#include "contact.h"
#include "init.h"
#include "structs.h"


int main()
{
  Carte carte1, carte2, carte3, carte4, carte5, carte6, carte7, carte8, carte9;
  Carte *plateau[3][3];
  carte1.Haut = carte2.Haut = carte3.Haut = carte4.Haut = carte5.Haut = carte6.Haut = carte7.Haut = carte8.Haut = carte9.Haut = 1;
  carte1.Bas = carte2.Bas = carte3.Bas = carte4.Bas = carte5.Bas = carte6.Bas = carte7.Bas = carte8.Bas = carte9.Bas = 2;
  carte1.Gauche = carte2.Gauche = carte3.Gauche = carte4.Gauche = carte5.Gauche = carte6.Gauche = carte7.Gauche = carte8.Gauche = carte9.Gauche = 3;
  carte1.Droite = carte2.Droite = carte3.Droite = carte4.Droite = carte5.Droite = carte6.Droite = carte7.Droite = carte8.Droite = carte9.Droite = 4;
  carte1.identifiant = 1;
  carte2.identifiant = 2;
  carte3.identifiant = 3;
  plateau[0][0] = &carte1;
  plateau[1][0] = &carte2;
  plateau[2][0] = &carte3;
  plateau[0][1] = &carte4;
  plateau[1][1] = &carte5;
  plateau[2][1] = &carte6;
  plateau[0][2] = &carte7;
  plateau[1][2] = &carte8;
  plateau[2][2] = &carte9;

  affichage(plateau, 3, 3);
  

  return 0;

}
