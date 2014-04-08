/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdlib.h>
#include "../headers/elements_nodes.h"
#include "../headers/matrix_operations.h"

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
    node *temp;
    int i,j=0;
    double m[3][3];
    
    while(1){
        for(i=0;i<3;i++){
            m[i][0]=no[i]->x; m[i][1]=no[i]->y; m[i][2]=1.0;
        }
        if((m[0][0]=calculateDeterminant(m))>0){
            return(0);
        }else{
            j>2 ? j=0 : j++;
            temp=no[j];
            no[j]=no[0];
            no[0]=temp;
        }
    }
    return(0);
}

int setP(element *e){
    e->p[0]=(e->no[1]->x)*(e->no[2]->y)-(e->no[2]->x)*(e->no[1]->y);
    e->p[1]=(e->no[2]->x)*(e->no[0]->y)-(e->no[0]->x)*(e->no[2]->y);
    e->p[2]=(e->no[0]->x)*(e->no[1]->y)-(e->no[1]->x)*(e->no[0]->y);
    e->D=e->p[0]+e->p[1]+e->p[2];
    return(0);
}
int setQ(element *e){
    e->q[0]=e->no[1]->y - e->no[2]->y;
    e->q[1]=e->no[2]->y - e->no[0]->y;
    e->q[2]=e->no[0]->y - e->no[1]->y;
    return(0);
}
int setR(element *e){
    e->r[0]=e->no[2]->x - e->no[1]->x;
    e->r[1]=e->no[0]->x - e->no[2]->x;
    e->r[2]=e->no[1]->x - e->no[0]->x;
    return(0);
}

int setParamsN(element *e){
    int i,j,k;
    char buff[256];
    if(organizeNodes(e->no)<0){
        return(-1);
    }
    else{
        if(setP(e)<0 || setQ(e)<0 || setR(e)<0)
            return(-1);
    }
    return(0);
}

int generateElementsN(element ***e){
    int i,j,k;
    for(i=0;i<nTotalElements;i++){
        if(setParamsN((*e)[i])<0){
            pMsg("erro ao gerar os elementos");
        }
    }
    return(0);
}

int printMesh(element **e, node **n){
    int i,j,k;
    char buff[200];
    //printing nodes:
    printf("printing nodes...\n");
    for(i=0;i<nTotalNodes;i++){
        printf("node %d: ",i+1);
        printf("P(%3.3f, %3.3f) ",n[i]->x,n[i]->y);
        if((n[i]->val)!=NULL){
            printf("V=%f",*(n[i]->val));
        }else{
            printf("V=null");
        }
        printf("\n%d elementos associados a este node: ",n[i]->n_elements);
        printf("\n");
    }
    printf("printing elements...\n");
    for(i=0;i<nTotalElements;i++){
        printf("elemento %d eps=%.3e [F/m] D=%.2f\n",i,e[i]->eps,e[i]->D);
    }
    return(0);
}


int findLocalNodePos(element *e, node *no_global){
    int i,j,k;
    for(i=0;i<3;i++){
        if(e->no[i]==no_global)
            return(i);
    }
    return(-1);
}


int freeNodes(node ***n, int size){
    int i,j,k;
    
    for(i=0;i<size;i++){
        if((*n)[i]->val!=NULL)
            free((*n)[i]->val);
        if((*n)[i]->elements!=NULL){
            free((*n)[i]->elements);
        }
        if((*n)[i]!=NULL){
            free((*n)[i]);
        }
    }
    return(0);
}


int freeElements(element ***e, int size){
    int i,j,k;
    
    for(i=0;i<size;i++){
        if((*e)[i]!=NULL){
            free((*e)[i]);
        }
    }
    return(0);
}


