#!/usr/bin/env python
#-*- coding: utf-8 -*-

import pygame, random, os, sys
from random import choice
from pygame.locals import *

class Generator:
	def __init__(self):

		if os.path.isfile("fichier.txt"):
			os.remove("fichier.txt")   
		if os.path.isfile("solution.txt"):
			os.remove("solution.txt") 

#############################################################################################
##			
##			            ___     -._
##			            `-. """--._ `-.
##			               `.      "-. `.
##			 _____           `.       `. \       
##			`-.   """---.._    \        `.\
##			   `-.         "-.  \         `\
##			      `.          `-.\          \_.-""""""""--._
##			        `.           `                          "-.
##			          `.                                       `.    __....-------...
##			--..._      \                                       `--"""""""""""---..._
##			__...._"_-.. \                       _,                             _..-""
##			`-.      """--`           /       ,-'/|     ,                   _.-"
##			   `-.                 , /|     ,'  / |   ,'|    ,|        _..-"
##			      `.              /|| |    /   / |  ,'  |  ,' /        ----"""""""""_`-
##			        `.            ( \  \      |  | /   | ,'  //                 _.-"
##			          `.        .'-\/'""\ |  '  | /  .-/'"`\' //            _.-"
##			    /'`.____`-.  ,'"\  ''''?-.V`.   |/ .'..-P''''  /"`.     _.-"
##			   '(   `.-._""  ||(?|    /'   >.\  ' /.<   `\    |P)||_..-"___.....---
##			     `.   `. "-._ \ ('   |     `8      8'     |   `) /"""""    _".""
##			       `.   `.   `.`.b|   `.__            __.'   |d.'  __...--""
##			         `.   `.   ".`-  .---      ,-.     ---.  -'.-""
##			           `.   `.   ""|      -._      _.-      |""
##			             `.  .-"`.  `.       `""""'       ,'
##			               `/     `.. ""--..__    __..--""
##			                `.      /7.--|    """"    |--.__
##			                  ..--"| (  /'            `\  ` ""--..
##			               .-"      \\  |""--.    .--""|          "-.
##			              <.         \\  `.    -.    ,'       ,'     >
##			             (P'`.        `%,  `.      ,'        /,' .-"'?)
##			             P    `. \      `%,  `.  ,'         /' .'     \
##			            | --"  _\||       `%,  `'          /.-'   .    )
##			            |       `-.""--..   `%..--"""\\"--.'       "-  |
##			            \          `.  .--"""  "\.\.\ \\.'       )     |
##			
#############################################################################################			
##
##
##
##
		SanGoku = 3				# 2, 3, 4, 5, 6, 7, etc. 	<<< a modif a la mano
		SanGohan = 3
		GenereAussiUnFichierSolution = 1	# 1 ou 0 			<<< a modif a la mano (a titre d'exemple)
##
##
##
##
#############################################################################################	

		Kamehameha = SanGoku*SanGohan
		ListeCartes = ["1234","3421","2143","4312","3214","1423","2341","4132","1432","3241","4123","2314","2134","3412","1243","4321","3124","2413","1342","4231","2431","3142","4213","1324"]
          
		self.CarteDBZ = [str(SanGoku),str(SanGohan)]

		for x in xrange(0, Kamehameha):
			self.CarteDBZ.append(str(x)+"_"+choice(ListeCartes))

		fichierSORTIE = open('fichier.txt','w')
		fichierSORTIE.write('\n'.join(self.CarteDBZ))
		fichierSORTIE.close()

		if GenereAussiUnFichierSolution == 1 :

			#self.CarteVEGETA = [str(SanGoku),str(SanGohan)]
			#for x in xrange(0, Kamehameha):
			#	self.CarteVEGETA.append(str(x)+"_"+choice(ListeCartes))

			#fichierSOL = open('solution.txt','w')
			#fichierSOL.write('\n'.join(self.CarteVEGETA))
			#fichierSOL.close()
			os.system("../bin/PUZZLE fichier.txt 1")
	
if __name__ == "__main__":
	Generator()
