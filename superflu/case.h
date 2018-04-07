#include<stdio.h>
#include<stdlib.h>



typedef enum couleurs{blanc, noir, croix}t_couleurs;
typedef struct Case{t_couleurs etat;}t_Case;
double * creerMatrice(int n);
void afficherMatrice(int n, double * A);