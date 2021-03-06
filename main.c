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

extern int nTotalNodes;
extern int nTotalElements;

int main (int argc, char *argv[]){
  //declaracao de variaveis principais
  element **elements; //lista com os elementos
  node **nodes; //lista com os nos
  double **globalMatrix;//matriz global de coeficientes
  double **globalAnsVector;//Vetor global de respostas
    char buff[256];
    char importFile[256];
    
    time_t ti,tf;
    
    switch(argc){
        case 2:
            strcpy(&importFile,argv[1]);
            break;
        default:
            strcpy(&importFile,"input.inp");
            break;
    }
    
  //declaracao das funcoes principais em ordem de execucao
    int (*importMesh)(char *, node ***, element ***); //aqui as condicoes de contorno devem ser aplicadas
    int (*generateElements)(element ***); //aqui deverao ser calculados os parametros p,q,r,D
  //ao gerar os elementos deve-se lembrar de inicializar as funcoes principais tambem
    int (*assemblyMatrix)(double ***, double ***, node ***, element ***);
    int (*solve)(double **, double ***,int);
    int (*atualizeNodes)(double *, node **);
    int (*exportAnswer)(char *, element ***, node ***);
   
  
    elements=malloc(sizeof(element *));
    nodes=malloc(sizeof(node *));
    globalMatrix=malloc(sizeof(double *));
    globalAnsVector=malloc(sizeof(double *));
    
  //Associacao das funcoes
    importMesh=&importMeshFromFile;
    generateElements=&generateElementsN;
    assemblyMatrix=&commomAssembly;
    solve=&gaussSeidel;
    exportAnswer=&exportForFile;
  
    
    if(importMesh(importFile, &nodes, &elements)<0)
        return(-1);
    
    if(generateElements(&elements)<0)
        return(-1);
    
    printMesh(elements, nodes);
    
    if(commomAssembly(&globalMatrix,&globalAnsVector,&nodes,&elements)<0)
        return(-1);
    
    printf("\nmatriz problema:\n");
    printMatrix(globalMatrix,nTotalNodes,nTotalNodes);
    
    if(solve(globalMatrix,&globalAnsVector,nTotalNodes)<0)
        return(-1);
    
    printf("\nVetor Solucoes:\n");
    printMatrix(globalAnsVector,nTotalNodes,1);
    
    printMesh(elements, nodes);
    
    if(exportAnswer("respostas.ans",&elements,&nodes)<0)
        return(-1);
    
    
    if(freeElements(&elements,nTotalElements) || freeNodes(&nodes, nTotalNodes))
        return(-1);
    
    //libera as matrizes alocadas dinamicamente
    if(freeMatrix(globalMatrix,nTotalNodes)<0)
        return(-1);
    
    free(elements);
    free(nodes);
    free(globalAnsVector);
    free(globalMatrix);
    
    return(0);
}
