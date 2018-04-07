/*********************************************************************************************/
/**
 * \fn max_h_Case(int a)
 * \brief Fonction qui vérifie la limite des cases de la grille.
 *
 * \param a La taille de la grille.
 */
/*int max_h_Case(int a) {
	if(a%2 == 1) {
		a = a-1;
		a++;
	}

	return a;
}*/
/**
 * \fn max_v_Case(int b)
 * \brief Fonction qui vérifie la limite des cases de la grille .
 *
 * \param b La taille de la grille.
 */

/*int max_v_Case(int b) {
	if(b%2 == 1) {
		b = b-1;
		b++;
	}

	return b;
} //*/

/*********************************************************************************************/
/**
 * \fn verifier_Case_Noire_Ligne( t_couleurs matr[N][N], int ligne, int valeur)
 * \brief Fonction qui vérifie que les cases noire correspondent au nombre horisentals de la matrice periphérique .
 *
 * \param matr La matrice qui represente la grille
 * \param ligne Les lignes de la grille
 * \param valeur Les valeurs de la matrice periphérique
 */

/*_Bool verifier_Case_Noire_Ligne( t_couleurs matr[N][N], int ligne, int valeur){
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
				*//*trois condition :
				1ere parcourir le reste des cases a verifier ;
				2eme on verifie qu'on a pas atteint la fin de la ligne ;
				3eme on s'arrete quand on trouve une case noiree*/ 
				/*while(i<i+c && i<N-1 && find==true)
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
} //*/
/*********************************************************************************************/
/**
* \fn verifier_Case_Noire_Col( t_couleurs matr[N][N], int col, int valeur)
 * \brief Fonction qui verifie que les cases noire correspondent au nombre verticals de la matrice periphÃ©rique .
 *
 * \param matr La matrice qui représente la grille
 * \param col Les colonnes de la grille
 * \param valeur Les valeurs de la matrice periphérique
 */
/*_Bool verifier_Case_Noire_Col( t_couleurs matr[N][N], int col, int valeur){
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
} //*/

