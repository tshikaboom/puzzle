#!/usr/bin/env python
#-*- coding: utf-8 -*-

import pygame, time, random, os, sys, webbrowser
from math import sqrt
from pygame.locals import *

class Dark:
	def __init__(self):

                # Variables et images (c'est ici qu'on charge les images en mémoire)

		if os.path.isfile("fichier.txt"):
			os.remove("fichier.txt")
		if os.path.isfile("solution.txt"):
			os.remove("solution.txt")

                pygame.init()

		largeur_ecran = 1024
		hauteur_ecran = 768

		directory = "cartes"
		self.number_of_files = len([item for item in os.listdir(directory) if os.path.isfile(os.path.join(directory, item))])

		self.scale_image = (largeur_ecran/self.number_of_files) - (self.number_of_files/3)

		n_Ximprim = 16/self.number_of_files

		self.fondPUR = pygame.image.load("images/fond.jpg")               
                self.fond = pygame.transform.smoothscale(self.fondPUR, (largeur_ecran, hauteur_ecran))
                
                self.font = pygame.font.Font(None, (320/self.number_of_files))
                self.fontpetit = pygame.font.Font(None, (160/self.number_of_files))

                ###

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

                ###

		self.CarteDELTA = [str(int(sqrt(self.number_of_files))), str(int(sqrt(self.number_of_files)))]

		###

		liste_des_cartes = os.listdir(directory)
		CarteLISTE = []

		for i in range(self.number_of_files):
			CarteLISTE.append(pygame.image.load(directory+"/"+liste_des_cartes[i]))

		# Options de Pygame (ici, la mise en place du fond d'écran et de la résolution du logiciel)
		self.screen = pygame.display.set_mode([largeur_ecran, hauteur_ecran], 0, 24)
		pygame.display.set_caption("Convertisseur")
		self.screen.blit(self.fond, (0, 0))
                pygame.display.flip()

                ###################

		# Boucle Principale (le programme attend des pressions de touche pour démarrer nos petites fonctions)
                while 1:
                        pygame.event.wait()
                        key = pygame.key.get_pressed()                        

                        if key[pygame.K_RETURN] :

                                #self.screen.blit(self.CarteA, (10, 25))

				n_Ximprim_Alpha = n_Ximprim

				for i in range(self.number_of_files):
					self.screen.blit((pygame.transform.smoothscale(CarteLISTE[i], (self.scale_image, self.scale_image))), (n_Ximprim_Alpha, 25))
					n_Ximprim_Alpha = n_Ximprim_Alpha + self.scale_image + (self.number_of_files/3)
                                
                                pygame.display.flip()

			##########################################################################

			elif key[pygame.K_SPACE] :

				n_Ximprim_Beta = n_Ximprim

				for i in range(self.number_of_files):
					tri_couleur(self,i,CarteLISTE[i],n_Ximprim_Beta)
					n_Ximprim_Beta = n_Ximprim_Beta + self.scale_image + (self.number_of_files/3)
				
				print self.CarteDELTA

				fichierSORTIE = open('fichier.txt','w')
				fichierSORTIE.write('\n'.join(self.CarteDELTA))
				fichierSORTIE.close()
				#webbrowser.open('fichier.txt') <<<<<<<<< si on veut ouvrir le fichier fichier automatiquement
				Houston = 0
				time.sleep(0.1)

                        ##########################################################################
			# LANCEMENT DU MOTEUR
                        ##########################################################################
			#	os.system("commande qui lance le moteur")
				os.system("../bin/PUZZLE fichier.txt 1")

				time.sleep(0.1)
				while Houston == 0 :
					if os.path.isfile("	sol0"):
						Houston = 1
					time.sleep(1)

				os.system("./interface.py")

				#break <<<<<<<<<<<<<< pour automatiquement fermer le convertisseur une fois qu'on a l'interface
								
                                
                        ##########################################################################

			elif key[pygame.K_LCTRL] :

                                m=0.3

                        ##########################################################################

			elif key[pygame.K_TAB] : #Le Reset
                                self.screen.blit(self.fond, (0, 0))
                                pygame.display.flip()

                        ##########################################################################                      

			elif key[pygame.K_ESCAPE] : #Le tueur de boucle, que l'on active via la touche Echap
                                break

##########################################################################
#Fonction qui trouve l'element le plus courant dans une liste
##########################################################################
def most_common(items):
	if not items:
		raise ValueError
	fitems = [] 
	best_idx = 0
	for item in items:   
		item_missing = True
		i = 0
		for fitem in fitems:  
			if fitem[0] == item:
				fitem[1] += 1
				d = fitem[1] - fitems[best_idx][1]
				if d > 0 or (d == 0 and fitems[best_idx][2] > fitem[2]):
					best_idx = i
				item_missing = False
				break
			i += 1
		if item_missing:
			fitems.append([item, 1, i])
	return items[best_idx]
