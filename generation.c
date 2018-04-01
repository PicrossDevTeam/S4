/**
* \file generatin.c
* \author KAJAK Rémi
* \version 1.0
* \date 19/03/2018
* \brief Fichier ayant servi à l'élaboration de la fonction de lecture du fichier texte qui contient les nombres générateurs de la matrice principale et la fonction de génération de la matrice solution.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* \def N
* \brief Nombre de lignes de la matrice test
*/
#define N 5

/**
* \fn afficher_matrice(int mat[N][N], char cle)
* \brief Affiche une matrice reçue en paramètre selon un modèle prédéfini.
* \param mat Une matrice de taille fixe
* \param cle Un caractère qui définit le mode d'affichage : "C" pour afficher horizontalement les nombres de la matrice périphérique des colonnes, "L" pour afficher verticalement les nombres de la matrice périphérique des lignes et "S" pour afficher une grille complète
* \return Ne retourne aucun résultat
*/
void afficher_matrice(int mat[N][N], char cle) {
	int i, j;
	
	printf("\n");
	if(cle == 'C') {
		printf("Matrice périphérique des colonnes :\n\n");
		for(i = N-1; i >= 0; i--) {
			for(j = N-1; j >= 0; j--) {
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
		printf("Matrice périphérique des lignes :\n\n");
		for(i = N-1; i >= 0; i--) {
			for(j = N-1; j >= 0; j--) {
				if(j == 0) printf("%i ",mat[i][j]);
				else {
					if(mat[i][j] > 0) printf("%i ",mat[i][j]);
					else printf("  ");
				}
			}
			printf("\n");
		}
	}
	else {
		printf("Matrice solution :\n\n");
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) printf("%i ",mat[i][j]);
			printf("\n");
		}
	}
}

