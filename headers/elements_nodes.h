/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdlib.h>

/**** Declaracao dos novos tipos ***/
//sera importante declarar antes pois havera referencia circular entre os tipos
typedef struct node node;
typedef struct element element;


/******* tipo Node e funcoes associadas *****/
//---Estruturas de dados ---
struct node{
  double x,y; // coordenadas
  double *val; //armazena o valor escalar do node. Null caso nao seja cond. de contorno
  int n_elements; //indica o numero de elements se utilizam deste node
  element **elements; // gera um vetor com n_elements posicoes apontando para os elementos que utilizam este node 
};

//----Funcoes-----

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


int findLocalNodePos(element *e, node *no_global);

int findGlobalNodeIntoElement(element *e, node **no_global,int localNode);

int freeNodes(node ***n, int size);


/******* tipo element e funcoes associadas *****/
//---Estruturas de dados ---
struct element{
  node *no[3]; // vetor de apontadores para os nos associados ao elemento
  double p[3],q[3],r[3]; // parametros p q e r
  double D; // parametro D
  double eps; //permissividade do elemento
};

//----Funcoes-----

/********************/
/* function: organizeNodes   */
/* input arg: node **no */
/* output arg: int ret */
/* description: organiza a matriz **no em sentido anti-horario*/
int organizeNodes(node *no[3]);

int setP(element *e);
int setQ(element *e);
int setR(element *e);
int setParamsN(element *e);

int generateElementsN(element ***e);

int printMesh(element **e, node **n);

int freeElements(element ***e, int size);
