/**
* \file generation.c
* \author KAJAK Rémi
* \version 1.2
* \date 02/04/2018
* \brief Fichier ayant servi à l'élaboration de la fonction de lecture du fichier texte qui contient les nombres générateurs de la matrice principale et la fonction de génération de la matrice solution.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generation.h"

/**
* \fn init_matrice(int mat[N][N])
* \brief Initialise une matrice avec des 0.
* \param mat Une matrice de taille fixe
* \return Ne retourne aucun résultat
*/
void init_matrice(int mat[N][N]) { // Fonction test pour ce fichier
	int i, j;
	
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			mat[i][j] = 0;
		}
	}
}

/**
* \fn afficher_matrice(int mat[N][N], char cle)
* \brief Affiche une matrice reçue en paramètre selon un modèle prédéfini.
* \param mat Une matrice de taille fixe
* \param taille_max La taille maximum relevée pour les matrices périphériques
* \param cle Un caractère qui définit le mode d'affichage : "C" pour afficher horizontalement les nombres de la matrice périphérique des colonnes, "L" pour afficher verticalement les nombres de la matrice périphérique des lignes et "S" pour afficher une grille complète
* \return Ne retourne aucun résultat
*/
void afficher_matrice(int mat[N][N], int taille_max, char cle) {
	int i, j, k = 0, mat_inversee[N][N];
	
	printf("\n");
	if(cle == 'C') {
		printf("Matrice périphérique des colonnes :\n\n");
		for(i = taille_max-1; i >= 0; i--) {
			for(j = 0; j < taille_max; j++) {
				if(i == 0) printf("%i ",mat[i][j]);
				else {
					if(mat[i][j] > 0) printf("%i ",mat[i][j]);
					else printf("  ");
				}
			}
			printf("\n");
		}
		
	}
	else if(cle == 'L') {
		init_matrice(mat_inversee);
		
		// On attribue les nombres dans une seconde matrice pour éviter une lecture erronée à l'affichage (nombres inversés)
		for(i = 0; i < N; i++) {
			for(j = N-1; j >= 0; j--) {
				if(mat[i][j] > 0) {
					mat_inversee[i][k] = mat[i][j];
					k++;
				}
			}
			k = 0;
		}
		printf("Matrice périphérique des lignes :\n\n");
		
		for(i = 0; i < taille_max; i++) {
			for(j = taille_max-1; j >= 0; j--) {
				if(j == 0) printf("%i ",mat_inversee[i][j]);
				else {
					if(mat[i][j] > 0) printf("%i ",mat_inversee[i][j]);
					else printf("  ");
				}
			}
			printf("\n");
		}
	}
	else {
		printf("Matrice solution :\n\n");
		for(i = 0; i < taille_max; i++) {
			for(j = 0; j < taille_max; j++) printf("%i ",mat[i][j]);
			printf("\n");
		}
	}
}

void afficher_matrice_claire(int mat[N][N]) { // Fonction test pour ce fichier
	int i, j;
	
	printf("\nMatrice solution éclaircie :\n\n");
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			if(mat[i][j]%2 == 0) printf("%i ",0);
			else printf("%i ",1);
		}
		printf("\n");
	}
}

