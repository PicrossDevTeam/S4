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
#include"Case.h"
/**
* \def N
* \brief la taille de la matrice.
*/
#define N 

/**
 * \fn void  init_case(t_couleurs matr[N][N])
 * \brief Fonction d'initialisation des cases.
 *
 * \param la matrice qui reprÃ©sente la grille.
 */


void  init_case(t_couleurs matr[N][N]){/*initialiser toutes les cases Ã  0 */

int i,j;

	for(i=0 ; i<= N ; i++)
	
		for(j=0 ; j<= N ; j++){
		
			matr[i][j] = 0;
			
				}
	
}
/*********************************************************************************************/
/**
 * \fn verif_matrice(t_couleurs matr[N][N] )
 * \brief Fonction qui affiche les cases.
 *
 * \param la matrice qui reprÃ©sente la grille.
 */

void  verif_matrice(t_couleurs matr[N][N] ){/*verification du contenu de la matrice */

int i,j;

	for(i=0 ; i<= N ; i++){
	
		for(j=0 ; j<= N ; j++){
		
			printf("|%i|", matr[i][j]);
						
				}
		printf("\n");
	}
}
/*********************************************************************************************/
/**
 * \fn changerEtat(t_couleurs matr[N][N], int x, int y)
 * \brief Fonction qui permet de changer l'etat de la case .
 *
 * \param la matrice ui represente la grille.
 */

int changerEtat(t_couleurs matr[N][N], int x, int y){/*changer l'etat de la case  de blanche representÃ© par un '0' Ã  noire representÃ© par un '1' et de noire Ã  blanche ou croix reprÃ©sentÃ© par un '2' */


	if(matr[x][y]==0)
		matr[x][y]= 1;
	else if(matr[x][y]==1)
		matr[x][y] = 2;
	else
		matr[x][y] = 0;
	
	
		
}

int saisir_coord(t_couleurs matr[N][N], int niveau){
	int i = 0, j =0,  taille = 0;
	
	
	if(niveau == 1)
		taille =3;
	else if(niveau == 2)
		taille =4;
	else if(niveau == 3)
		taille =5;
	else if(niveau == 4)
		taille =10;

	while((i < 1 || i > taille) && (j < 1 || j > taille)) {
		
		printf("i=");
		scanf("%i", &i);
		printf("j=");
		scanf("%i", &j);
		
		if(i==-1 && j==-1) 
			return 1;

 	}
	changerEtat(matr,i-1,j-1);
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
* \fn verifier_Case_Noire_Ligne( t_couleurs matr[N][N], int ligne, int valeur)
 * \brief Fonction qui verifie que les cases noire correspondent au nombre horisentals de la matrice periphÃ©rique .
 *
 * \param la matrice qui represente la grille , les lignes de la grille, les valeurs de la matrice periphÃ©rique.
 */

_Bool verifier_Case_Noire_Ligne( t_couleurs matr[N][N], int ligne, int valeur){/*verifier si les cases noire correspondent au nombres horizontals*/

int i,j=0; 
_Bool comp=false,find=false;   ///find : trouver une case noire/ comp : trouver toute les cases
int c=0;    //compteur qui correspond au nombre de case a trouvé

	while(j<N-1 && comp==false)       // parcourir toute la ligne et on a pas encore trouvé toute les cases
	{
		if(matr[ligne][j]==1)          // si on a trouvé la premiére case noire
		{
			i=j+1;                     //on verifi la deuxiéme case
			find=true;                //on a trouvé la premiére case
			c=valeur-1;              //parcourir les cases restantes
			if(c==0){               // si il est demandé de trouver qu'une seule valeur
				comp=true;
				}
			else
			{
				while(i<i+c && i<N-1 && find==true)     	/*trois condition : 1ere parcourir le reste des cases a verifier/2eme
															on verifie qu'on a pas atteint la fin de la ligne/3eme on s'arrete quand on trouve une case noiree*/ 
				{
					if(matr[ligne][i]==1){                //on a trouvé la deuxieme case noire
						i++;}                             //on passe a la case à coté
					else{
						find=false;}                    // si la deuxiéme n'est pas noire on sort de la boucle
				}
					if(find==true){
						comp=true;}
					else{                     // remetre le compteur à 0 pour la prochaine recherche
						c=0;}
			 }
		}
		
	j++;
	}
return comp;
}
/*********************************************************************************************/
/**
* \fn verifier_Case_Noire_Col( t_couleurs matr[N][N], int col, int valeur)
 * \brief Fonction qui verifie que les cases noire correspondent au nombre verticals de la matrice periphÃ©rique .
 *
 * \param la matrice qui represente la grille , les colonnes de la grille, les valeurs de la matrice periphÃ©rique.
 */
_Bool verifier_Case_Noire_Col( t_couleurs matr[N][N], int col, int valeur){/*verifier si les cases noire correspondent au nombres verticals*/

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
/*int main()

{

int U[5][5], c;
_Bool b=false;



init_case(U);
verif_matrice(U);
printf("---------------\n");


c = saisir_coord(U,2);
verif_matrice(U);
printf("\n c = %i\n\n",c);

 int k= max_h_Case(5);
    	printf("%d\n",k);
    int V= max_v_Case(5);
   	 printf("%d\n",V);

//verification d'une ligne

b=verifier_Case_Noire_Ligne(U,2,1);
	if(b==true){
		printf("Bravooo");}
	else{
		printf("Reessayer");}

 return 0;
}*/
