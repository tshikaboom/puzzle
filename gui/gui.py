#!/usr/bin/env python
#-*- coding: utf-8 -*-

#PUZZLE - LI260

import pygame, time, random, os, sys
from random import choice
from pygame.locals import *

import webbrowser as wb

import convert, interface

class Gui:
	def __init__(self):

		if os.path.isfile("fichier.txt"):
			os.remove("fichier.txt")   
		if os.path.isfile("sol1"):
			os.remove("sol1") 

                pygame.init()

                # Variables et images (c'est ici qu'on charge les images en mémoire)    

		largeur_ecran = 1024
		hauteur_ecran = 768

		self.typeDeParcours=0
		self.generatorX=0
		self.generatorY=0
         
                self.fondN = 0
                self.z0_fond = pygame.image.load("images/fond0.jpg")
                self.z0_nosoluce = pygame.image.load("images/nosoluce.png")
		self.z0_noyaucherche = pygame.image.load("images/noyaucherche.png")
                self.upmc = pygame.image.load("images/upmc.png")
                self.intro = pygame.image.load("images/gui.png")
		self.gui_a = pygame.image.load("images/gui_a.png")
		self.gui_b = pygame.image.load("images/gui_b.png")
		self.gui_c = pygame.image.load("images/gui_c.png")
		self.gui_precedent = pygame.image.load("images/precedent.png")
		self.image_reset = pygame.image.load("images/reset.png")

		self.gui_random = pygame.image.load("images/gui_random.png")
		self.gui_convert = pygame.image.load("images/gui_convert.png")
		self.gui_3x3 = pygame.image.load("images/3x3.png")
		self.gui_4x3 = pygame.image.load("images/4x3.png")
		self.gui_4x4 = pygame.image.load("images/4x4.png")
		self.gui_5x4 = pygame.image.load("images/5x4.png")
		self.gui_5x5 = pygame.image.load("images/5x5.png")
		self.parcours1 = pygame.image.load("images/p1.png")
		self.parcours2 = pygame.image.load("images/p2.png")
		self.parcours3 = pygame.image.load("images/p3.png")
		self.parcours4 = pygame.image.load("images/p4.png")

######################################################################################################################

		# Options de Pygame (ici, la mise en place du fond d'écran et de la résolution du logiciel)
		self.screen = pygame.display.set_mode([largeur_ecran, hauteur_ecran], 0, 24)
		pygame.display.set_caption("Interface LI260")
		
		self.screen.blit(self.z0_fond, (0, 0))
		self.screen.blit(self.intro, (0, 0))
		self.screen.blit(self.upmc, (774, 11))

		self.bouton_gui_random = self.screen.blit(self.gui_random,(3000,0))
		self.bouton_gui_convert = self.screen.blit(self.gui_convert,(3000,0))
		self.boutonA_precedent = self.screen.blit(self.gui_precedent,(3000,0))
		self.boutonB_precedent = self.screen.blit(self.gui_precedent,(3000,0))

		self.bouton_3x3 = self.screen.blit(self.gui_3x3,(3000,0))
		self.bouton_4x3 = self.screen.blit(self.gui_4x3,(3000,0))
		self.bouton_4x4 = self.screen.blit(self.gui_4x4,(3000,0))
		self.bouton_5x4 = self.screen.blit(self.gui_5x4,(3000,0))
		self.bouton_5x5 = self.screen.blit(self.gui_5x5,(3000,0))

		self.bouton_parcours1 = self.screen.blit(self.parcours1,(3000,0))
		self.bouton_parcours2 = self.screen.blit(self.parcours2,(3000,0))
		self.bouton_parcours3 = self.screen.blit(self.parcours3,(3000,0))
		self.bouton_parcours4 = self.screen.blit(self.parcours4,(3000,0))

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
					FonctionAffichage(self)

                                ##########################################################################

                                elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1 : #Le Reset (via la souris)

                                        if self.bouton_gui_random.collidepoint(souris_pos):
                                                FonctionAffichage2(self)
                                        elif self.bouton_gui_convert.collidepoint(souris_pos):
						wb.open("cartes")
						#os.system("./convert.py")
						convert.Dark()
						Houston = 0
						while Houston == 0 :
							if os.path.isfile("fichier.txt"):
								Houston = 1
                                                FonctionAffichage3(self)

                                        elif self.bouton_3x3.collidepoint(souris_pos):
						self.generatorX=3
						self.generatorY=3
						FonctionSonGoku(self)
                                                FonctionAffichage3(self)
                                        elif self.bouton_4x3.collidepoint(souris_pos):
						self.generatorX=3
						self.generatorY=4
						FonctionSonGoku(self)
                                                FonctionAffichage3(self)
                                        elif self.bouton_4x4.collidepoint(souris_pos):
						self.generatorX=4
						self.generatorY=4
						FonctionSonGoku(self)
                                                FonctionAffichage3(self)
                                        elif self.bouton_5x4.collidepoint(souris_pos):
						self.generatorX=4
						self.generatorY=5
						FonctionSonGoku(self)
                                                FonctionAffichage3(self)
                                        elif self.bouton_5x5.collidepoint(souris_pos):
						self.generatorX=5
						self.generatorY=5
						FonctionSonGoku(self)
                                                FonctionAffichage3(self)

                                        elif self.bouton_parcours1.collidepoint(souris_pos):
						self.typeDeParcours=1
                                                FonctionFinal(self)
                                        elif self.bouton_parcours2.collidepoint(souris_pos):
						self.typeDeParcours=2
                                                FonctionFinal(self)
                                        elif self.bouton_parcours3.collidepoint(souris_pos):
						self.typeDeParcours=3
                                                FonctionFinal(self)
                                        elif self.bouton_parcours4.collidepoint(souris_pos):
						self.typeDeParcours=4
                                                FonctionFinal(self)

                                ##########################################################################                  

                                elif event.type == KEYDOWN and event.key == K_ESCAPE : #Le tueur de boucle, que l'on active via la touche Echap
                                        
                                        running = False
                                        pygame.quit()
                                        break
                