/**
* \fn lecture_fic(char *nom, int niveau, int C[N][N], int L[N][N])
* \brief Lit un fichier avec un format spécifique et renseigne les nombres contenus dans les matrices périphériques. Elle renvoie la largeur maximum d'une rangée pour améliorer les affichages et les traitements des matrices.
* \param nom Nom du fichier texte à analyser
* \param niveau Nombre du puzzle à trouver dans le fichier
* \param C La matrice périphérique des colonnes
* \param L La matrice périphérique des lignes
* \param solveur Booléen qui indique si la lecture du fichier concerne le solveur ou pas
* \return Retourne la largeur maximum d'une matrice
*/
int lecture_fic(char *nom_fic, int niveau, int C[N][N], int L[N][N], int solveur) {
	FILE * fic_gen;
	char cle[5] = "PCLFD", carac;
	int colonne = 0, ligne = 0, largeur_max = 0, num_puz, nb_case, i;

	fic_gen = fopen(nom_fic,"r");
	fscanf(fic_gen,"%c %i",&carac,&num_puz);

	while(!feof(fic_gen)) { // Tant que la fin du fichier n'a pas été atteinte
		if(carac == cle[0] && num_puz == niveau) { // Si on trouve le bon niveau de puzzle
			if(solveur == 1) {
				for(i = 1; i <= 2; i++) { // Lecture successive des clés
					colonne = 0;
					ligne = 0;
					
					while(carac != cle[i]) fscanf(fic_gen,"%c",&carac); // Tant que l'on n'a pas trouvé la clé de départ (ici, "C")

					while(carac != cle[i+1]) { // Tant que l'on n'a pas trouvé la clé de fin
						if(carac == ' ' || carac == '\n') {
							fscanf(fic_gen,"%i",&nb_case);
							if(cle[i] == 'C') C[colonne][ligne] = nb_case;
							else if(cle[i] == 'L') L[ligne][colonne] = nb_case;
							colonne++;
							if(colonne > largeur_max) largeur_max = colonne;
						}
						else if(carac == '+') {
							ligne++;
							colonne = 0;
						}
						fscanf(fic_gen,"%c",&carac);
					}
				}
			} 
			else {
				while(carac != cle[4]) fscanf(fic_gen,"%c",&carac); // Tant que l'on n'a pas trouvé la clé de départ (ici, "D")
				
				while(carac != cle[3]) { // Tant que l'on n'a pas trouvé la clé de fin
					if(carac == ' ' || carac == '\n') {
						fscanf(fic_gen,"%i",&nb_case);
						C[ligne][colonne] = nb_case;
						colonne++;
						if(colonne > largeur_max) largeur_max = colonne;
					}
					else if(carac == '+') {
						ligne++;
						colonne = 0;
					}
					fscanf(fic_gen,"%c",&carac);
				}
			}
		}
		fscanf(fic_gen,"%c %i",&carac,&num_puz);
	}
	fclose(fic_gen);
	return largeur_max;
}

void gen_peripheriques(int S[N][N], int C[N][N], int L[N][N], int taille_max) {
	int i, j, nb_groupes, taille_groupe;
	
	// Remplissage de la matrice périphérique des colonnes
	
	
	// Remplissage de la matrice périphérique des lignes
	for(i = 0; i < taille_max; i++) {
		nb_groupes = 0;
		taille_groupe = 0;
		
		for(j = 0; j < taille_max; j++) {
			if(S[i][j]%2 == 1) {
				taille_groupe++;
				
				if(j == taille_max-1) L[i][nb_groupes] = taille_groupe;
			}
			else if(S[i][j]%2 == 0 && S[i][j-1]%2 == 1) {
				L[i][nb_groupes] = taille_groupe;
				taille_groupe = 0;
				nb_groupes++;
			}
		}
	}
}

/**
* \fn init_compteur_groupes(int S[N][N], int nombres[N], int rangee, char type_rangee)
* \brief Initialise une liste d'entiers avec, pour chaque entier, le nombre de cases pleines d'un groupe analysé verticalement ou horizontalement.
* \param S La matrice solution qui contient les données nécessaires à l'anaylse
* \param nombres La liste cotnenant chaque nombre qui correspond individuellement à un groupe de cases pleines trouvé par la fonction 
* \param rangee L'indice numérique de la rangée analysée
* \param type_rangee La nature de la rangée (ligne ou colonne)
* \return La taille finale de la liste d'entiers.
*/
int init_compteur_groupes(int S[N][N], int nombres[N], int rangee, char type_rangee) {
	int i, j, taille = 0;
	
	// Avant toute opération, on initialise la liste de vérification des nombres
	for(i = 0; i < N; i++) nombres[i] = 0;
	
	if(type_rangee == 'C') { // Rangée de type colonne
		i = 0;
		j = rangee;
	}
	else if(type_rangee == 'L') { // Rangée de type ligne
		i = rangee;
		j = 0;
	}
	
	while(i < N && j < N) {
		if(S[i][j]%2 == 1) nombres[taille] = nombres[taille] + 1;	// Si on rentre dans un groupe de cases pleines
	
		if(type_rangee == 'C') {
			if(i != 0 && S[i-1][j]%2 == 1 && S[i][j]%2 == 0) taille++; // Si on sort du groupe vertical vérfié
			i++;
		}
		else {
			if(j != 0 && S[i][j-1]%2 == 1 && S[i][j]%2 == 0) taille++; // Si on sort du groupe horizontal vérfié
			j++;
		}
	}
	return taille;
}

