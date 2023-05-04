#include<stdio.h>
#include<stdlib.h>
#include "hash.h"

/*
    Desenvolvido por:
        Davi Garcia Lazzarin
        Pedro Amaral Chapelin        
    Data: 29/01/2023
*/

#define TAM_LINHA 10

int main(){

    Cuckoo_Hash_t *T;
    T=Hash_init();

    if (!T){
        perror("Erro ao alocar memória para a tabela");
        return 1;
    }

    char opt,  linha[TAM_LINHA];
    int k;

    //Lê o stdin
    while(!feof (stdin)){
        
        fgets(linha, TAM_LINHA, stdin);
        opt=linha[0];

        for (int x = 0; x<2; x++)
            linha[x]='0';

        k=atoi(linha);
       
        if (opt == 'i'){

            inserir_hash_aberto(T, k);
        }
        else if (opt == 'r'){

            remove_hash(T, k);
        }   
    }//while

    imprime_saida(T);
    destroy_Cuckoo_hash(T);

    return 0;
}
