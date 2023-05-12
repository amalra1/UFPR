#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


int main () 
{ 
  FILE* arqLP;
  tabela_t *tabela = malloc(sizeof(tabela_t));
  char linha[TAM_LINHA];
  int i, j;
  float aux;


  // ETAPA 1 - COLETA DOS DADOS

  fgets(linha, TAM_LINHA, stdin);
  le_produtos_e_compostos(linha, tabela);

  fgets(linha, TAM_LINHA, stdin);
  le_valores(linha, tabela);

  fgets(linha, TAM_LINHA, stdin);
  le_custos_e_limites(linha, tabela);

  le_quantsPorL(linha, tabela);

  // ETAPA 2 - ESCRITA EM UM ARQUIVO NO MODELO ACEITO PELO LP_SOLVE

  strcpy(linha, "");
  arqLP = fopen("entrada.lp", "w");

  // Testa se o arquivo abre
  if (!arqLP)
  {
    printf("Impossivel abrir arquivo\n");
    exit(1);
  }

  // Escreve funcao objetivo
  i = 0;
  fprintf(arqLP, "max: ");
  while (i < tabela->quantN - 1)
  {
    aux = 0;

    for (j = 0; j < tabela->quantM; j++)
      aux += tabela->c[i][j] * tabela->m[j].custo;

    fprintf(arqLP, "%.1fx%d + ", tabela->n[i].valor - aux, i + 1);
    i++;
  }

  // Faz o mesmo para o ultimo composto
  aux = 0;
  for (j = 0; j < tabela->quantM; j++)
      aux += tabela->c[i][j] * tabela->m[j].custo;

  fprintf(arqLP, "%.1fx%d;\n\n", tabela->n[i].valor - aux, i + 1);
  

  // Escreve as restricoes 
  j = 0;
  while (j < tabela->quantM)
  {
    i = 0;
    while (i < tabela->quantN - 1)
    {
      fprintf(arqLP, "%.1fx%d + ", tabela->c[i][j], i + 1);
      i++;
    }

    fprintf(arqLP, "%.1fx%d <= %d;\n", tabela->c[i][j], i + 1, tabela->m[j].limite);
    j++;
  }

  // Restricoes de nao-negatividade
  i = 0;
  for (i = 0; i < tabela->quantN; i++)
    fprintf(arqLP, "x%d >= 0;\n", i + 1);


  fclose(arqLP);
  free(tabela);

  return 0;
}

