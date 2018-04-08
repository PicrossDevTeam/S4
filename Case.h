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
typedef enum difficulte {facile = 3, normal, difficile, expert = 10} t_difficulte;

t_couleurs* init_case(t_difficulte taille_max);
void verif_matrice(t_couleurs *mat, t_difficulte taille_max);
void changerEtat(t_couleurs *mat, t_difficulte taille, int x, int y);
int saisir_coord(t_couleurs *mat, t_difficulte taille);
int verifierGrille(t_couleurs *matd, t_couleurs *matf, t_difficulte taille);
int renvoyerTailleMax(t_difficulte niveau);
