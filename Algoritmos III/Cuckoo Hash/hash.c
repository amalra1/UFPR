#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include "hash.h"

/*
    Desenvolvido por:
        Davi Garcia Lazzarin
        Pedro Amaral Chapelin        
    Data: 29/01/2023
*/

int h1(int k){
    return k % M;
}

int h2(int k){
    int d=k * 0.9;
    float f=k * 0.9;
    d = M * (f-d); 
    return d;
}

Cuckoo_Hash_t* Hash_init(){
    int i;
	
	Cuckoo_Hash_t* T = malloc(sizeof(Cuckoo_Hash_t));
	if(!T)
		return NULL;
	
    T->T1 = malloc(sizeof(Elemento_TabelaHash_t) * M);
    if (!T->T1)
    	return NULL;

    T->T2 = malloc(sizeof(Elemento_TabelaHash_t) * M);
    if (!T->T2)
    	return NULL;
    
    for (i = 0; i < 11; i++){
        T->T1[i].chave = 0;
        T->T1[i].estado = VAZIO;

        T->T2[i].chave = 0;
        T->T2[i].estado = VAZIO;
    }
    
    return T;
}

//Limpa o rastro e libera memória
void destroy_Cuckoo_hash(Cuckoo_Hash_t* T){
    
    for(int i = 0; i<M; i++){

        T->T1[i].chave = 0;
        T->T1[i].estado = DELETADO;
        T->T2[i].chave = 0;
        T->T2[i].estado = DELETADO;
    };
    free(T->T1);
    free(T->T2);
    free(T);
}

//Busca um valor "chave" na tabela, retorna 1 se achar, 0 se não achar
//Retorna a localização da chave no vetor v={N da tabela, index}
int busca(Cuckoo_Hash_t* T, int chave, int v[2]){
    int i;

    i = h1(chave);

    // Se for deletado, verificamos a T2
    if (T->T1[i].estado == DELETADO){
       
       i = h2(chave);
       if (T->T2[i].chave == chave){
            v[0] = 2;
            v[1] = i;
            return 1;   
        }
    }

    // Se a chave for igual a do T1
    else if (T->T1[i].chave == chave){
        
        v[0] = 1;
        v[1] = i;
        return 1;   
    }

    // Se a chave for diferente da do T1, ve a T2
    else{

        i = h2(chave);
        if (T->T2[i].chave == chave){

            v[0] = 2;
            v[1] = i;
            return 1;   
        }
    }

    // Chegou ate aqui, nao achou
    return 0;
}

//Insere a chave nas tabelas
int inserir_hash_aberto(Cuckoo_Hash_t* T, int k){

    int indexT1, indexT2;
    int v[2];

    // funcao de busca pra verificar se existe em alguma T
    if (busca(T, k, v))
        return -1; 
   
    indexT1 = h1(k);
        
    // Se for vazio o slot, apenas insere
    if (T->T1[indexT1].estado == VAZIO || T->T1[indexT1].estado == DELETADO){

        T->T1[indexT1].chave = k;
        T->T1[indexT1].estado = OCUPADO;
        return indexT1;
    }

    // Se nao, move a chave do slot para T2 e insere
    else{

        indexT2 = h2(T->T1[indexT1].chave);

        T->T2[indexT2].chave = T->T1[indexT1].chave;
        T->T2[indexT2].estado = OCUPADO;
        T->T1[indexT1].chave = k;

        return indexT2;
    }
}

//Remove a chave das tabelas
int remove_hash(Cuckoo_Hash_t* T, int chave){

    int v[2];

    // Se nao esta em nenhuma T, impossivel remover
    if (!busca(T, chave, v))
        return -1;

    if (v[0] == 1){
        
        T->T1[v[1]].chave = 0;
        T->T1[v[1]].estado = DELETADO;
        return 1;
    }
    else{
        
        T->T2[v[1]].chave = 0;
        T->T2[v[1]].estado = DELETADO;
        return 1;
    } 
}

//Imprime a saída no padrão solicitado
void imprime_saida(Cuckoo_Hash_t* T){
    
    int i;
    
    for (i = 0; i < 11; i++){
        if (T->T2[i].estado == OCUPADO)
            printf("%d,T2,%d\n", T->T2[i].chave, i);       
    }

    for (i = 0; i < 11; i++){   
        if (T->T1[i].estado == OCUPADO)
            printf("%d,T1,%d\n", T->T1[i].chave, i);
    }
}
