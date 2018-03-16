#include <stdio.h>
#include <stdlib.h>
#include "case.h"



double * creerMatrice(int n)
{
    double * A = malloc (n * n * sizeof(*A));

    if (A == NULL)
    {
        printf("Erreur d'allocation");
        exit(EXIT_FAILURE);
    }

    return A;
}
void afficherMatrice(int n, double * A){
int i,j, p=0;


	printf("\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%f\t",*(A+p));
			p++;
                }
		printf("\n");
        }
	printf("\n");

}
int main()
{
    double * A;
    double * B;
    double * resultat;



    A = creerMatrice(3);

    *(A+0) = 1; *(A+1) = 2; *(A+2) = 3;
    *(A+3) = 4; *(A+4) = 5; *(A+5) = 6;
    *(A+6) = 7; *(A+7) = 8; *(A+8) = 9;

    resultat = creerMatrice(3);
    
    printf("Matrice A: \r\n");
    afficherMatrice(3, A);
    int k= max_h_Case(5);
    int v= max_v_Case(5);
    int l=verifierCaseNoire(3,A);
    return 0;
}