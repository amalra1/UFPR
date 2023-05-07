#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


int main () 
{ 
  FILE* arqLP;
  tabela_t *tabela = malloc(sizeof(tabela_t));
  char linha[TAM_LINHA];


  // ETAPA 1 - COLETA DOS DADOS

  fgets(linha, TAM_LINHA, stdin);
  le_produtos_e_compostos(linha, tabela);

  fgets(linha, TAM_LINHA, stdin);
  le_valores(linha, tabela);

  fgets(linha, TAM_LINHA, stdin);
  le_custos_e_limites(linha, tabela);

  le_quantsPorL(linha, tabela);

  imprime_dados(tabela);

  // ETAPA 2 - ESCRITA EM UM ARQUIVO NO MODELO ACEITO PELO LP_SOLVE

  arqLP = fopen("entrada.lp", "w");









  /*arqIN = fopen("entrada.in", "r");

  // Teste se o arquivo abre
  if (arqIN == NULL)
  {
    printf("Erro ao abrir arquivo de entrada\n");
    exit(1);
  }

  fclose(arqIN);*/

  // for (i = 0; i < quantM; i++)
  // {
  //   printf("composto [%d]\n", i);
  //   printf("custo = %f\n", m[i].custo);
  //   printf("limite = %d\n\n", m[i].limite);
  // }

  //system("lp_solve -S3 < model.lp");


  fclose(arqLP);
  free(tabela);

  return 0;
}

