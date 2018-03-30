#include <stdio.h>
#include <stdlib.h>

typedef struct cocher
{
	int croix;
	struct cocher *noire, *blanche;
}t_cocher;

typedef struct cocher* t_caz;

/*ici la case vaut caz, les croix vaut croix, les cases cocher vaut noire, les case vide vaut blanche*/
t_caz creer_caz(int croix, t_caz noire, t_caz blanche)
{
	t_caz caz = malloc(sizeof(t_cocher));
	caz->croix = croix;
	caz->noire = noire;
	caz->blanche = blanche;
	return caz;
}

/*vrai si la case est vide*/
int caz_blanche(t_caz caz)
{
	return caz == 0;
}

/*vrai si la case est cocher*/
t_caz caz_noire(t_caz caz)
{
	if(caz_blanche(caz))
		return 0;
	else
		return caz->noire;
}

/*met la case en X si l'utilisateur decoche la case cocher*/
int modif_caz(t_caz caz, int croix)
{
	if(caz == 0)
		return 0;
	caz->croix = croix;
	return 1;
}
