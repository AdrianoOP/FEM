/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdlib.h>
#include "../../headers/elements_nodes.h"
#include "../../headers/matrix_operations.h"
#include "../../headers/global.h"

extern int nTotalElements;
extern int nTotalNodes;

int calculateEfields(element ***e, double **Ex, double **Ey){
    int i,j,k;
    
    *Ex=realloc(*Ex,nTotalElements*sizeof(double));
    *Ey=realloc(*Ey,nTotalElements*sizeof(double));
    
    for(i=0;i<nTotalElements;i++){
        //para cada elemento
        (*Ex)[i]=(-1/(*e)[i]->D)*(*((*e)[i]->no[0]->val)*(*e)[i]->q[0]+
                        *((*e)[i]->no[1]->val)*(*e)[i]->q[1]+
                        *((*e)[i]->no[2]->val)*(*e)[i]->q[2]);
        (*Ey)[i]=(-1/(*e)[i]->D)*(*((*e)[i]->no[0]->val)*(*e)[i]->r[0]+
                    *((*e)[i]->no[1]->val)*(*e)[i]->r[1]+
                    *((*e)[i]->no[2]->val)*(*e)[i]->r[2]);
    }
    return(0);
}