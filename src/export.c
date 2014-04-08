/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../headers/elements_nodes.h"
#include "../headers/global.h"

extern int nTotalNodes;
extern int nTotalElements;

int exportForFile(char *filename, element ***e, node ***n){
    int i,j,k;
    FILE *p;
    
    p=fopen(filename,"w");
    
    for(i=0;i<nTotalNodes;i++){
        
    }
    
    fclose(p);
    return(0);
}