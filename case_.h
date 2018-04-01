#ifndef __CASE_H__
#define __CASE_H__

#include<stdio.h>
#include<stdlib.h>

typedef struct cocher
{
	int croix;
	struct cocher *noire, *blanche;
}t_cocher;

typedef struct cocher* t_caz;
 
int caz_blanche(t_caz );
t_caz caz_noire(t_caz );
int modif_caz(t_caz , int );


#endif
