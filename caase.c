#include<stdio.h>
#include<stdlib.h>
#include"case.h"
#define N 5



t_Case  init_case(t_couleurs etat ){/*initialiser toutes les cases à 0 */
t_Case matr[N][N];
int i,j;

	for(i=0 ; i<= N ; i++)
	
		for(j=0 ; j<= N ; j++){
		
			matr[i][j].etat= 0;
						
		}
	return matr[i][j] ;
}
	


/******************************************************************************************************/
void changerEtat(t_Case c){/*changer l'etat de la case  de blanche à noire et de noire à blanche ou croix */

	if(c.etat == 0)
		c.etat = 1;
	if(c.etat == 1)
		c.etat = 2;
		else
		c.etat = 0;
	
	
		
}

/******************************************************************************************************************/
int max_h_Case(int a){/*limite cases horizontales*/

int m = a -1 ;

  if(a%2==1)

    m++;

return m;

 }

int max_v_Case(int b){/*limite cases verticales*/

int m = b -1;

  if(b%2==1)
    m++;

return m;


 }

/****************************************************************************************************************/
double verifierCaseNoire( int matd[N][N] , int matf[N][N]){/*verifier si le groube de cases noire correspond au nombres horizontals et verticals*/
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


int main()

{



 /* Déclarations */
 int U[50][50]; /* matrice */
 int M[50][50];
 int v = 5;         /* dimension de la matrice  */
 int I, J;      /* indices courants */


 

 

 /* Construction de la matrice  */
 for (I=0; I<v; I++)
     for (J=0; J<v; J++)

             U[I][J]=0;
		
 
  /* Edition du résultat */
 printf("MATRICE1 :\n" );
 for (I=0; I<v; I++)
    {
     for (J=0; J<v; J++)
          printf("%4d", U[I][J]);
        
     printf("\n");
    }
 
 /* Construction de la matrice 2 */
 for (I=0; I<v; I++)
     for (J=0; J<v; J++)

             M[I][J]=1;
		
 
  /* Edition du résultat 2*/
 printf("MATRICE2 :\n" );
 for (I=0; I<v; I++)
    {
     for (J=0; J<v; J++)
          printf("%4d", M[I][J]);
        
     printf("\n");
    }
 

/*
     
      t_Case s = init_case(0);
    
      changerEtat(s);
      

    double L= verifierCaseNoire(U,M);
	  printf("%d\n",L);

    int k= max_h_Case(5);
    	printf("%d\n",k);
    int z= max_v_Case(5);
   	 printf("%d\n",z);
   */


    return 0;
}
