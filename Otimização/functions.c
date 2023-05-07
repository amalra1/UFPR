#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void le_produtos_e_compostos(char* linha, tabela_t* tabela)
{
  sscanf(linha, "%d %d", &tabela->quantN, &tabela->quantM);
}

void le_valores(char* linha, tabela_t* tabela)
{
  char* token;
  int i;

  token = strtok(linha, " ");
  i = 0;
  while (token != NULL) 
  {
    sscanf(token, "%f", &tabela->n[i].valor);

    i++;
    token = strtok(NULL, " ");
  }
}

void le_custos_e_limites(char* linha, tabela_t* tabela)
{
  char* token;
  int i;

  for (i = 0; i < tabela->quantM; i++)
  {
    token = strtok(linha, " ");

    sscanf(token, "%f", &tabela->m[i].custo);

    token = strtok(NULL, " ");

    if(token) 
      sscanf(token, "%d", &tabela->m[i].limite);

    fgets(linha, TAM_LINHA, stdin);
    }
}

void le_quantsPorL(char* linha, tabela_t* tabela)
{
  char* token;
  int i, j;

  // Nao precisamos ler a prox linha pois ja foi feito
  // isso no fim do loop anterior
  for (i = 0; i < tabela->quantN; i++)
  {
    token = strtok(linha, " ");

    for (j = 0; j < tabela->quantM; j++)
    {
      sscanf(token, "%f", &tabela->c[i][j]);
      token = strtok(NULL, " ");
    }

    fgets(linha, TAM_LINHA, stdin);
  }
}

void imprime_dados(tabela_t* tabela) 
{
  int i, j;

  printf("\nN = %d\n", tabela->quantN);
  printf("M = %d\n\n", tabela->quantM);

  for (i = 0; i < tabela->quantN; i++)
    printf("Valor N%d = %f\n", i, tabela->n[i].valor);

  printf("\n");

  for (i = 0; i < tabela->quantM; i++)
  {
    printf("Custo M%d = %f\n", i, tabela->m[i].custo);
    printf("limite M%d = %d\n\n", i, tabela->m[i].limite);
  }

  printf("\n");

  for (i = 0; i < tabela->quantN; i++)
  {
    for (j = 0; j < tabela->quantM; j++)
    {
      printf("C[%d][%d] = %f ", i, j, tabela->c[i][j]);
    }
    printf("\n");
  }
};