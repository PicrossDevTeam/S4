/**
* \file terminal.c
* \author KAJAK Rémi
* \version 1.0
* \date 03/04/2018
* \brief Fichier permettant de jouer une partie de Picross à partir d'un terminal de commande.
*/
#include <stdio.h>
#include <stdlib.h>

typedef enum couleurs {Blanche, Noire, Croix} t_couleurs;
typedef enum difficulte {facile=3, normal=5, difficile=7, expert=10} t_difficulte;

t_couleurs * init_matrice_prin(t_difficulte dim_mat){
	t_couleurs * mat = malloc(dim_mat*dim_mat*sizeof(t_couleurs));
	int i,j;

	for(i=0 ; i < dim_mat ; i++) {
		for(j=0 ; j < dim_mat ; j++) {
			mat[dim_mat*i+j] = Blanche;
		}
	}
	return mat;
}

int * init_matrice_peri(t_difficulte dim_mat){
	int * mat = malloc(dim_mat*dim_mat*sizeof(int));
	int i,j;

	for(i=0 ; i < dim_mat ; i++) {
		for(j=0 ; j < dim_mat ; j++) {
			mat[dim_mat*i+j] = 0;
		}
	}
	return mat;
}

void detruire_matrice_peri(int * mat) {
	free(mat);
}

void detruire_matrice_prin(t_couleurs * mat){
	free(mat);
}

void afficher_haut(int *mat_hori, t_difficulte dim_mat){
	int i,j;

	for(i = 0; i < dim_mat; i++) {
		for(j = 0; j < dim_mat; j++) {
			printf("  ");
		}
		printf(" ");
		for(j = 0; j < dim_mat; j++){
			if(mat_hori[dim_mat*i+j]!=0)
				printf("%i ",mat_hori[dim_mat*i+j]);
		}
		printf("\n");
	}
	printf("\n");
}

void afficher_bas(int *mat_verti, t_couleurs *mat_prin, t_difficulte dim_mat){
	int i,j,k;
	int espace=dim_mat;

	for(i = 0; i < dim_mat; i++) {
		for(j = 0; j < dim_mat; j++) {
			if(mat_verti[dim_mat*i+j]!=0){
				printf("%i ", mat_verti[dim_mat*i+j]);
				espace--;
			}
			else
				espace++;
		}

		for(k=0; k<espace; k++)
			printf(" ");
		espace=dim_mat;

		printf(" ");
		for(j = 0; j < dim_mat; j++){
			printf("%i ", mat_prin[dim_mat*i+j]);
		}
		printf("\n");
	}
}

void affichage_jeu(int *mat_hori, int *mat_verti, t_couleurs *mat_prin, t_difficulte dim_mat){
	afficher_haut(mat_hori, dim_mat);
	afficher_bas(mat_verti, mat_prin, dim_mat);
}

/* -------------------------------------- */

void changerEtat(t_couleurs *mat_prin, t_difficulte dim_mat, int x, int y) {
	if(mat_prin[dim_mat*x+y] == Blanche)
		mat_prin[dim_mat*x+y] = Noire;
	else if(mat_prin[dim_mat*x+y] == Noire)
		mat_prin[dim_mat*x+y] = Croix;
	else
		mat_prin[dim_mat*x+y] = Blanche;
}

int saisir_coord(t_couleurs *mat_prin, t_difficulte dim_mat) {
	int x = 0, y = 0;

	while((x < 1 || x > dim_mat) || (y < 1 || y > dim_mat)) {
		printf("\nEntrez les coordonnées de l'abscisse et de l'ordonnée de la case à cocher (comprises entre 1 et %i). Pour valider votre grille, entrez -1 aux deux coordonnées : ",dim_mat);
		scanf("%i %i",&y,&x);
		
		if(x != -1 || y != -1) {
			if(x < 1 || x > dim_mat)
				printf("\nERREUR : La coordonnée x n'est pas comprise entre les nombres indiqués !");
			if(y < 1 || y > dim_mat)
				printf("\nERREUR : La coordonnée y n'est pas comprise entre les nombres indiqués !\n");
		}
		else
			return 1;
 	}
	changerEtat(mat_prin,dim_mat,x-1,y-1);
	return 0;
}

