/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/elements_nodes.h"
#include "headers/import.h"
#include "headers/matrix_operations.h"
#include "headers/global.h"
#include "headers/solver.h"
#include "headers/export.h"
#include "headers/physics/electrostatics.h"

extern int nTotalNodes;
extern int nTotalElements;

int main (int argc, char *argv[]){
    //declaracao de variaveis principais
    element **elements; //lista com os elementos
    node **nodes; //lista com os nos
    char buff[256];
    double *Ex, *Ey;
    time_t ti,tf,tdiff;
    
    
    //declaracao das funcoes principais em ordem de execucao
    int (*importMesh)(char *, node ***, element ***); //aqui as condicoes de contorno devem ser aplicadas
    int (*generateElements)(element ***); //aqui deverao ser calculados os parametros p,q,r,D
    //ao gerar os elementos deve-se lembrar de inicializar as funcoes principais tambem
    int (*exportAnswer)(char *, element ***, node ***);
   
  
    elements=malloc(sizeof(element *));
    nodes=malloc(sizeof(node *));
    Ex=malloc(sizeof(double));
    Ey=malloc(sizeof(double));
    
    //Associacao das funcoes
    importMesh=&importMeshFromFile;
    generateElements=&generateElementsN;
    exportAnswer=&exportForFile;

    if(importMesh("respostas.ans", &nodes, &elements)<0)
        return(-1);
    
    if(generateElements(&elements)<0)
        return(-1);
    
    printMesh(elements, nodes);
    
    if(calculateEfields(&elements,&Ex,&Ey)<0)
        return(-1);
    
    printf("Ex (V/m):\n");
    printMatrix(&Ex,1,nTotalElements);
    
    printf("Ey (V/m):\n");
    printMatrix(&Ey,1,nTotalElements);
    
    if(freeElements(&elements,nTotalElements) || freeNodes(&nodes, nTotalNodes))
        return(-1);
    
    free(elements);
    free(nodes);
    free(Ex);
    free(Ey);
    
    return(0);
}
