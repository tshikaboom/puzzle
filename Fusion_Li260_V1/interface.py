#!/usr/bin/env python
#-*- coding: utf-8 -*-

#PUZZLE - LI260

import pygame, time
from pygame.locals import *

class Puzzle:
	def __init__(self):

                pygame.init()

                # Variables et images (c'est ici qu'on charge les images en mémoire)    

		largeur_ecran = 1024
		hauteur_ecran = 768
         
                self.fondN = 0
                self.z0_fond = pygame.image.load("images/fond0.jpg")
                self.upmc = pygame.image.load("images/upmc.png")
                self.intro = pygame.image.load("images/intro.png")
                self.image_reset = pygame.image.load("images/reset.png")
                
                self.carteVIDE = pygame.image.load("images/vide.png")

                self.temp_carte = self.z19_move = self.carteVIDE

                self.carte1234 = pygame.image.load("images/1234.png")
                self.carte3421 = pygame.transform.rotate(self.carte1234, 90)
                self.carte2143 = pygame.transform.rotate(self.carte1234, 180)
                self.carte4312 = pygame.transform.rotate(self.carte1234, 270)

                self.carte3214 = pygame.image.load("images/3214.png")
                self.carte1423 = pygame.transform.rotate(self.carte3214, 90)
                self.carte2341 = pygame.transform.rotate(self.carte3214, 180)
                self.carte4132 = pygame.transform.rotate(self.carte3214, 270)
                                
                self.carte1432 = pygame.image.load("images/1432.png")
                self.carte3241 = pygame.transform.rotate(self.carte1432, 90)
                self.carte4123 = pygame.transform.rotate(self.carte1432, 180)
                self.carte2314 = pygame.transform.rotate(self.carte1432, 270)

                self.carte2134 = pygame.image.load("images/2134.png")
                self.carte3412 = pygame.transform.rotate(self.carte2134, 90)
                self.carte1243 = pygame.transform.rotate(self.carte2134, 180)
                self.carte4321 = pygame.transform.rotate(self.carte2134, 270)

                self.carte3124 = pygame.image.load("images/3124.png")
                self.carte2413 = pygame.transform.rotate(self.carte3124, 90)
                self.carte1342 = pygame.transform.rotate(self.carte3124, 180)
                self.carte4231 = pygame.transform.rotate(self.carte3124, 270)

                self.carte2431 = pygame.image.load("images/2431.png")
                self.carte3142 = pygame.transform.rotate(self.carte2431, 90)
                self.carte4213 = pygame.transform.rotate(self.carte2431, 180)
                self.carte1324 = pygame.transform.rotate(self.carte2431, 270)

                tableau_fichier = []
		tableau_fichier_ordre = []
                str_fichier = [] 
                                
                with open("fichier.txt") as f_fichier:
                        for line in f_fichier:
				line = line.split("_")

				if len(line) > 1:
                                	tableau_fichier.append(int(line[1]))
					tableau_fichier_ordre.append(int(line[0]))
                                	str_fichier.append('self.carte'+(str(int(line[1]))))
				else:
					tableau_fichier.append(int(line[0]))
					tableau_fichier_ordre.append(int(line[0]))
                                	str_fichier.append('self.carte'+(str(int(line[0]))))

                tableau_solution = []
		tableau_solution_ordre = []
                str_solution = [] 
                                
                with open("solution.txt") as f_solution:
                        for line in f_solution:
				line = line.split("_")

				if len(line) > 1:
                                	tableau_solution.append(int(line[1]))
					tableau_solution_ordre.append(int(line[0]))
                                	str_solution.append('self.carte'+(str(int(line[1]))))
				else:
					tableau_solution.append(int(line[0]))
					tableau_solution_ordre.append(int(line[0]))
                                	str_solution.append('self.carte'+(str(int(line[0]))))

		##############################################################################################

		self.NOMBRE_TOTAL_DE_CARTES = tableau_solution[0]*tableau_solution[1]
		print self.NOMBRE_TOTAL_DE_CARTES

		self.Bandicoot = []

		self.ABRACADABRA = (largeur_ecran/self.NOMBRE_TOTAL_DE_CARTES) - 1

