/**************************************************************************************************/
/* PROJETO DE SOFTWARE PARA SIMULACAO DE ELETROMAGNETISMO UTILIZANDO METODO DOS ELEMENTOS FINITOS */
/* Desenvolvedor: Adriano Oliveira Pires */
/* pagina: https://github.com/AdrianoOP/FEM */
/********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/global.h"
#include "../headers/elements_nodes.h"
#define EPSILONO 8.85411878176e-12

extern int nTotalNodes;
extern int nTotalElements;


int importMeshFromFile(char *filename, node ***n, element ***e){
    char buf[256], buf2[256];
    char temp;
    FILE *fp;
    int i,j,k,l,m,o;
  
    pMsg("Iniciando a importacao de malha...\n");
    fp=fopen(filename,"r");
    
    if(fp<0){
        sprintf(&buf,"\nnao foi possivel ler o arquivo %s\n",filename);
        pMsg(buf);
        return(-1);
    }
    //else
    //foreach line
    i=0;
    j=0;
    k=1;
    m=1000;
    while(1){
        temp=fgetc(fp);
        if(temp<0)
            break;
        if(temp==':'){
            buf2[j]='\0';
            j=0;
            if(strcmp("nodes",buf2)==0){
                pMsg("lendo nodes\n");
                k=1;
                m=1;
                continue;
            }
            else if(strcmp("elements",buf2)==0){
                pMsg("lendo Elements\n");
                nTotalNodes=k-1;
                k=1;
                m=2;
                continue;
            }else{
                sprintf(&buf,"Erro ao ler %s em importMesh\n",buf2);
                pMsg(buf);
                break;
            }
        }
        if(temp=='\n'){
            if(j<3){
                //linha em branco
                j=0;
                continue;
            }
            //else
            buf2[j]=temp;
            j=0;
            if(m==1){//esta sendo lido o no
                *n=realloc(*n,k*sizeof(node *));
                if(!*n)
                    return(alocationMemoryError());
                
                (*n)[k-1]=malloc(sizeof(node));
                if(!(*n)[k-1])
                    return(alocationMemoryError());
                
                if(createNode(&buf2,(*n)[k-1],k)>0){
                    if((*n)[k-1]->val!=NULL){
                        sprintf(&buf,"node %d: x=%f y=%f val=%f\n",k,(*n)[k-1]->x,(*n)[k-1]->y,*((*n)[k-1]->val));
                        pMsg(buf);
                    }
                    k++;
                    continue;
                }else{
                    sprintf(&buf, "erro ao definir o no %d em importMesh\n",k);
                    pMsg(buf);
                    return(-1);
               }
            }else if(m==2){//esta sendo lido o elemento
                *e=realloc(*e,k*sizeof(element *));
                if(*e==NULL)
                    return(alocationMemoryError());
                (*e)[k-1]=(element *)malloc(sizeof(element));
                if((*e)[k-1]==NULL)
                    return(alocationMemoryError());
                
                if(createElement(buf2,(*e)[k-1],k,*n)>0){
                    sprintf(&buf,"element %d: no1=%f no2=%f no3=%f eps=%f\n",k,(*e)[k-1]->no[0]->x,(*e)[k-1]->no[1]->x,(*e)[k-1]->no[2]->x,(*e)[k-1]->eps);
                    pMsg(buf);
                }else{
                    sprintf(&buf, "erro ao definir o elemento %d em importMesh\n",k);
                    pMsg(buf);
                    return(-1);
                }
                k++;
            }
        }
        buf2[j]=temp;
        j++;
    }
    nTotalElements=k-1;
    sprintf(&buf,"fim do arquivo. Lidos %d nodes e %d elements\n",nTotalNodes, nTotalElements);
    pMsg(buf);
    return(0);
}

int createNode(char *buff, node *n, int pos){
    char buff2[200];
    char temp;
    int i,j,k;
    double dtemp;
    //buff contem os valores:
    // x y valor_no_node
    i=0;j=0;k=0;
    while(1){
        if(buff[i]=='\0'){
            buff2[j]=buff[i];
            if(strcmp(buff2,"null")<=0){
                n->val=(double *)malloc(sizeof(double));
                if(n->val==NULL)
                    return(alocationMemoryError());
                dtemp=atof(buff2);
                *(n->val)=dtemp;
                n->n_elements=0;
            }else{
                n->val=NULL;
            }
            return(1);
        }
        if(buff[i]==' '){
            switch(k){
                case 0:
                    j=0;
                    n->x=atof(buff2);
                    i++;//pula o caractere de espaco
                    k++;
                    clearBuff(buff2);
                    break;
                case 1:
                    n->y=atof(buff2);
                    j=0;
                    i++; //pula o caractere de espaco
                    k++;
                    clearBuff(buff2);
                    break;
                default:
                    pMsg("erro ao ler K em createNode\n");
                    break;
            }
            continue;
        }
        buff2[j]=buff[i];
        j++;
        i++;
    }
    return(1);
}

int createElement(char *buff, element *e,int pos, node **n){
    char buff2[200];
    char temp;
    int i,j,k;
    int itemp;
    double dtemp;
    
    //buff contem os valores:
    // node1 node2 node3 epsilonr
    i=0;j=0;k=0;
    while(1){
        if(buff[i]=='\0'){
            dtemp=atof(buff2);
            e->eps=EPSILONO*dtemp;
            return(1);
        }
        if(buff[i]==' '){
            switch(k){
                case 0:
                    j=0;
                    itemp=atoi(buff2);
                    if(addElementToNode(n[itemp-1], e)<0)
                        return(-1);
                    e->no[0]=n[itemp-1];
                    i++;//pula o caractere de espaco
                    k++;
                    clearBuff(buff2);
                    break;
                case 1:
                    itemp=atoi(buff2);
                    if(addElementToNode(n[itemp-1], e)<0)
                        return(-1);
                    e->no[1]=n[itemp-1];
                    j=0;
                    i++; //pula o caractere de espaco
                    k++;
                    clearBuff(buff2);
                    break;
                case 2:
                    itemp=atoi(buff2);
                    if(addElementToNode(n[itemp-1], e)<0)
                        return(-1);
                    
                    e->no[2]=n[itemp-1];
                    j=0;
                    i++; //pula o caractere de espaco
                    k++;
                    clearBuff(buff2);
                    break;
                default:
                    pMsg("erro ao ler K em createElement\n");
                    break;
            }
            continue;
        }
        buff2[j]=buff[i];
        j++;
        i++;
    }
    return(1);
}


int clearBuff(char *buff){
    int i=0;
    for(i=0;i<20;i++){
        buff[i]='\0';
    }
}

int addElementToNode(node *n, element *e){
    char buff[200];
    int i;
    if(n->elements==NULL || n->n_elements==0){
        n->elements=(element **)malloc(sizeof(element *));
        if(n->elements==NULL)
            return(alocationMemoryError());
        n->elements[0]=e;
        n->n_elements=1;
    }else{
        n->n_elements++;
        n->elements=(element **)realloc(n->elements,(n->n_elements)*sizeof(element *));
        if(n->elements==NULL)
            return(alocationMemoryError());
        n->elements[n->n_elements-1]=e;
    }
    return(0);
}
