/**
* \file terminal.c
* \author KAJAK Rémi
* \version 1.0
* \date 03/04/2018
* \brief Fichier permettant de jouer une partie de Picross à partir d'un terminal de commande.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "matrice.h"

/**
* \fn dimension_matrice(int puzzle)
* \brief Fonction qui vérifie si les cases de la grille du joueur est correcte par rapport à la grille solution.
*
* \param puzzle 
*
* \return La difficulté correspondant au numéro du puzzle
*/
t_difficulte dimension_matrice(int puzzle){
	if(puzzle == 1 || puzzle == 2)
		return facile;
	else if(puzzle == 3 || puzzle == 4)
		return normal;
	else
		return difficile;
}

int main() {
	char *fic = "puzzles_binaires.txt";
	t_difficulte dim_mat;
	t_couleurs *grille_jeu = NULL, *grille_soluce = NULL;
	int *grille_gauche = NULL, *grille_haut = NULL;
	int continuation, continuer_partie = 1, jeu_gagne = 0, nb_erreurs, num_puzzle = 1, puzzle_actuel;

	while(num_puzzle < 7 && continuer_partie == 1) {
		dim_mat = dimension_matrice(num_puzzle);
		
		// Matrices de type t_couleurs
		grille_jeu = init_matrice_prin(dim_mat);
		grille_soluce = init_matrice_prin(dim_mat);
		
		// Matrices de type int
		grille_haut = init_matrice_peri(dim_mat);
		grille_gauche = init_matrice_peri(dim_mat);
		
		lecture_fic_v1(fic,num_puzzle,grille_soluce,dim_mat);
		gen_peripheriques(grille_soluce,grille_haut,grille_gauche,dim_mat);
		puzzle_actuel = num_puzzle;
		
		while(puzzle_actuel == num_puzzle && continuer_partie == 1) {
			do {
				system("clear");
				affichage_jeu(grille_haut,grille_gauche,grille_jeu,dim_mat);
			} while(saisir_coord(grille_jeu,dim_mat) != 1);
			
			nb_erreurs = verifierGrille(grille_soluce,grille_jeu,dim_mat);
			continuation = -1;
			
			if(nb_erreurs >= 1) {
				printf("\nVotre solution est fausse, elle comporte %i erreurs ! Entrez 1 pour continuer ou 0 pour arrêter : ",nb_erreurs);
				
				do {
					scanf("%i",&continuation);
					
					if(continuation < 0 || continuation > 1) printf("\nVous n'avez pas saisi un choix valide... Veuillez recommencer : ");
				} while(continuation < 0 || continuation > 1);
				
				if(continuation == 1) continuer_partie = 1;
				else continuer_partie = 0;
			}
			else {
				printf("\nFélicitation ! Si vous souhaitez accéder au niveau suivant, entrez 1 pour continuer. Pour arrêter, entrez 0 : ");
				
				do {
					scanf("%i",&continuation);
					
					if(continuation < 0 || continuation > 1) printf("\nVous n'avez pas saisi un choix valide... Veuillez recommencer : ");
				} while(continuation < 0 || continuation > 1);
				
				if(continuation == 1) {
					num_puzzle++;
					continuer_partie = 1;
			
					if(num_puzzle == 7) jeu_gagne = 1;
				}
				else continuer_partie = 0;
			}
		}
		// Destruction des matrices de type t_couleurs
		detruire_matrice_prin(grille_jeu);
		detruire_matrice_prin(grille_soluce);
		// Destruction des matrices de type int
		detruire_matrice_peri(grille_gauche);
		detruire_matrice_peri(grille_haut);
	}
	if(jeu_gagne == 1) printf("\nFélicitation, vous avez réussi le jeu du Picross !");
	printf("\nMerci d'avoir joué à notre jeu ! À une prochaine fois !\n\n");
	return 0;
}
