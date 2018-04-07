/**
* \file generation.c
* \author KAJAK Rémi
* \version 1.2
* \date 07/04/2018
* \brief Fichier ayant servi à l'élaboration des différentes fonctions de génération des trois matrices principales.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Case.h"
#include "generation.h"

/**
* \fn init_matrice(int mat[N][N])
* \brief Initialise une matrice avec des 0.
* \param taille_max La taille maximum de la matrice à initialiser
* \return Une matrice de type int allouée dynamiquement
*/
int* init_matrice(int taille_max) {
	int i, j, *mat = malloc(sizeof(int));
	
	for(i = 0; i < taille_max; i++) {
		for(j = 0; j < taille_max; j++) {
			mat[taille_max*i+j] = 0;
		}
	}
}

/**
* \fn afficher_matrice(int *mat, int niveau, int taille, char cle)
* \brief Affiche une matrice reçue en paramètre selon un modèle prédéfini.
* \param mat Une matrice de taille fixe
* \param niveau Un chiffre indiquant la taille de la longueur des matrices
* \param taille La taille maximum relevée pour les matrices périphériques
* \param cle Un caractère qui définit le mode d'affichage : "C" pour afficher horizontalement les nombres de la matrice périphérique des colonnes, "L" pour afficher verticalement les nombres de la matrice périphérique des lignes et "S" pour afficher une grille complète
* \return Ne retourne aucun résultat
*/
void afficher_matrice(int *mat, int niveau, int taille, char cle) {
	int i, j, k = 0, *mat_inversee = malloc(taille * taille * sizeof(int));
	
	printf("\n");
	if(cle == 'C') {
		printf("Matrice périphérique des colonnes :\n\n");
		for(i = taille-1; i >= 0; i--) {
			for(j = 0; j < taille; j++) {
				if(i == 0) printf("%i ",mat[taille*i+j]);
				else {
					if(mat[taille*i+j] > 0) printf("%i ",mat[taille*i+j]);
					else printf("  ");
				}
			}
			printf("\n");
		}
		
	}
	else if(cle == 'L') {
		init_matrice(mat_inversee);
		
		// On attribue les nombres dans une seconde matrice pour éviter une lecture erronée à l'affichage (nombres inversés)
		for(i = 0; i < taille; i++) {
			for(j = taille-1; j >= 0; j--) {
				if(mat[taille*i+j] > 0) {
					mat_inversee[taille*i+k] = mat[taille*i+j];
					k++;
				}
			}
			k = 0;
		}
		printf("Matrice périphérique des lignes :\n\n");
		
		for(i = 0; i < taille; i++) {
			for(j = taille-1; j >= 0; j--) {
				if(j == 0) printf("%i ",mat_inversee[taille*i+j]);
				else {
					if(mat_inversee[taille*i+j] > 0) printf("%i ",mat_inversee[taille*i+j]);
					else printf("  ");
				}
			}
			printf("\n");
		}
	}
	else {
		printf("Matrice solution :\n\n");
		for(i = 0; i < taille; i++) {
			for(j = 0; j < taille; j++) printf("%i ",mat[taille*i+j]);
			printf("\n");
		}
	}
}