######################################################################################################################
                # Liste des images
                self.Liste = [self.z0_fond]

		for i in range(self.NOMBRE_TOTAL_DE_CARTES*2) :
			self.Bandicoot.append(pygame.transform.smoothscale(self.carteVIDE, (self.ABRACADABRA, self.ABRACADABRA)))
			self.Liste.append(self.Bandicoot[i])

		self.Liste.append(self.z19_move)
		self.Liste.append(self.upmc)

                # Liste des positions en X des images
                self.ListeX = [0]

		TitanX = (largeur_ecran - ((self.ABRACADABRA*self.NOMBRE_TOTAL_DE_CARTES) + self.NOMBRE_TOTAL_DE_CARTES))/2
		for i in range(self.NOMBRE_TOTAL_DE_CARTES) :
			self.ListeX.append(TitanX)
			TitanX = TitanX + self.ABRACADABRA + 1

		AsteriX = (largeur_ecran - ((self.ABRACADABRA*tableau_solution[0]) + tableau_solution[0]))/2
		for i in range(tableau_solution[0]) :
			for k in range(tableau_solution[0]) :
				self.ListeX.append(AsteriX)
				AsteriX = AsteriX + self.ABRACADABRA + 1
			AsteriX = (largeur_ecran - ((self.ABRACADABRA*tableau_solution[0]) + tableau_solution[0]))/2

		self.ListeX.append(0)
		self.ListeX.append(774)

                # Liste des positions en Y des images
                self.ListeY = [0]

		for i in range(self.NOMBRE_TOTAL_DE_CARTES) :
			self.ListeY.append(653)

		TitanY = 150
		for i in range(tableau_solution[0]) :
			for k in range(tableau_solution[0]) :
				self.ListeY.append(TitanY)
			TitanY = TitanY + self.ABRACADABRA + 1

		self.ListeY.append(0)
		self.ListeY.append(11)
