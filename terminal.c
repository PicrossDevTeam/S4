/**
* \file terminal.c
* \author KAJAK Rémi
* \version 1.0
* \date 03/04/2018
* \brief Fichier permettant la génération d'une partie de Picross à partir d'un terminal de commande.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generation.h"

int main() {
	char *nom_fichier = "puzzles_binaires.txt";
	int test[N][N], colonnes[N][N], lignes[N][N], taille;
	
	init_matrice(test);
	taille = lecture_fic(nom_fichier,1,test,NULL,0);
	
	afficher_matrice(test,'T');
	printf("\nTaille de la rangée : %i\n",taille);
}
