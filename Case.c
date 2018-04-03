#include<stdio.h>
#include<stdlib.h>
#include"case.h"
#include<stdbool.h>
#define N 5




void  init_case(int matr[N][N]){/*initialiser toutes les cases à 0 */

int i,j;

	for(i=1 ; i<= N ; i++)
	
		for(j=1 ; j<= N ; j++){
		
			matr[i][j] = 0;
		printf("\n");		
				}
	
}

/*********************************************************************************************/

void  verif_matrice(int matr[N][N] ){/*verification du contenu de la matrice */

int i,j;

	for(i=1 ; i<= N ; i++){
	
		for(j=1 ; j<= N ; j++){
		
			printf("|%i|", matr[i][j]);
						
				}
		printf("\n");
	}
}


int changerEtat(int c){/*changer l'etat de la case  de blanche representé par un '0' à noire representé par un '1' et de noire à blanche ou croix représenté par un '2' */


	if(c==0)
		return 1;
	else if(c==1)
		return 2;
	else
		return 0;
	
	
		
}

/*********************************************************************************************/

int max_h_Case(int a){/*limite cases horizontales*/

  if(a%2==1){
    a=a-1;
    a++;}

return a;

 }
int max_v_Case(int b){/*limite cases verticales*/

  if(b%2==1){
     b=b-1;
     b++;}

return b;


 }

/*********************************************************************************************/


_Bool verifier_Case_Noire_Ligne( int matr[N][N], int ligne, int valeur){/*verifier si les cases noire correspondent au nombres horizontals*/

int i,j=0;
_Bool comp=false,find=false;
int c=0;

	while(j<N-1 && comp==false)
	{
		if(matr[ligne][j]==1)
		{
			i=j+1;
			find=true;
			c=valeur-1;
			if(c==0){
				comp=true;
				}
			else
			{
				while(i<i+c && i<=N-1 && find==true)
				{
					if(matr[ligne][i]==1){
						i++;}
					else{
						find=false;}
				}
					if(find==true){
						comp=true;}
					else{
						c=0;}
			 }
		}
		else
		{
			c=0;}
	j++;
	}
return comp;
}

/*********************************************************************************************/

_Bool verifier_Case_Noire_Col( int matr[N][N], int col, int valeur){/*verifier si les cases noire correspondent au nombres verticals*/

int i,j=0,c=0;
_Bool comp=false,find= false;


	while(j<N-1 && comp==false)
	{
		if(matr[j][col]==1)
		{
			i=j+1;
			find=true;
			c=valeur-1;
			if(c==0){
				comp=true;
				}
			else
			{
				while(i<i+c && i<=N-1 && find==true)
				{
					if(matr[i][col]==1){
						i++;}
					else{
						find=false;}
				}
					if(find==true){
						comp=true;}
					else{
						c=0;}
			 }
		}
		else
		{
			c=0;}
	j++;
	}
return comp;
}


/*********************************************************************************************/



int verifierGrille(int matd[N][N] , int matf[N][N]){/*verifier si la grille du joueur est correcte*/
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
/*********************************************************************************************/
int main()

{

int U[5][5];
_Bool b=false;
int i,j;

int coup = 0;

     
init_case(U);
verif_matrice(U);
printf("---------------\n");
for(i=1 ; i<=5 ; i++){
	for(j=1 ; j<=5 ; j++){
		printf("i=");
		scanf("%i", &i);
		printf("j=");
		scanf("%i", &j);
		printf("---------------\n");
		U[i][j]=changerEtat(U[i][j]);
		verif_matrice(U);
		coup++;
		printf("\nnombre des coups %d\n",coup);
		printf("-------------\n");
/*
U[i][j]=changerEtat(U[i][j]);
verif_matrice(U);
printf("----------------\n");
U[i][j]=changerEtat(U[i][j]);
verif_matrice(U);*/
	}
}

 int k= max_h_Case(5);
    	printf("%d\n",k);
    int V= max_v_Case(5);
   	 printf("%d\n",V);

/*verification d'une ligne*/

b=verifier_Case_Noire_Ligne(U,2,1);
	if(b==true){
		printf("Bravooo");}
	else{
		printf("Reessayer");}

 return 0;
}