/* -------------------------------------- */

void lecture_fic_v1(char *nom_fic, int puzzle, t_couleurs *soluce, t_difficulte taille) {
	FILE *fic_gen;
	char *cle = "PDF", carac;
	int rangee = 0, curseur = 0, num_puz, nb_case;
	
	fic_gen = fopen(nom_fic,"r");
	fscanf(fic_gen,"%c %i",&carac,&num_puz);
	
	while(!feof(fic_gen)) { // Tant que la fin du fichier n'a pas été atteinte
		if(carac == cle[0] && num_puz == puzzle) { // Si on trouve le bon niveau de puzzle
			while(carac != cle[1]) fscanf(fic_gen,"%c",&carac); // Tant que l'on n'a pas trouvé la clé de départ (ici, "D")
				
			while(carac != cle[2]) { // Tant que l'on n'a pas trouvé la clé de fin
				if(carac == ' ' || carac == '\n') {
					fscanf(fic_gen,"%i",&nb_case);
					if(nb_case == 1) soluce[taille*curseur+rangee] = Noire;
					rangee++;
				}
				else if(carac == '+') {
					curseur++;
					rangee = 0;
				}
				fscanf(fic_gen,"%c",&carac);
			}
		}
		fscanf(fic_gen,"%c %i",&carac,&num_puz);
	}
	fclose(fic_gen); 
}

void gen_peripheriques(t_couleurs *soluce, int *colonnes, int *lignes, t_difficulte taille) {
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

/* -------------------------------------- */

int verif_soluce(t_couleurs *mat_prin, t_couleurs *mat_soluce, int dim_mat){
	int i,j;

	for(i=0; i<dim_mat; i++){
		for(j=0; j<dim_mat; j++){
			if(mat_soluce[dim_mat*i+j]==1){
				if(mat_prin[dim_mat*i+j]!=1){
					return 1;
				}
			}
		}
	}
	return 0;
}

/* -------------------------------------- */

int main(void){
	t_difficulte dim_mat=facile;
	t_couleurs * mat_prin = init_matrice_prin(dim_mat);
	t_couleurs * mat_soluce = init_matrice_prin(dim_mat);
	int num_puzzle=2;
	int quit;
	int mat_ok=1;
	int choix=0;
	int jeu_gagne=1;

	int * mat_verti = init_matrice_peri(dim_mat);
	int * mat_hori = init_matrice_peri(dim_mat);

	while(num_puzzle<7 && choix==0){
		lecture_fic_v1("puzzles_binaires.txt", num_puzzle, mat_soluce, dim_mat);
		gen_peripheriques(mat_soluce, mat_hori, mat_verti, dim_mat);

		while(mat_ok==1){
			mat_ok=0;
			do{
				affichage_jeu(mat_hori, mat_verti, mat_prin, dim_mat);
				quit=saisir_coord(mat_prin, dim_mat);
			} while(quit!=1);

			do{
				if(verif_soluce(mat_prin, mat_soluce, dim_mat)==1){
					printf("Votre solution est fausse, entrez 0 pour continuer ou 1 pour arrêter : ");
					scanf("%i", &choix);
					if(choix==0)
						mat_ok=1;
				} else {
					printf("Félicitation ! Si vous voulez passer au niveau suivant entrez 0 pour continuer ou 1 pour arrêter : ");
					scanf("%i", &choix);
					if(choix==0){
						num_puzzle++;
						if(num_puzzle==7)
							jeu_gagne==0;
					}
				}
			} while(choix!=0 && choix!=1);
		}

		detruire_matrice_prin(mat_prin);
		detruire_matrice_peri(mat_verti);
		detruire_matrice_peri(mat_hori);
	}
	if(jeu_gagne==0){
		printf("Félicitation, vous avez réussi le jeu du Picross, à une prochaine fois !\n");
	}
	printf("Merci d'avoir joué à notre jeu, à une prochaine fois !\n");
	return 0;
}