/**
* \fn verif_adequation_globale(int soluce[N][N], int C[N][N], int L[N][N], int respect_C[N], int respect_L[N])
* \brief Lorsqu'une itération de la boucle principale de la fonction "gen_solution" a été effectuée, cette fonction a pour rôle de vérifier l'état de toutes les rangées. Elle remplie les tableaux "respect_" avec un indicateur numérique : 0 pour une rangée qui ne respecte pas ses règles, 1 pour un résultat positif. 
* \param solune La matrice solution
* \param C La matrice périphérique des colonnes
* \param L La matrice périphérique des lignes
* \param respect_C Le tableau qui va contenir les résultats du test pour les colonnes des matrices soluce et C
* \param respect_L Le tableau qui va contenir les résultats du test pour les lignes des matrices soluce et L
* \return Ne retourne aucune variable
*/
void verif_adequation_globale(int soluce[N][N], int C[N][N], int L[N][N], int respect_C[N], int respect_L[N]) {
	int i, j;
	
	// On commence par vérifier l'état des lignes
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			
		}
	}
	// Puis on vérifie l'état des colonnes
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
		
		}
	}
}

/**
* \fn adequation_rangee_et_nombres(int S[N][N], int periph[N][N], int nb_groupes_defaut, int rangee, char type_rangee)
* \brief Vérifie dans la matrice solution, pour une matrice périphérique, un compteur d'indice et une rangée précise donnés, si le remplissage d'une rangée de type "ligne" correspond aux nombres de la rangée de type "colonne" (et inversement).
* \param S La matrice solution dans laquelle on vérifie l'adéquation d'une rangée par rapport à une autre
* \param periph La matrice périphérique qui contient les nombres nécessaires à la vérification
* \param nb_groupes_defaut La taille normale du groupe de nombres de la rangée
* \param rangee La rangée de la matrice solution qui va être vérifiée
* \param type_rangee La nature de la rangée (ligne ou colonne)
* \return Cinq valeurs possibles : 2 si un groupe possède plus de cases que prévu, 1 si des groupes supplémentaires sont détectés, 0 si les données correspondent, -1 s'il reste des groupes à créer, -2 s'il reste des cases à compléter
*/
int adequation_rangee_et_nombres(int S[N][N], int periph[N][N], int nb_groupes_defaut, int rangee, char type_rangee) {
	int i, j, k, taille_groupe[nb_groupes_defaut], nb_groupes = 0;
	
	nb_groupes = init_compteur_groupes(S,taille_groupe,rangee,type_rangee);
	
	printf("\nNombre de groupes par défaut : %i, rangée %c vérifiée : %i",nb_groupes_defaut,type_rangee,rangee);
	printf("\nNombre de groupes identifiés dans la rangée : %i",nb_groupes);
	for(k = 0; k < nb_groupes; k++) printf("\nNombre de cases pour le groupe n°%i : %i",k+1,taille_groupe[k]);
	k = 0;
	
	while(k < nb_groupes_defaut) {
		if(nb_groupes < nb_groupes_defaut) return -1;		// Moins de groupes que prévu
		else if(nb_groupes > nb_groupes_defaut) return 1;	// Plus de groupes que prévu (cas improbable, néanmoins)
		else {
			if(type_rangee == 'C') {
				if(taille_groupe[k] < periph[k][j]) return -2;		// Un groupe possède moins de cases que prévu
				else if(taille_groupe[k] > periph[k][j]) return 2;	// Un groupe possède plus de cases que prévu
			}
			else if(type_rangee == 'L') {
				if(taille_groupe[k] < periph[i][k]) return -2;
				else if(taille_groupe[k] > periph[i][k]) return 2;
			}
		}
		k++;
	}
	return 0; // La rangée analysée correspond aux attentes de la rangée de la matrice périphérique
}

