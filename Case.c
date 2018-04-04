/**
 * \file Case.c
 * \brief ReprÃ©sentation des cases.
 * \author Taous.M
 * \version 0.1
 * \date 3 avril 2018
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/**
* \def N
* \brief la taille de la matrice.
*/
#define N 5

/**
 * \fn void  init_case(int matr[N][N])
 * \brief Fonction d'initialisation des cases.
 *
 * \param la matrice qui reprÃ©sente la grille.
 */


void  init_case(int matr[N][N]){/*initialiser toutes les cases Ã  0 */

int i,j;

	for(i=1 ; i<= N ; i++)
	
		for(j=1 ; j<= N ; j++){
		
			matr[i][j] = 0;
		printf("\n");		
				}
	
}
/*********************************************************************************************/
/**
 * \fn verif_matrice(int matr[N][N] )
 * \brief Fonction qui affiche les cases.
 *
 * \param la matrice qui reprÃ©sente la grille.
 */

void  verif_matrice(int matr[N][N] ){/*verification du contenu de la matrice */

int i,j;

	for(i=1 ; i<= N ; i++){
	
		for(j=1 ; j<= N ; j++){
		
			printf("|%i|", matr[i][j]);
						
				}
		printf("\n");
	}
}
/*********************************************************************************************/
/**
 * \fn changerEtat(int c)
 * \brief Fonction qui permet de changer l'etat de la case .
 *
 * \param la valeur qui represente la case.
 */

int changerEtat(int c){/*changer l'etat de la case  de blanche representÃ© par un '0' Ã  noire representÃ© par un '1' et de noire Ã  blanche ou croix reprÃ©sentÃ© par un '2' */


	if(c==0)
		return 1;
	else if(c==1)
		return 2;
	else
		return 0;
	
	
		
}

/*********************************************************************************************/
/**
 * \fn max_h_Case(int a)
 * \brief Fonction qui verifie la limite des cases de la grille .
 *
 * \param la taille de la grille.
 */
int max_h_Case(int a){/*limite cases horizontales*/

  if(a%2==1){
    a=a-1;
    a++;}

return a;

 }
 /**
 * \fn max_v_Case(int b)
 * \brief Fonction qui verifie la limite des cases de la grille .
 *
 * \param la taille de la grille.
 */
 
int max_v_Case(int b){/*limite cases verticales*/

  if(b%2==1){
     b=b-1;
     b++;}

return b;


 }

/*********************************************************************************************/
/**
* \fn verifier_Case_Noire_Ligne( int matr[N][N], int ligne, int valeur)
 * \brief Fonction qui verifie que les cases noire correspondent au nombre horisentals de la matrice periphÃ©rique .
 *
 * \param la matrice qui represente la grille , les lignes de la grille, les valeurs de la matrice periphÃ©rique.
 */

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
			if(c==0){une seule valeur
				comp=true;
				}
			else
			{
				while(i<i+c && i<N-1 && find==true) 
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
		
	j++;
	}
return comp;
}

/*********************************************************************************************/
/**
* \fn verifier_Case_Noire_Col( int matr[N][N], int col, int valeur)
 * \brief Fonction qui verifie que les cases noire correspondent au nombre verticals de la matrice periphÃ©rique .
 *
 * \param la matrice qui represente la grille , les colonnes de la grille, les valeurs de la matrice periphÃ©rique.
 */
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
		
	j++;
	}
return comp;
}


/*********************************************************************************************/
/**
* \fn verifierGrille(int matd[N][N] , int matf[N][N])
 * \brief Fonction qui verifie si les cases la grille du joueur est correcte .
 *
 * \param la matrice qui represente la grille qu'il faut avoir, la matrice qui represente la grille du joueur.
 */


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
 
/**
 * \fn int main (void)
 * \brief EntrÃ©e du programme.
 *
 */
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
