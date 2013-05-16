Projet : PUZZLE
===============

Participants
------------

Bouilly Romain 2908292  (interface graphique)   
Vigano Sylvain 3203772    
Viljasaar Oskar 3000989   
Bielle Benjamin 2900825   

Fichiers inclus
---------------

> include/structs.h    
>     Structures de données du projet   
>     - (tout le monde)   

> src/init.c et include/init.h   
>     Fonctions de base   
>     - (tout le monde)   

> src/contact.c et include/contact.h    
>     Fonctions testant si deux cartes sont compatibles    
>     - Oskar Viljasaar   

> src/chemin.c et include/chemin.h      
>     Fonction donnant le chemin de résolution à suivre    
>     - Benjamin Bielle    
>     - Vigano Sylvain    

> src/backtrack.c et include/backtrack.h           
>     Fonction de résolution du puzzle           
>     - Benjamin Bielle         

> src/parser.c et include/parser.h              
>     Fonctions permettant la création et la lecture du fichier de solution              
>     - Sylvain Vigano               
>     - format agréé par tout le monde            

> src/main.c       
>     Main du projet         
>     - Oskar Viljasaar        
>     - Benjamin Bielle       

Directives de Makefile
----------------------

> all  
    Compilation de tous les fichiers   

> DEBUG=1    
    Compilation du projet en mode DEBUG (donne notamment l'etat actuel du plateau dans la résolution)    

> clean   
    Suppression de tous les binaires, de tous les fichiers objet et de la librairie    

> proper    
    Suppression de tous les fichiers temporaires    

> cleanall    
    Suppression de tous les binaires, de tous les fichiers objet, de la librairie et des dossiers bin, obj et lib    

> run1   
    Lance le programme avec les valeurs par défaut    

> run2    
    Lance le programme à partir du fichier Puzzle.puzzle en spirale (départ du centre)   

> run3   
    Lance le programme à partir du fichier Puzzle.puzzle en serpent (départ du coin supérieur gauche)   

> run4   
    Lance le programme à partir du fichier Puzzle.puzzle en mode hybride (serpent + spirale)   

> run5   
    Lance le programme à partir du fichier Puzzle.puzzle en mode serpent2   

Directives de l'exécutable bin/PUZZLE
-------------------------------------

> Usage: nom programme [FICHIER MODE] [OPTION ..]    
> FICHIER etant un fichier avec les cartes et la taille du plateau a resoudre. MODE etant l'entier 1, 2 ou 3.    
> 1: resolution du puzzle en spirale a partir du centre    
> 2: resolution du puzzle en serpent a partir du coin superieur gauche    
> 3: resolution du puzzle en hybride (spirale+serpent). Ceci sert surtout pour des plateaux rectangulaires.    
> 4: resolution du puzzle en serpentTwo    
> Les OPTIONS sont    
> --no-swap : seule la premiere carte sera placee initialement. Il n'y aura pas de placement possible des autres cartes disponibles   
> --no-rotate : la carte initialement placee ne subira pas de rotation initiale.   
> --help : afficher ce message.    
> Appel sans fichier: resolution d'un plateau deja donne dans le programme.    

Etat d'avancement
-----------------

> src/init.c      - OK   
> src/contact.c   - OK   
> src/chemin.c    - OK   
> src/backtrack.c - OK   
> src/parser.c    - OK   
> src/main.c      - Fini quand les autres fonctions seront finies    

Normes utilisées
----------------

Norme Posix (POSIX SOURCE 1), ANSI   


Bibliothèque Graphique
----------------------

Pygame (bibliothèque basée sur SDL) - Licence : GNU GPL      