##########################################################################
#Fonction qui trie les couleurs
##########################################################################
def tri_couleur(self,id,xCARTE,xYATA):
	
                                hautSTR = basSTR = gaucheSTR = droiteSTR = " "

                                hautTab = []
                                basTab = []
                                gaucheTab = []
                                droiteTab = []
                                
                                #-------------------------------------------------------                                
                                for x in xrange(20, 79):
                                        for y in xrange(0, 19):
                                                hautTab.append(xCARTE.get_at((x, y)))
                                                hautMajoritaire = most_common(hautTab)

                                haut = hautMajoritaire

                                if haut.r >= 128 and haut.g < 128 and haut.b < 128 :
                                        hautSTR = "1"

                                elif haut.r < 128 and haut.g < 128 and haut.b >= 128 :
                                        hautSTR = "3"

                                elif haut.r < 128 and haut.g >= 128 and haut.b < 128 :
                                        hautSTR = "4"

                                elif hautSTR == " " :
                                        hautSTR = "2"
                                #-------------------------------------------------------                          
                                for x in xrange(20, 79):
                                        for y in xrange(80, 99):
                                                basTab.append(xCARTE.get_at((x, y)))
                                                basMajoritaire = most_common(basTab)

                                bas = basMajoritaire

                                if bas.r >= 128 and bas.g < 128 and bas.b < 128 :
                                        basSTR = "1"

                                elif bas.r < 128 and bas.g < 128 and bas.b >= 128 :
                                        basSTR = "3"

                                elif bas.r < 128 and bas.g >= 128 and bas.b < 128 :
                                        basSTR = "4"

                                elif basSTR == " " :
                                        basSTR = "2"
                                #-------------------------------------------------------                                
                                for x in xrange(0, 19):					#<<<<<<<<<<<<<<< à changer
                                        for y in xrange(20, 79):
                                                gaucheTab.append(xCARTE.get_at((x, y)))
                                                gaucheMajoritaire = most_common(gaucheTab)

                                gauche = gaucheMajoritaire

                                if gauche.r >= 128 and gauche.g < 128 and gauche.b < 128 :
                                        gaucheSTR = "1"

                                elif gauche.r < 128 and gauche.g < 128 and gauche.b >= 128 :
                                        gaucheSTR = "3"

                                elif gauche.r < 128 and gauche.g >= 128 and gauche.b < 128 :
                                        gaucheSTR = "4"

                                elif gaucheSTR == " " :
                                        gaucheSTR = "2"
                                #-------------------------------------------------------                                
                                for x in xrange(80, 99):					#<<<<<<<<<<<<<<< à changer
                                        for y in xrange(20, 79):
                                                droiteTab.append(xCARTE.get_at((x, y)))
                                                droiteMajoritaire = most_common(droiteTab)

                                droite = droiteMajoritaire

                                if droite.r >= 128 and droite.g < 128 and droite.b < 128 :
                                        droiteSTR = "1"

                                elif droite.r < 128 and droite.g < 128 and droite.b >= 128 :
                                        droiteSTR = "3"

                                elif droite.r < 128 and droite.g >= 128 and droite.b < 128 :
                                        droiteSTR = "4"

                                elif droiteSTR == " " :
                                        droiteSTR = "2"
                                #-------------------------------------------------------

                                NOMBRE_str = hautSTR+basSTR+gaucheSTR+droiteSTR
                                CartePourPrint = str(id) + "_" + str(NOMBRE_str)
                                IMAGE_str = "self.carte" + NOMBRE_str

                                self.convertNOMBRE = self.font.render(CartePourPrint, True, (255,255,255))
                                self.screen.blit(self.convertNOMBRE, (xYATA+(135/self.number_of_files), 274))
                                #self.screen.blit(eval(IMAGE_str), (xYATA, 300))

				self.screen.blit((pygame.transform.smoothscale(eval(IMAGE_str), (self.scale_image, self.scale_image))), (xYATA, 300))
                                
                                self.convertHaut = self.fontpetit.render(str(haut), True, (haut.r, haut.g, haut.b))
                                self.screen.blit(self.convertHaut, (xYATA+2, 500))

                                self.convertBas = self.fontpetit.render(str(bas), True, (bas.r, bas.g, bas.b))
                                self.screen.blit(self.convertBas, (xYATA+2, 550))

                                self.convertGauche = self.fontpetit.render(str(gauche), True, (gauche.r, gauche.g, droite.b))
                                self.screen.blit(self.convertGauche, (xYATA+2, 600))

                                self.convertDroite = self.fontpetit.render(str(droite), True, (droite.r, droite.g, droite.b))
                                self.screen.blit(self.convertDroite, (xYATA+2, 650))
                                
                                pygame.display.flip()
				self.CarteDELTA.append(CartePourPrint)

##########################################################################
	
if __name__ == "__main__":
	Dark()