void afficher_matrice_claire(int mat[N][N]) {
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
* \fn lecture_fic(char *nom, int niveau)
* \brief Lit un fichier avec un format spécifique et renseigne les nombres contenus dans les matrices périphériques.
* \param nom Nom du fichier texte à analyser
* \param niveau Nombre du puzzle à trouver dans le fichier
* \return Ne retourne aucun résultat
*/
void lecture_fic(char *nom_fic, int niveau, int C[N][N], int L[N][N]) { /* Lecture du fichier contenant les puzzles prédéfinis */
	FILE * fic_gen;
	char cle[4] = "PCLF", carac;
	int ligne, colonne, num_puz, nb_case, i;

	fic_gen = fopen(nom_fic,"r");
	fscanf(fic_gen,"%c %i",&carac,&num_puz);

	while(!feof(fic_gen)) { // Tant que la fin du fichier n'a pas été atteinte
		if(carac == cle[0] && num_puz == niveau) { // Si on trouve le bon niveau de puzzle
			for(i = 1; i <= 2; i++) { // Lecture successive des clés
				ligne = 0;
				colonne = 0;

				while(carac != cle[i]) { // Tant que l'on n'a pas trouvé la clé de départ
					fscanf(fic_gen,"%c",&carac);
				}
				fscanf(fic_gen,"%c",&carac);

				while(carac != cle[i+1]) { // Tant que l'on n'a pas trouvé la clé de fin
					if(carac == ' ' || carac == '\n') {
						fscanf(fic_gen,"%i",&nb_case);
						if(cle[i] == 'C') C[colonne][ligne] = nb_case;
						else if(cle[i] == 'L') L[ligne][colonne] = nb_case;
						colonne++;
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
}

/**
* \fn verif_adequation_globale(int soluce[N][N], int C[N][N], int L[N][N], int reglesC[N], int reglesL[N])
* \brief Lorsque deux itérations de la boucle principale de la fonction "gen_solution" ont été effectuées, cette fonction a pour rôle de vérifier toutes les rangées en utilisant la fonction "adequation_rangee_et_nombres". Elle remplie les tableaux "regles_" avec un indicateur numérique : 0 pour une rangée qui ne respecte pas les règles, 1 pour un résultat positif. 
* \param solune La matrice solution
* \param C La matrice périphérique des colonnes
* \param L La matrice périphérique des lignes
* \param reglesC Le tableau qui va contenir les résultats du test pour les colonnes des matrices soluce et C
* \param reglesL Le tableau qui va contenir les résultats du test pour les lignes des matrices soluce et L
* \return Ne retourne aucune variable
*/
void verif_adequation_globale(int soluce[N][N], int C[N][N], int L[N][N], int reglesC[N], int reglesL[N]) {
	
}

/**
* \fn adequation_rangee_et_nombres(int S[N][N], int periph[N][N], int cpt[N], int rangee, char type_rangee)
* \brief Vérifie dans la matrice solution, pour une matrice périphérique, un compteur d'indice et une rangée précise donnés, si le remplissage d'une rangée de type "ligne" correspond aux nombres de la rangée de type "colonne" (et inversement).
* \param S La matrice solution dans laquelle on vérifie l'adéquation d'une rangée par rapport à une autre
* \param periph La matrice périphérique qui contient les nombres nécessaires à la vérification
* \param groupes_defaut La taille normale du groupe de nombres de la rangée
* \param rangee La rangée de la matrice solution qui va être vérifiée
* \param type_rangee La nature de la rangée (ligne ou colonne)
* \return Cinq valeurs possibles : 2 si un groupe possède plus de cases que prévu, 1 si des groupes supplémentaires sont détectés, 0 si les données correspondent, -1 s'il reste des groupes à créer, -2 s'il reste des cases à compléter
*/
int adequation_rangee_et_nombres(int S[N][N], int periph[N][N], int groupes_defaut, int rangee, char type_rangee) {
	int i, j, k, taille_groupe[groupes_defaut], nb_groupe = 0;
	
	// Avant toute opération, on initialise la liste de vérification des nombres
	for(i = 0; i < groupes_defaut; i++) taille_groupe[i] = 0;
	
	if(type_rangee == 'C') { // Rangée de type colonne
		i = 0;
		j = rangee;
	}
	else if(type_rangee == 'L') { // Rangée de type ligne
		i = rangee;
		j = 0;
	}
	
	for(i = 0; i < N; i++) {
		if(S[i][j]%2 == 1) taille_groupe[nb_groupe] = taille_groupe[nb_groupe] + 1; // Si on rentre dans un groupe de cases pleines
		else if(i != 0 && S[i-1][j]%2 == 1 && S[i][j]%2 == 0)  nb_groupe++; // Si on sort du groupe vérfié
	}
	printf("\nNombre de groupes par défaut : %i, rangée %c vérifiée : %i",groupes_defaut,type_rangee,rangee);
	printf("\nNombre de groupes identifiés dans la rangée : %i",nb_groupe);
	for(k = 0; k < nb_groupe; k++) printf("\nNombre de cases pour le groupe n°%i : %i",k+1,taille_groupe[k]);
	k = 0;
	
	while(k < groupes_defaut) {
		if(nb_groupe < groupes_defaut) return -1;		// Moins de groupes que prévu
		else if(nb_groupe > groupes_defaut) return 1;	// Plus de groupes que prévu (cas improbable, néanmoins)
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
* \fn init_compteurs_periph(int cptC[N], int cptL[N])
* \brief Initialise les compteurs des matrices périphériques. Leur rôle est d'indiquer combien de nombres sont contenus dans chaque rangée (ligne/colonne) de chaque matrice périphérique. Ces compteurs sont utilisés dans la fonction "gen_solution".
* \param cptC Tableau d'indices de la matrice périphérique des colonnes
* \param cptL Tableau d'indices de la matrice périphérique des lignes
* \return Ne retourne aucun résultat
*/
void init_compteurs_periph(int cptC[N], int cptL[N]) {
	int i;
	
	for(i = 0; i < N; i++) {
		cptC[i] = 0;
		cptL[i] = 0;
	}
}

/**
* \fn gen_solution(int S[N][N], int C[N][N], int L[N][N])
* \brief Initialise la matrice solution grâce aux données des matrices périphériques. Pour gérer le remplissage progressif et les cas d'erreur, un système de numérotation des cases a été mis en place : 0 => case vide non-testée, 1 => case cochée, 2 => case vide déjà testée, 3 => case cochée validée.
* \param S La matrice solution qui va contenir le motif du puzzle
* \param C La matrice périphérique des colonnes (situé en haut de la grille du Picross)
* \param L La matrice périphérique des lignes (situé à gauche de la grille du Picross)
* \return Ne retourne aucun résultat
*/
void gen_solution(int S[N][N], int C[N][N], int L[N][N]) {
	int nombres_C[N], nombres_L[N], completionC[N], completionL[N]; // Tableaux
	int i, j, k, l, decalage, verif, lecture_grille = 0, respect_regles = 0, tour_ligne = 1;
	
	// Dans un premier temps, on dénombre les chiffres présents dans chacune des lignes des matrices périphériques
	init_compteurs_periph(nombres_C,nombres_L);
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			if(C[j][i] > 0) nombres_C[i] = nombres_C[i] + 1;
			if(L[i][j] > 0) nombres_L[i] = nombres_L[i] + 1;
		}
	}
	
	// Initialisation des variables d'incrémentation
	i = 0;
	j = 0;
	
	afficher_matrice(C,'C');
	
	// Ensuite, on boucle la matrice jusqu'à ce que la solution soit correctement générée
	while(respect_regles != 1) {
		printf("\nLecture de la grille n°%i",lecture_grille);
		printf("\nTour n°%i",i);
		
		// Lorsque toutes les rangées auront été lues au moins une fois pour la complétion, on effectue une vérification globale pour passer à la troisième étape de la génération
		//if(lecture_grille >= 1) verif_adequation_globale(S,C,L,completionC,completionL);
		
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
			
			if(i >= N) {
				lecture_grille++;
				tour_ligne = 0;
				i = 0;
				j = 0;
			}
			afficher_matrice(S,'S');
			printf("\n\n");
		}
		else { // Puis on passe au remplissage des colonnes
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
			afficher_matrice(S,'S');
			printf("\n\n");
		}
		if(lecture_grille == 2) respect_regles = 1;
	}
}

void init_matrices(int S[N][N], int C[N][N], int L[N][N]) {
	int i, j;
	
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			S[i][j] = 0;
			C[i][j] = 0;
			L[i][j] = 0;
		}
	}
}

int main() {
	char *saisie = "nombres_puzzle.txt";
	int matC[N][N], matL[N][N], soluce[N][N];
	
	init_matrices(soluce,matC,matL);
	lecture_fic(saisie,2,matC,matL);
	
	//afficher_matrice(matC,'C');
	//afficher_matrice(matL,'L');
	
	gen_solution(soluce,matC,matL);
	afficher_matrice_claire(soluce);
	printf("\n");
}