/**
* \fn init_compteurs_periph(int periph_C[N][N], int cptC[N], int periph_L[N][N], int cptL[N])
* \brief Initialise les compteurs des matrices périphériques. Leur rôle est d'indiquer combien de nombres sont contenus dans chaque rangée (ligne/colonne) de chaque matrice périphérique. Ces compteurs sont utilisés dans la fonction "gen_solution".
* \param periph_C La matrice périphérique des colonnes
* \param cptC Tableau d'indices de la matrice périphérique des colonnes
* \param periph_L La matrice périphérique des lignes
* \param cptL Tableau d'indices de la matrice périphérique des lignes
* \return Ne retourne aucun résultat
*/
void init_compteurs_periph(int periph_C[N][N], int cpt_C[N], int periph_L[N][N], int cpt_L[N]) {
	int i, j;
	
	// Initialisation des colonnes des listes
	for(i = 0; i < N; i++) {
		cpt_C[i] = 0;
		cpt_L[i] = 0;
	}
	
	// Remplissage des listes avec les données des matrices périphériques
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			if(periph_C[j][i] > 0) cpt_C[i] = cpt_C[i] + 1;
			if(periph_L[i][j] > 0) cpt_L[i] = cpt_L[i] + 1;
		}
	}
}

/**
* \fn gen_solution(int S[N][N], int C[N][N], int L[N][N])
* \brief Initialise la matrice solution grâce aux données des matrices périphériques. Pour gérer le remplissage progressif et les cas d'erreur, un système de numérotation des cases a été mis en place : 0 => case vide non-testée, 1 => case cochée, 2 => case vide déjà testée, 3 => case cochée validée.
* \param S La matrice solution qui va contenir le motif du puzzle
* \param C La matrice périphérique des colonnes (situé en haut de la grille du Picross)
* \param L La matrice périphérique des lignes (situé à gauche de la grille du Picross)
* \param largeur La taille maximum des rangées pour les matrices périphériques
* \return Ne retourne aucun résultat
*/
void gen_solution(int S[N][N], int C[N][N], int L[N][N], int largeur) {
	int nombres_C[N], nombres_L[N], completionC[N], completionL[N]; // Tableaux à une dimension
	int i, j, k, l, decalage, verif, lecture_grille = 0, respect_regles = 0, tour_ligne = 1;
	
	// Dans un premier temps, on dénombre les chiffres présents dans chacune des lignes des matrices périphériques
	init_compteurs_periph(C,nombres_C,L,nombres_L);
	
	// Initialisation des variables d'incrémentation
	i = 0;
	j = 0;
	
	afficher_matrice(C,largeur,'C');
	
	// Ensuite, on boucle la matrice jusqu'à ce que la solution soit correctement générée
	while(respect_regles != 1) {
		printf("\nLecture de la grille n°%i",lecture_grille);
		printf("\nTour n°%i",i);
		
		// Lorsque toutes les rangées auront été lues au moins une fois pour la complétion, on effectue une vérification globale pour passer à la troisième étape de la génération
		if(lecture_grille >= 1) verif_adequation_globale(S,C,L,completionC,completionL);
		
		if(tour_ligne == 1) { // On commence par remplir les lignes
			// On remplit les cases en fonction du ou des nombres indiqués dans la colonne de la matrice périphérique
			if(nombres_L[i] > 0) {
				decalage = j;
			
				for(k = 0; k < nombres_L[i]; k++) {
					if(L[i][k] > 0 && L[i][k] < N) {
						for(l = 0; l < L[i][k]; l++) {
							S[i][decalage] = 1;
							decalage++;
						}
						if(lecture_grille == 0) decalage++; // On effectue un décalage d'une unité entre chaque groupe à la première lecture
					}
					else if(L[i][k] == N) for(l = 0; l < N; l++) S[i][l] = 3;
				}
			}
			else for(l = 0; l < N; l++) S[i][l] = 2;
			
			if(lecture_grille == 0) {
				if(L[i][i] > 0 && L[i][i] < N) {
					verif = adequation_rangee_et_nombres(S,C,nombres_C[i],j,'C');
					printf("\nVérification : %i ",verif);
			
					if(verif == 0) { // Si la complétion correspond aux rangées lues
						i++;
						j++;
					}
					else if(verif == -1) i++;
					else if(verif == -2) j++;
				}
				else i++;
			}
			
			if(i >= N) {
				lecture_grille++;
				tour_ligne = 0;
				i = 0;
				j = 0;
			}
			afficher_matrice(S,largeur,'S');
			printf("\n\n");
		}
		else { // Puis on passe au remplissage des colonnes
			verif_adequation_globale(S,C,L,completionC,completionL);
			
			// On remplit les cases en fonction du ou des nombres indiqués dans la colonne de la matrice périphérique
			if(nombres_C[j] > 0) {
				decalage = i;
			
				for(k = 0; k < nombres_C[j]; k++) {
					if(C[k][j] > 0 && C[k][j] < N) {
						for(l = 0; l < C[k][j]; l++) {
							S[decalage][j] = 1;
							decalage++;
						}
						decalage++; // On effectue un décalage d'une unité entre chaque groupe à la première lecture
					}
					else if(C[i][k] == N) for(l = 0; l < N; l++) S[i][l] = 3;
				}
			}
			else for(l = 0; l < N; l++) S[i][l] = 2;
			
			if(L[j][j] > 0 && L[j][j] < N) {
				verif = adequation_rangee_et_nombres(S,L,nombres_L[j],i,'L');
				printf("\nVérification : %i ",verif);
			
				if(verif == 0) { // Si la complétion correspond aux rangées lues
					i++;
					j++;
				}
				else if(verif == -1) j++;
				else if(verif == -2) i++;
			}
			else j++;
			
			if(j >= N) {
				lecture_grille++;
				tour_ligne = 0;
				i = 0;
				j = 0;
			}
			afficher_matrice(S,largeur,'S');
			printf("\n\n");
		}
		if(lecture_grille == 1) respect_regles = 1;
	}
}

// Main test pour ce fichier
/*
* Cas n°1 : Succès avec une seule itération de gen_solution
* Cas n°2 : Succès avec une seule itération de gen_solution - À tester avec deux itérations (seconde étape de la génération)
* Cas n°3 : Échec - Erreur de segmentation avec une seule itération de gen_solution
* Cas n°4 : Échec avec une seule itération de gen_solution
* Cas n°5 : Testé rapidement - aucune analyse effectuée entre la génération et le résultat attendu (échec certain avec une seule itération)

int main() {
	char *saisie = "nombres_puzzle.txt";
	int matC[N][N], matL[N][N], soluce[N][N], taille;
	
	init_matrice(soluce);
	init_matrice(matC);
	init_matrice(matL);
	taille = lecture_fic(saisie,4,matC,matL,1);
	
	afficher_matrice(matC,taille,'C');
	afficher_matrice(matL,taille,'L');
	
	//gen_solution(soluce,matC,matL,taille);
	//afficher_matrice_claire(soluce);
	printf("\n");
} //*/
