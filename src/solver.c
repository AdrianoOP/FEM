/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdlib.h>
#include "../headers/elements_nodes.h"
#include "../headers/matrix_operations.h"
#include "../headers/global.h"

#define MAXITERATIONS 10000
#define MINERROR 1e-6

extern int nTotalElements;
extern int nTotalNodes;

int commomAssembly(double ***c, double ***v, node ***n, element ***e){
    int i,j,k;
    int local_pos1, local_pos2;
    double acumulator;
    (*v)=malloc(nTotalNodes*sizeof(double *));
    for(i=0;i<nTotalNodes;i++){
        (*c)[i]=malloc(nTotalNodes*sizeof(double));
        (*v)[i]=(*n)[i]->val; // matriz de solucao recebe o endereco do node
        if((*n)[i]->val!=NULL){ //caso seja condicao de contorno de dirichlet
            for(j=0;j<nTotalNodes;j++){
                //seta 1 para o termo j=i e zera o resto da linha
                (*c)[i][j] = (i!=j) ? 0.0 : 1.0;
            }
        }else{ //caso a condicao seja newman
            (*v)[i]=malloc(sizeof(double));
            *((*v)[i])=0;
            (*n)[i]->val=(*v)[i]; // matriz de solucao recebe o endereco do node
            for(j=0;j<nTotalNodes;j++){
                //cria os coeficientes para cada linha
                (*c)[i][j]=0;
                for(k=0;k<(*n)[i]->n_elements;k++){
                    //procura todos os elementos que tem relacao com o no em questao
                    local_pos1=findLocalNodePos((*n)[i]->elements[k],(*n)[i]);//procura a posicao local do no dentro do elemento
                    local_pos2=findLocalNodePos((*n)[i]->elements[k],(*n)[j]);//procura a posicao local do no dentro do elemento
                    if(local_pos1>-1 && local_pos2>-1){
                        //tendo as posicoes no no posso aplicar:
                        //c[i,j](e)=(eps(e)/(2*D(e))*(q[i](e)*q[j](e)+r[i](e)*r[j](e))
                        //i=local_pos1, j=local_pos2
                        //(*n)[i]->elements[k] == elemento (e)
                        acumulator=((*n)[i]->elements[k]->eps/(2*(*n)[i]->elements[k]->D))*
                        ((*n)[i]->elements[k]->q[local_pos1]*(*n)[i]->elements[k]->q[local_pos2] +
                         (*n)[i]->elements[k]->r[local_pos1]*(*n)[i]->elements[k]->r[local_pos2]);
                        (*c)[i][j]=(*c)[i][j]+acumulator;
                    }
                }
            }
        }
    }
    return(0);
}


int gaussSeidel(double **m, double ***ans,int size){
    int i,j,it;
    double *x_est1, *x_est2, *g, *d;
    double div;
    char buff[256];
    x_est1=malloc(size*sizeof(double));
    x_est2=malloc(size*sizeof(double));
    g=malloc(size*sizeof(double));
    d=malloc(size*sizeof(double));
    
    //formar os vetores e matrizes iniciais do problema
    for(i=0;i<size;i++){
        div=m[i][i];
        for(j=0;j<size;j++){
            if(i==j){
                g[i]=(*(*ans)[i])/div;
                x_est1[i]=g[i];
                m[i][j]=0;
            }else{
                m[i][j]=-m[i][j]/div;
            }
        }
    }
    //executa o metodo fazendo:
    //x(k)=Cx(k-1)+g no modo gaussSeidel
    for(it=0;it<MAXITERATIONS;it++){
        //para cada iteracao
        for(i=0;i<size;i++){
            x_est2[i]=0;
            for(j=0;j<size;j++){
                x_est2[i]=x_est2[i]+x_est1[j]*m[i][j];
            }
            x_est2[i]=x_est2[i]+g[i];
            d[i]=mod(x_est2[i]-x_est1[i]);
            x_est1[i]=x_est2[i];
        }

        //checa criterio de parada
        if(max1d(d,nTotalNodes)<MINERROR){
            for(i=0;i<nTotalNodes;i++){
                if((*ans)[i]==NULL)
                    (*ans)[i]=malloc(sizeof(double));
                *((*ans)[i])=x_est2[i];
            }
            sprintf(&buff,"convergencia em %d iteracoes\n",it);
            pMsg(&buff);
            break;
        }
    }
    free(x_est1);
    free(x_est2);
    free(g);
    free(d);
    return(0);
}