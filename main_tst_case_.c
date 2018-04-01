#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "case.h"

int caz_blanche();
int modif_caz();

int main()
{
	t_caz caz = NULL;
	int vide;
	int comp_coup = 0;
	int puzzle_resolu = 0;
	int croix1 = 1;
	int croix2 = 0;
	int M[20][20];
	const int N = 3; 
	int i, j;

	for (i=0; i<N; i++)
		for (j=0; j<N; j++)
			M[i][j]=0;
	 
	  /* Edition du résultat */
	 printf("\nFacile :\n\n" );
	for (i=0; i<N; i++)
	{
		for (j=0; j<N; j++)
			printf("%2d", M[i][j]);
		printf("\n");
	}

	do{
		vide = caz_blanche(caz);
		printf("\njouer\n");
		scanf("%d",&puzzle_resolu);

		if(vide){
			modif_caz(caz,croix1);
			comp_coup++;
			return M[i][j] = 1;
		}
		else{
			modif_caz(caz,croix2);
			comp_coup++;
			return M[i][j] = 0;
		}
	}
	while(!puzzle_resolu);
	if(caz_noire(caz) == 0)
		printf("Felicitation vous avez resolu le puzzle avec succès!!\nEn %d coup jouer", comp_coup);
		printf("\n");

	return 0;
}
