/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../headers/elements_nodes.h"
#include "../headers/global.h"
#define DEBUG_MODE

int pMsg(char *msg){
  #ifdef DEBUG_MODE
  printf(msg);
  return(0);
  #else
  return(1);
  #endif
}

int alocationMemoryError(){
    pMsg("Erro de alocacao de memoria\n");
    return(-1);
}
