/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdlib.h>

/**** Declaracao dos novos tipos ***/
//sera importante declarar antes pois havera referencia circular entre os tipos

int calculateEfields(element ***e, double **Ex, double **Ey);

double VonPoint(element ***e,double x, double y);