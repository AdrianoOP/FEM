/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdlib.h>

int importMeshFromFile(char *filename, node ***n, element ***e);

int createNode(char *buff, node *n,int pos);

int clearBuff(char *buff);

int createElement(char *buff, element *e,int pos, node **n);

int addElementToNode(node *n, element *e);
