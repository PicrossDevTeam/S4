/**
 * \enum t_couleurs
 * \brief la couleur des cases.
 *
 */
typedef enum couleurs {Blanche, Noire, Croix} t_couleurs;

/**
 * \enum t_couleurs
 * \brief la couleur des cases.
 *
 */
typedef enum difficulte {facile, normal, difficile, expert} t_difficulte;

t_couleurs* init_case(int taille_max);
void verif_matrice(t_couleurs *mat, int taille_max);
void changerEtat(t_couleurs *mat, int taille, int x, int y);
int saisir_coord(t_couleurs *mat, int taille);
int verifierGrille(t_couleurs *matd, t_couleurs *matf, int taille);
int renvoyerTailleMax(t_difficulte niveau);
