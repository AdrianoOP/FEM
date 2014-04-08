/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdlib.h>

double calculateDeterminant(double m[3][3]);

int printMatrix(double **m,int i_max,int j_max);

double max1d(double *v, int size);

double min1d(double *v, int size);

int freeMatrix(double **m,int imax);