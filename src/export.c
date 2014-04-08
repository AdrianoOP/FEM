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
    fprintf(p,"nodes:\n");
    for(i=0;i<nTotalNodes;i++){
        fprintf(p,"%f %f %f\n",(*n)[i]->x,(*n)[i]->y,*((*n)[i]->val));
    }
    
    fprintf(p,"elements:\n");
    for(i=0;i<nTotalElements;i++){
        fprintf(p,"%d %d %d %.7e\n",findGlobalNodeIntoElement((*e)[i],(*n),0),findGlobalNodeIntoElement((*e)[i],(*n),1),
                findGlobalNodeIntoElement((*e)[i],(*n),2),(*e)[i]->eps);
    }
    
    fclose(p);
    return(0);
}