/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdlib.h>
#include "../headers/elements_nodes.h"

extern int nTotalElements;
extern int nTotalNodes;

//----Funcoes elements-----

/********************/
/* function: dist   */
/* input arg: node n, double x, double y */
/* output arg: double R */
/* description: retorna a distancia geometrica entre o node n e o ponto P(x,y)*/
double dist(node n, double x, double y);

/********************/
/* function: hasElement   */
/* input arg: node n, element *e */
/* output arg: int has */
/* description: retorna 1 se *e faz parte da lista de elementos de n*/
int hasElement(node n, element *e);


//----Funcoes nodes-----

/********************/
/* function: organizeNodes   */
/* input arg: node **no */
/* output arg: int ret */
/* description: organiza a matriz **no em sentido anti-horario*/
int organizeNodes(node *no[3]){
    //para organizar os nos no sentido anti-horario, pode-se pensar que:
    //(1) - sera escolhido o node com menor valor de x caso haja dois menores valores, escolhe-se o menos valor de y
    //(2) - sera escolhido o segundo node com menor valor de x caso haja dois valores iguais, escolhe-se o menor valor de y
    node *temp1,*temp2,*temp3;
    int i,j,k,l;
    double x1,x2,x3;
    double y1,y2,y3;
    double xmin=no[0]->x,ymin=no[0]->y;
    
    return(0);
}

int setP(element *e){
    return(0);
}
int setQ(element *e){
    return(0);
}
int setR(element *e){
    return(0);
}

int setParams(element *e){
    int i,j,k;
    char buff[256];
    if(organizeNodes<0)
        return(-1);
    //else
    if(setP(e)<0 || setQ(e)<0 || setR(e)<0)
        return(-1);

    return(0);
}
