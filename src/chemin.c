#define _POSIX_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

Position chemin (int i,int choix)
{
  Position pos_suivant;
  
  /*En Spirale*/
  int tabI_spirale[10] = {1,0,0,1,2,2,2,1,0};
  int tabJ_spirale[10] = {1,1,2,2,2,1,0,0,0};
  
  /*En Z*/
  int tabI_Z[10] = {0,1,2,2,1,0,0,1,2};
  int tabJ_Z[10] = {0,0,0,1,1,1,2,2,2};
  
  
  switch(choix)
    {
    case 1 :
      {
	pos_suivant.x = tabI_spirale[i];
	pos_suivant.y = tabJ_spirale[i];
	
	/*return pos_suivant; */
	break;
      }
      
    case 2 :
      {
	pos_suivant.x = tabI_Z[i];
	pos_suivant.y = tabJ_Z[i];
	
	/*return pos_suivant; */
	break;
      }

    default :
      {
	printf("Choix du chemin non valide\n");
	pos_suivant.x = -1;
	pos_suivant.y = -1;
	/*return pos_suivant; */
	break;
      }
    }
  return pos_suivant;
}
