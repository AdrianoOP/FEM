/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdlib.h>
#include <math.h>
#include "../headers/elements_nodes.h"
#include "../headers/matrix_operations.h"
#include "../headers/global.h"

extern int nTotalElements;
extern int nTotalNodes;

double calculateDeterminant(double m[3][3]){
    //m= | m[0][0] m[0][1] m[0][2] |
    //   | m[1][0] m[1][1] m[1][2] |
    //   | m[2][0] m[2][1] m[2][2] |
    return((m[0][0]*m[1][1]*m[2][2]+m[0][1]*m[1][2]*m[2][0]+m[0][2]*m[1][0]*m[2][1])-
           (m[2][0]*m[1][1]*m[0][2]+m[2][1]*m[1][2]*m[0][0]+m[2][2]*m[1][0]*m[0][1]));
}

int printMatrix(double **m,int i_max,int j_max){
    int i,j;
    for(i=0;i<i_max;i++){
        printf("| ");
        for(j=0;j<j_max;j++){
            printf("%.1e ",m[i][j]);
        }
        printf("|\n");
    }
    return(0);
}

double max1d(double *v, int size){
    int i;
    double max=v[0];
    for(i=0;i<size;i++){
        max=(max>v[i]? max : v[i]);
    }
    
    return(max);
}

double min1d(double *v, int size){
    int i;
    double min=v[0];
    for(i=0;i<size;i++){
        min=(min<v[i]? min : v[i]);
    }
    return(min);
}

int freeMatrix(double **m,int imax){
    int i,j,k;
    
    for(i=0;i<imax;i++){
        if(m[i]!=NULL){
            free(m[i]);
        }
    }
    return(0);
}