######################################################################################################################
			

		# Options de Pygame (ici, la mise en place du fond d'écran et de la résolution du logiciel)
		self.screen = pygame.display.set_mode([largeur_ecran, hauteur_ecran], 0, 24)
		pygame.display.set_caption("Interface LI260")
		
		self.screen.blit(self.z0_fond, (0, 0))
		self.screen.blit(self.intro, (0, 0))
		self.screen.blit(self.upmc, (774, 11))
                pygame.display.update()
                
                pygame.event.set_allowed(None)          #
                pygame.event.set_allowed(QUIT)          # } Le programme ne cherche que les évènements du type "touche pressée" : KEYDOWN ou "action de fermerture" : QUIT
                pygame.event.set_allowed(KEYDOWN)       #   cela permet d'éviter une surcharge CPU liée aux mouvements de la souris.
                pygame.event.set_allowed(MOUSEBUTTONDOWN)

		# Boucle Principale (le programme attend des pressions de touche pour démarrer nos petites fonctions)
                running = True
                while running:
                        
                        souris_pos = pygame.mouse.get_pos()
                        
                        for event in pygame.event.get():
                                if event.type == pygame.QUIT:
                                        running = False
                                        pygame.quit()
                                        break

                                ##########################################################################
                        
                                elif (event.type == KEYDOWN and event.key == K_RETURN) or (event.type == KEYDOWN and event.key == K_KP_ENTER) :

                                        n = 0.1
                                        omega = 1

                                        while omega<(self.NOMBRE_TOTAL_DE_CARTES+1):                                
                                                self.Liste[omega] = eval(str_fichier[omega+1])
						self.Liste[omega] = pygame.transform.smoothscale(self.Liste[omega], (self.ABRACADABRA, self.ABRACADABRA))
                                                FonctionAffichage(self)
                                                time.sleep(n)
                                                omega = omega + 1

                                ##########################################################################

                                elif event.type == KEYDOWN and event.key == K_SPACE :

                                        n = 0.1
                                        listes = 1
                                        omega = 1

                                        while omega<(self.NOMBRE_TOTAL_DE_CARTES+1):                                
                                                self.Liste[omega] = eval(str_solution[omega+1])
						self.Liste[omega] = pygame.transform.smoothscale(self.Liste[omega], (self.ABRACADABRA, self.ABRACADABRA))
                                                FonctionAffichage(self)
                                                time.sleep(n)
                                                omega = omega + 1

                                        while listes<(self.NOMBRE_TOTAL_DE_CARTES+1):
                                                self.temp_carte = self.Liste[listes]
                                                FonctionDeSonic(self, self.ListeX[listes], self.ListeY[listes], self.ListeX[listes+self.NOMBRE_TOTAL_DE_CARTES], self.ListeY[listes+self.NOMBRE_TOTAL_DE_CARTES], self.Liste[listes], listes)                                
                                                self.Liste[listes+self.NOMBRE_TOTAL_DE_CARTES] = eval(str_solution[listes+1])
						self.Liste[listes+self.NOMBRE_TOTAL_DE_CARTES] = pygame.transform.smoothscale(self.Liste[listes+self.NOMBRE_TOTAL_DE_CARTES], (self.ABRACADABRA, self.ABRACADABRA))
                                                FonctionAffichage(self)
                                                listes = listes + 1
						time.sleep(n)

                                ##########################################################################

                                elif event.type == KEYDOWN and event.key == K_TAB : #Le Reset
                                        
					self.Liste = [self.z0_fond]

					for i in range(self.NOMBRE_TOTAL_DE_CARTES*2) :
						self.Bandicoot.append(pygame.transform.smoothscale(self.carteVIDE, (self.ABRACADABRA, self.ABRACADABRA)))
						self.Liste.append(self.Bandicoot[i])

					self.Liste.append(self.z19_move)
					self.Liste.append(self.upmc)
                                
                                        self.screen.blit(self.Liste[0], (0, 0))
                                        self.screen.blit(self.intro, (0, 0))
                                        self.screen.blit(self.upmc, (774, 11))
                                        pygame.display.update()

                                ##########################################################################

                                elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1 : #Le Reset (via la souris)
                                        if self.bouton_reset.collidepoint(souris_pos):

						self.Liste = [self.z0_fond]

						for i in range(self.NOMBRE_TOTAL_DE_CARTES*2) :
							self.Bandicoot.append(pygame.transform.smoothscale(self.carteVIDE, (self.ABRACADABRA, self.ABRACADABRA)))
							self.Liste.append(self.Bandicoot[i])

						self.Liste.append(self.z19_move)
						self.Liste.append(self.upmc)
                                        
                                                self.screen.blit(self.Liste[0], (0, 0))
                                                self.screen.blit(self.intro, (0, 0))
                                                self.screen.blit(self.upmc, (774, 11))
                                                pygame.display.update()

                                ##########################################################################

                                elif event.type == KEYDOWN and event.key == K_BACKSPACE : #Le fond d'écran

                                        if self.fondN < 5 :
                                                self.fondN = self.fondN + 1
                                                self.Liste[0] = pygame.image.load("images/fond"+str(self.fondN)+".jpg")
                                                FonctionAffichage(self)
                                                
                                        else :
                                                self.fondN = 0
                                                self.Liste[0] = pygame.image.load("images/fond0.jpg")
                                                FonctionAffichage(self)

                                ##########################################################################                  

                                elif event.type == KEYDOWN and event.key == K_ESCAPE : #Le tueur de boucle, que l'on active via la touche Echap
                                        
                                        running = False
                                        pygame.quit()
                                        break
                        
##########################################################################
def FonctionAffichage(self):
        x = 0
	while x<(len(self.Liste)):
		self.screen.blit(self.Liste[x], (self.ListeX[x], self.ListeY[x]))
		x=x+1
		
	self.bouton_reset = self.screen.blit(self.image_reset,(10,10))
	pygame.display.flip()

##########################################################################
def FonctionDeSonic(self, posX_start, posY_start, posX_stop, posY_stop, carte, delta):

        for x in range(20):                  #animation
                self.Liste[delta] = self.carteVIDE
                self.Liste[-2] = pygame.transform.rotate(carte, (x*(18)))
                
                if (posX_start - posX_stop)>=0:
                        positionX = posX_start - ((abs(posX_start-posX_stop))/20)*(x+1)
                        positionY = posY_start - ((abs(posY_start-posY_stop))/20)*(x+1)
                else:
                        positionX = posX_start + ((abs(posX_start-posX_stop))/20)*(x+1)
                        positionY = posY_start - ((abs(posY_start-posY_stop))/20)*(x+1)
                   
                self.ListeX[-2] = positionX
                self.ListeY[-2] = positionY
                FonctionAffichage(self)
                time.sleep(0.02)
                
        self.Liste[-2] = self.carteVIDE
	
##########################################################################			
if __name__ == "__main__":
	Puzzle()
