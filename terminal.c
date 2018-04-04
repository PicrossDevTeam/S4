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
	char *nom_fic1 = "puzzles_binaires.txt", *nom_fic2 = "nombres_puzzle.txt";
	int test[N][N], colonnes[N][N], lignes[N][N], taille;
	
	init_matrice(test);
	init_matrice(colonnes);
	init_matrice(lignes);
	
	taille = lecture_fic(nom_fic1,1,test,NULL,0);
	afficher_matrice(test,taille,'T');
	
	gen_peripheriques(test,colonnes,lignes,taille);
	
	afficher_matrice(colonnes,taille,'C');
	afficher_matrice(lignes,taille,'L');
	printf("\n");
}
