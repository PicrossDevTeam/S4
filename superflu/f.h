/* Variable globale */

/* Taille après le choix de la difficulté */
int T;

/* Taille des matrices périphérique pour éviter un parcours trop long */
int P;

/* Création de matrice (Kinzi Erick) */

void creer_mat_ori(int mat_ori[T][T]);
void creer_peri_haut(int mat_ori[T][T]);
void creer_peri_gauche(int mat_ori[T][T]);

/* Affichage de matrice (Kinzi Erick) */

void aff_mat_ori(int mat_ori[T][T]);
void aff_peri_haut(int mat_ori[T][T]);
void aff_peri_gauche(int mat_ori[T][T]);

/* Lecture fichier et remplissage de la matrice de solution avec le fichier (Kajak Rémi) */

void lecture_fic(char *nom_fic, int niveau);

/* Validation solution (Nouvelière Benjamin) */

int verif_peri_h(int matrice_globale[T][T]);
int verif_peri_g(int matrice_globale[T][T]);
int validation(int matrice_globale[T][T]);