/**
* \fn lecture_fic(char *nom, int puzzle, int *colonnes, int *lignes, int taille, _Bool solveur)
* \brief Lit un fichier avec un format spécifique et renseigne les nombres contenus dans les matrices périphériques. Elle renvoie la largeur maximum d'une rangée pour améliorer les affichages et les traitements des matrices.
* \param nom Nom du fichier texte à analyser
* \param puzzle Numéro du puzzle à trouver dans le fichier
* \param colonnes La matrice périphérique des colonnes ou la matrice solution (version 1 du jeu)
* \param lignes La matrice périphérique des lignes
* \param taille La taille des matrices
* \param solveur Booléen qui indique si la lecture du fichier concerne le solveur ou pas
* \return Retourne la largeur maximum d'une matrice
*/
int lecture_fic(char *nom_fic, int puzzle, int *colonnes, int *lignes, int taille, _Bool solveur) {
	FILE * fic_gen;
	char *cle = "PCLFD", carac;
	int rangee = 0, curseur = 0, largeur_max = 0, num_puz, nb_case, i;

	fic_gen = fopen(nom_fic,"r");
	fscanf(fic_gen,"%c %i",&carac,&num_puz);

	while(!feof(fic_gen)) { // Tant que la fin du fichier n'a pas été atteinte
		if(carac == cle[0] && num_puz == puzzle) { // Si on trouve le bon niveau de puzzle
			if(solveur == true) {
				for(i = 1; i <= 2; i++) { // Lecture successive des clés
					rangee = 0;
					curseur = 0;
					
					while(carac != cle[i]) fscanf(fic_gen,"%c",&carac); // Tant que l'on n'a pas trouvé la clé de départ (ici, "C")

					while(carac != cle[i+1]) { // Tant que l'on n'a pas trouvé la clé de fin
						if(carac == ' ' || carac == '\n') {
							fscanf(fic_gen,"%i",&nb_case);
							if(cle[i] == 'C') colonnes[taille*rangee+curseur] = nb_case;
							else if(cle[i] == 'L') lignes[taille*curseur+rangee] = nb_case;
							rangee++;
							if(rangee > largeur_max) largeur_max = rangee;
						}
						else if(carac == '+') {
							curseur++;
							rangee = 0;
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
						colonnes[taille*curseur+rangee] = nb_case;
						rangee++;
						if(rangee > largeur_max) largeur_max = rangee;
					}
					else if(carac == '+') {
						curseur++;
						rangee = 0;
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

/**
* \fn gen_peripheriques(int *soluce, int *colonnes, int *lignes, int taille)
* \brief Lit la matrice solution et génère les nombres correspondant aux groupes de cases pleines de chaque rangée dans les bonnes matrices périphériques.
* \param soluce La matrice solution de type enum
* \param colonnes La matrice périphérique des colonnes
* \param lignes La matrice périphérique des lignes
* \param taille La taille maximum de la largeur des matrices périphériques ; elle permet de limiter les traitements sur la matrice solution de taille N*N
* \return Ne retourne aucune valeur
*/
void gen_peripheriques(t_couleurs *soluce, int *colonnes, int *lignes, int taille) {
	int i, j, nb_groupes_colonne, nb_groupes_ligne, taille_groupe_colonne, taille_groupe_ligne;
	
	
	for(i = 0; i < taille; i++) {
		nb_groupes_colonne = 0;
		nb_groupes_ligne = 0;
		taille_groupe_colonne = 0;
		taille_groupe_ligne = 0;
		
		for(j = 0; j < taille; j++) {
			// Remplissage de la matrice périphérique des colonnes
			if(soluce[taille*j+i]%2 == 1) {
				taille_groupe_colonne++;
				
				if(j == taille-1) colonnes[taille*nb_groupes_colonne+i] = taille_groupe_colonne;
			}
			else if(soluce[taille*j+i]%2 == 0 && soluce[taille*(j-1)+i]%2 == 1) {
				colonnes[taille*nb_groupes_colonne+i] = taille_groupe_colonne;
				taille_groupe_colonne = 0;
				nb_groupes_colonne++;
			}
			// Remplissage de la matrice périphérique des lignes
			if(soluce[taille*i+j]%2 == 1) {
				taille_groupe_ligne++;
				
				if(j == taille-1) lignes[taille*i+nb_groupes_ligne] = taille_groupe_ligne;
			}
			else if(soluce[taille*i+j]%2 == 0 && soluce[taille*i+j-1]%2 == 1) {
				lignes[taille*i+nb_groupes_ligne] = taille_groupe_ligne;
				taille_groupe_ligne = 0;
				nb_groupes_ligne++;
			}
		}
	}
}

/**
* \fn init_compteur_groupes(int *soluce, int nombres[N], int rangee, char type_rangee)
* \brief Initialise une liste d'entiers avec, pour chaque entier, le nombre de cases pleines d'un groupe analysé verticalement ou horizontalement.
* \param soluce La matrice solution de type enum qui contient les données nécessaires à l'anaylse
* \param taille_mat La taille de la matrice solution 
* \param rangee L'indice numérique de la rangée analysée
* \param type_rangee La nature de la rangée (ligne ou colonne)
* \return La taille finale de la liste d'entiers.
*/
int* init_compteur_groupes(t_couleurs *soluce, int taille_mat, int rangee, char type_rangee) {
	int i, j, groupe = 0, *nombres = malloc(taille_mat * sizeof(int));
	
	// Avant toute opération, on initialise la liste de vérification des nombres
	for(i = 0; i < taille_mat; i++) nombres[taille_mat*i] = 0;
	
	if(type_rangee == 'C') { // Rangée de type colonne
		i = 0;
		j = rangee;
	}
	else if(type_rangee == 'L') { // Rangée de type ligne
		i = rangee;
		j = 0;
	}
	
	while(i < taille_mat && j < taille_mat) {
		if(soluce[taille_mat*i+j]%2 == 1) nombres[taille_mat*groupe] = nombres[taille_mat*groupe] + 1;	// Si on rentre dans un groupe de cases pleines
	
		if(type_rangee == 'C') {
			if(i != 0 && soluce[taille*(i-1)+j]%2 == 1 && soluce[taille*i+j]%2 == 0) groupe++; // Si on sort du groupe vertical vérfié
			i++;
		}
		else {
			if(j != 0 && soluce[taille_mat*i+j-1]%2 == 1 && soluce[taille_mat*i+j]%2 == 0) groupe++; // Si on sort du groupe horizontal vérfié
			j++;
		}
	}
	return nombres;
}

/**
* \fn verif_adequation_globale(t_couleurs *soluce, int *colonnes, int *lignes, int *respect_colonnes, int *respect_lignes, int taille)
* \brief Lorsqu'une itération de la boucle principale de la fonction "gen_solution" a été effectuée, cette fonction a pour rôle de vérifier l'état de toutes les rangées. Elle remplie les tableaux "respect_" avec un indicateur numérique : 0 pour une rangée qui ne respecte pas ses règles, 1 pour un résultat positif. 
* \param soluce La matrice solution de type enum
* \param colonnes La matrice périphérique des colonnes
* \param lignes La matrice périphérique des lignes
* \param respect_colonnes Le tableau qui va contenir les résultats du test pour les colonnes des matrices soluce et colonnes
* \param respect_lignes Le tableau qui va contenir les résultats du test pour les lignes des matrices soluce et lignes
* \param taille La taille des matrices renseignées
* \return Ne retourne aucune variable
*/
void verif_adequation_globale(t_couleurs *soluce, int *colonnes, int *lignes, int *respect_C, int *respect_L, int taille) {
	int i, j;
	
	// On commence par vérifier l'état des lignes
	for(i = 0; i < taille; i++) {
		for(j = 0; j < taille; j++) {
			
		}
	}
	// Puis on vérifie l'état des colonnes
	for(i = 0; i < taille; i++) {
		for(j = 0; j < taille; j++) {
		
		}
	}
}

/**
* \fn adequation_rangee_et_nombres(t_couleurs *soluce, int *periph, int taille, int nb_groupes_defaut, int rangee, char type_rangee)
* \brief Vérifie dans la matrice solution, pour une matrice périphérique, un compteur d'indice et une rangée précise donnés, si le remplissage d'une rangée de type "ligne" correspond aux nombres de la rangée de type "colonne" (et inversement).
* \param soluce La matrice solution de type enum dans laquelle on vérifie l'adéquation d'une rangée par rapport à une autre
* \param periph La matrice périphérique qui contient les nombres nécessaires à la vérification
* \param taille La taille des matrices renseignées
* \param nb_groupes_defaut La taille normale du groupe de nombres de la rangée
* \param rangee La rangée de la matrice solution qui va être vérifiée
* \param type_rangee La nature de la rangée (ligne ou colonne)
* \return Cinq valeurs possibles : 2 si un groupe possède plus de cases que prévu, 1 si des groupes supplémentaires sont détectés, 0 si les données correspondent, -1 s'il reste des groupes à créer, -2 s'il reste des cases à compléter
*/
int adequation_rangee_et_nombres(t_couleurs *soluce, int *periph, int taille, int nb_groupes_defaut, int rangee, char type_rangee) {
	int i, j, k, taille_groupe[nb_groupes_defaut], *nb_groupes = NULL;
	
	nb_groupes = init_compteur_groupes(soluce,taille_groupe,rangee,type_rangee);
	
	/*printf("\nNombre de groupes par défaut : %i, rangée %c vérifiée : %i",nb_groupes_defaut,type_rangee,rangee);
	printf("\nNombre de groupes identifiés dans la rangée : %i",nb_groupes);
	for(k = 0; k < nb_groupes; k++) printf("\nNombre de cases pour le groupe n°%i : %i",k+1,taille_groupe[k]); //*/
	k = 0;
	
	while(k < nb_groupes_defaut) {
		if(nb_groupes < nb_groupes_defaut) return -1;		// Moins de groupes que prévu
		else if(nb_groupes > nb_groupes_defaut) return 1;	// Plus de groupes que prévu (cas improbable, néanmoins)
		else {
			if(type_rangee == 'C') {
				if(taille_groupe[taille*k] < periph[taille*k+j]) return -2;		// Un groupe possède moins de cases que prévu
				else if(taille_groupe[taille*k] > periph[taille*k+j]) return 2;	// Un groupe possède plus de cases que prévu
			}
			else if(type_rangee == 'L') {
				if(taille_groupe[taille*k] < periph[taille*i+k]) return -2;
				else if(taille_groupe[taille*k] > periph[taille*i+k]) return 2;
			}
		}
		k++;
	}
	return 0; // La rangée analysée correspond aux attentes de la rangée de la matrice périphérique
}

/**
* \fn init_compteurs_periph(int *periph, int *cpt, int taille)
* \brief Initialise les compteurs des matrices périphériques. Leur rôle est d'indiquer combien de nombres sont contenus dans chaque rangée (ligne/colonne) de chaque matrice périphérique. Ces compteurs sont utilisés dans la fonction "gen_solution".
* \param periph Une matrice périphérique renseignée
* \param cpt Tableau d'indices de la matrice périphérique associée
* \param taille La taille de la matrice périphérique renseignée
* \return Retourne une liste d'entiers allouée dynamiquement
*/
int* init_compteurs_periph(int *periph, int taille) {
	int i, j, *liste_cpt = malloc(taille * sizeof(int));
	
	// Initialisation de la liste
	for(i = 0; i < taille; i++) liste_cpt[taille*i] = 0;
	
	// Remplissage des listes avec les données des matrices périphériques
	for(i = 0; i < taille; i++) {
		for(j = 0; j < taille; j++) if(periph[taille*j+i] > 0) liste_cpt[taille*i] = liste_cpt[taille*i] + 1;
	}
	return liste_cpt;
}

/**
* \fn gen_solution(t_couleurs *soluce, int *colonnes, int *lignes, int taille)
* \brief Initialise la matrice solution grâce aux données des matrices périphériques. Pour gérer le remplissage progressif et les cas d'erreur, un système de numérotation des cases a été mis en place : 0 => case vide non-testée, 1 => case cochée, 2 => case vide déjà testée, 3 => case cochée validée.
* \param soluce La matrice solution de type enum qui va contenir le motif du puzzle
* \param colonnes La matrice périphérique des colonnes (situé en haut de la grille du Picross)
* \param lignes La matrice périphérique des lignes (situé à gauche de la grille du Picross)
* \param taille La taille maximum des rangées pour les matrices périphériques
* \return Ne retourne aucun résultat
*/
void gen_solution(t_couleurs *soluce, int *colonnes, int *lignes, int taille) {
	int *nombres_colonnes = NULL, *nombres_lignes = NULL, *completion_colonnes = NULL, *completion_lignes = NULL; // Listes
	int i, j, k, l, decalage, verif, lecture_grille = 0, respect_regles = 0, tour_ligne = 1;
	
	// Dans un premier temps, on dénombre les chiffres présents dans chacune des lignes des matrices périphériques
	nombres_colonnes = init_compteurs_periph(colonnes,taille);
	nombres_lignes = init_compteurs_periph(lignes,taille);
	
	// Initialisation des variables d'incrémentation
	i = 0;
	j = 0;
	
	afficher_matrice(colonnes,3,taille,'C');
	
	// Ensuite, on boucle la matrice jusqu'à ce que la solution soit correctement générée
	while(respect_regles != 1) {
		printf("\nLecture de la grille n°%i",lecture_grille);
		printf("\nTour n°%i",i);
		
		// Lorsque toutes les rangées auront été lues au moins une fois pour la complétion, on effectue une vérification globale pour passer à la troisième étape de la génération
		if(lecture_grille >= 1) verif_adequation_globale(soluce,colonnes,lignes,completion_colonnes,completion_lignes,taille);
		
		if(tour_ligne == 1) { // On commence par remplir les lignes
			// On remplit les cases en fonction du ou des nombres indiqués dans la colonne de la matrice périphérique
			if(nombres_lignes[taille*i] > 0) {
				decalage = j;
			
				for(k = 0; k < nombres_lignes[taille*i]; k++) {
					if(lignes[taille*i+k] > 0 && lignes[taille*i+k] < taille) {
						for(l = 0; l < lignes[taille*i+k]; l++) {
							soluce[taille*i+decalage] = 1;
							decalage++;
						}
						if(lecture_grille == 0) decalage++; // On effectue un décalage d'une unité entre chaque groupe à la première lecture
					}
					else if(lignes[taille*i+k] == taille) for(l = 0; l < taille; l++) soluce[taille*i+l] = 3;
				}
			}
			else for(l = 0; l < taille; l++) soluce[taille*i+l] = 2;
			
			if(lecture_grille == 0) {
				if(lignes[taille*i+i] > 0 && lignes[taille*i+i] < taille) {
					verif = adequation_rangee_et_nombres(soluce,colonnes,nombres_colonnes[taille*i],j,'C');
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
			
			if(i >= taille) {
				lecture_grille++;
				tour_ligne = 0;
				i = 0;
				j = 0;
			}
			afficher_matrice(soluce,3,taille,'S');
			printf("\n\n");
		}
		else { // Puis on passe au remplissage des colonnes
			verif_adequation_globale(soluce,colonnes,lignes,completion_colonnes,completion_lignes);
			
			// On remplit les cases en fonction du ou des nombres indiqués dans la colonne de la matrice périphérique
			if(nombres_colonnes[taille*j] > 0) {
				decalage = i;
			
				for(k = 0; k < nombres_colonnes[taille*j]; k++) {
					if(colonnes[taille*k+j] > 0 && colonnes[taille*k+j] < taille) {
						for(l = 0; l < C[taille*k+j]; l++) {
							soluce[taille*decalage+j] = 1;
							decalage++;
						}
						decalage++; // On effectue un décalage d'une unité entre chaque groupe à la première lecture
					}
					else if(colonnes[taille*i+k] == taille) for(l = 0; l < taille; l++) S[taille*i+l] = 3;
				}
			}
			else for(l = 0; l < taille; l++) S[taille*i+l] = 2;
			
			if(lignes[taille*j+j] > 0 && lignes[taille*j+j] < N) {
				verif = adequation_rangee_et_nombres(soluce,lignes,nombres_lignes[taille*j],i,'L');
				printf("\nVérification : %i ",verif);
			
				if(verif == 0) { // Si la complétion correspond aux rangées lues
					i++;
					j++;
				}
				else if(verif == -1) j++;
				else if(verif == -2) i++;
			}
			else j++;
			
			if(j >= taille) {
				lecture_grille++;
				tour_ligne = 0;
				i = 0;
				j = 0;
			}
			afficher_matrice(soluce,3,taille,'S');
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
*/
int main() {
	char *saisie = "nombres_puzzle.txt";
	int *matColonnes, *matLignes;
	t_couleurs *soluce;
	t_difficulte niveau = facile;
	
	printf("Niveau : %i\n",niveau);
	
	//init_case(soluce);
	//matColonnes = init_matrice(niveau);
	
	//taille = lecture_fic(saisie,4,matC,matL,1);
	
	//afficher_matrice(matC,1,taille,'C');
	//afficher_matrice(matL,1,taille,'L');
	
	//gen_solution(soluce,matC,matL,taille);
	//afficher_matrice_claire(soluce);
	printf("\n");
} //*/
