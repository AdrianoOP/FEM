/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdio.h>
#include <stdlib.h>
#include "headers/elements_nodes.h"
#include "headers/import.h"
#include "headers/global.h"
//#include "headers/solver.h"
//#include "headers/export.h"

int main (int argc, char *argv[]){
  //declaracao de variaveis principais
  element **elements; //lista com os elementos
  node **nodes; //lista com os nos
  double **globalMatrix;//matriz global de coeficientes
  double *globalAnsVector;//Vetor global de respostas
    char buff[256];
  //declaracao das funcoes principais em ordem de execucao
    int (*importMesh)(char *, node ***, element ***); //aqui as condicoes de contorno devem ser aplicadas
  int (*generateElements)(element **, node **); //aqui deverao ser calculados os parametros p,q,r,D
  //ao gerar os elementos deve-se lembrar de inicializar as funcoes principais tambem
  int (*assemblyMatrix)(element **);
  int (*solve)(double **, double *);
  int (*atualizeNodes)(double *, node **);
  int (*exportAnswer)(node **);
    int (*setParams)(element *);
  
    elements=malloc(sizeof(element *));
    nodes=malloc(sizeof(node *));
    printf("nodes %p\n", &nodes);
    printf("elements %p\n", &elements);
    
  //Associacao das funcoes
    importMesh=&importMeshFromFile;
    generateElements=&generateElements;
    setParams=&setParams;

    sprintf(&buff,"Resultado de importmesh: %d\n",importMesh("input.inp", &nodes, &elements));
    pMsg(buff);
    printMesh(elements, nodes);
    return(0);
}