##########################################################################
def FonctionAffichage(self):
	self.screen.blit(self.z0_fond, (0, 0))
	self.screen.blit(self.gui_a, (0, 0))
	self.screen.blit(self.upmc, (774, 11))

	self.bouton_gui_random = self.screen.blit(self.gui_random,(80,200))
	self.bouton_gui_convert = self.screen.blit(self.gui_convert,(80,500))

	pygame.display.flip()

##########################################################################
def FonctionAffichage2(self):
	self.bouton_gui_random = self.screen.blit(self.gui_random,(3000,0))
	self.bouton_gui_convert = self.screen.blit(self.gui_convert,(3000,0))

	self.screen.blit(self.z0_fond, (0, 0))
	self.screen.blit(self.gui_b, (0, 0))
	self.screen.blit(self.upmc, (774, 11))

	self.bouton_3x3 = self.screen.blit(self.gui_3x3,(125,220))
	self.bouton_4x3 = self.screen.blit(self.gui_4x3,(400,220))
	self.bouton_4x4 = self.screen.blit(self.gui_4x4,(700,200))
	self.bouton_5x4 = self.screen.blit(self.gui_5x4,(200,500))
	self.bouton_5x5 = self.screen.blit(self.gui_5x5,(600,480))

	pygame.display.flip()

##########################################################################
def FonctionAffichage3(self):
	self.screen.blit(self.z0_fond, (0, 0))
	self.screen.blit(self.gui_c, (0, 0))
	self.screen.blit(self.upmc, (774, 11))

	self.bouton_gui_random = self.screen.blit(self.gui_random,(3000,0))
	self.bouton_gui_convert = self.screen.blit(self.gui_convert,(3000,0))
	self.bouton_3x3 = self.screen.blit(self.gui_3x3,(3000,0))
	self.bouton_4x3 = self.screen.blit(self.gui_4x3,(3000,0))
	self.bouton_4x4 = self.screen.blit(self.gui_4x4,(3000,0))
	self.bouton_5x4 = self.screen.blit(self.gui_5x4,(3000,0))
	self.bouton_5x5 = self.screen.blit(self.gui_5x5,(3000,0))

	self.bouton_parcours1 = self.screen.blit(self.parcours1,(30,180))
	self.bouton_parcours2 = self.screen.blit(self.parcours2,(469,180))
	self.bouton_parcours3 = self.screen.blit(self.parcours3,(30,450))
	self.bouton_parcours4 = self.screen.blit(self.parcours4,(469,450))

	pygame.display.flip()
##########################################################################
def FonctionSonGoku(self):

	Kamehameha = self.generatorX*self.generatorY
	ListeCartes = ["1234","3421","2143","4312","3214","1423","2341","4132","1432","3241","4123","2314","2134","3412","1243","4321","3124","2413","1342","4231","2431","3142","4213","1324"]
  
	CarteDBZ = [str(self.generatorX),str(self.generatorY)]

	for x in xrange(0, Kamehameha):
		CarteDBZ.append(str(x)+"_"+choice(ListeCartes))

	fichierSORTIE = open('fichier.txt','w')
	fichierSORTIE.write('\n'.join(CarteDBZ))
	fichierSORTIE.close()
##########################################################################
def FonctionFinal(self):
	#strFINAL = "../bin/PUZZLE --no-swap --no-rotate fichier.txt " + str(self.typeDeParcours) #pour gain de perf --no-swap --no-rotate mais plus gros risque de ne pas trouver de solution
	strFINAL = "../bin/PUZZLE --resolve-once fichier.txt " + str(self.typeDeParcours) + " --quiet" #assez lent
	print "ON LANCE LE NOYAU"
	self.screen.blit(self.z0_fond, (0, 0))
	self.screen.blit(self.upmc, (774, 11))
	self.screen.blit(self.z0_noyaucherche, (0, 0))
	pygame.display.flip()
	os.system(strFINAL)
	print "LE NOYAU A TERMINE"

	XY_fichier = open("fichier.txt", "r")
	self.generatorX = int(XY_fichier.readline())
	self.generatorY = int(XY_fichier.readline())

	strCHEMIN = str(self.generatorX) +"x"+ str(self.generatorY)

	os.system("cd " + strCHEMIN + " && mv sol1 ../sol1 && mv ..")
	print "IL A MOV LE sol1 et va lancer l'interface"

	if os.path.isfile("sol1"):
		print "IL A TROUVE LE FICHIER sol1"
		#os.system("./interface.py")
		interface.Puzzle()
		pygame.quit()
	else :
		print "AUCUNE SOLUTION"
		self.screen.blit(self.z0_fond, (0, 0))
		self.screen.blit(self.upmc, (774, 11))
		self.screen.blit(self.z0_nosoluce, (0, 0))
		pygame.display.flip()
##########################################################################
		
if __name__ == "__main__":
	Gui()
