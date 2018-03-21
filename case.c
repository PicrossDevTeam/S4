#include<stdio.h>
#include<stdlib.h>
#include"case.h"
#define N 5
  



t_Case  init_case(int mat[N][N]){
t_couleurs etat;
int i,j;

	for(i=0 ; i<= N ; i++){
	
		for(j=0 ; j<= N ; j++){
		
			etat.mat[i][j] = 0;
						
		}

	}
}
void changerEtat(t_Case c){/*changer l'etat de la case de noire à blanche et de blanche à noire*/

	if(c.etat == 0)
		c.etat = 1;
	if(c.etat == 1)
		c.etat = 2;
		else
		c.etat = 0;
		
}
	                    
int max_h_Case(int a){/*limite cases horizontales*/

int m = a / 2;

  if(a%2==1)
    m++;

return m;

 }
                    
int max_v_Case(int b){/*limite cases verticales*/

int m = b/ 2;

  if(b%2==1)
    m++;

return m;


 }


int verifierCaseNoire(t_Case c , int matd[N][N] , int matf[N][N]){/*verifier si le groube de cases noire correspond au nombres horizontals et verticals*/
int i,j;
int comp = 0;

	for(i=0; i<=N; i++ )
	{
		for(j=0; j<=N; j++)
		{
			if(matd[i][j] != matf[i][j])
				comp++;

		}
}
 			return comp;


}

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
    
     B = creerMatrice(3);

    *(B+0) = -1; *(B+1) = -2; *(B+2) = 0;
    *(B+3) = 4; *(B+4) = 5; *(B+5) = 6;
    *(B+6) = 3; *(B+7) = 2; *(B+8) = 1;

    resultat = creerMatrice(3);
    
    printf("Matrice A: \r\n");
    afficherMatrice(3, A);
    printf("Matrice B: \r\n");
    afficherMatrice(3, B);
    t_Case S= init_case(A);
    t_Case Z= changerEtat(A);
    int k= max_h_Case(5);
    int v= max_v_Case(5);
    int l= verifierCaseNoire(3,A,B);

    
    return 0;
}