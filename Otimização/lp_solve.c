#include <stdio.h>
#include <stdlib.h>


struct composto
{
  int limite;
  float custo;
};
typedef struct composto composto_t;

struct produto
{
  float valor;
};
typedef struct produto produto_t;




int main () 
{ 
  FILE* arqLP, *arqIN;
  float inputF;
  int inputI, i, j;
  int quantM, quantN;

  produto_t n[1000];
  composto_t m[1000];
  float quantPorL[1000][1000];

  arqIN = fopen("entrada.in", "r");

  // Teste se o arquivo abre
  if (arqIN == NULL)
  {
    printf("Erro ao abrir arquivo de entrada\n");
    exit(1);
  }

  // Le N
  printf("Digite a quantidade de N:\n");
  scanf("%d", &inputI);
  quantN = inputI;

  // Le M
  printf("Agora a quantidade de M:\n");
  scanf("%d", &inputI);
  quantM = inputI;

  // Le v's
  printf("Agora o valor de cada produto:\n\n");
  for (i = 0; i < quantN; i++)
  {
    printf("produto [%d]\n", i);
    printf("valor = ");
    scanf("%f", &inputF);
    n[i].valor = inputF;
    printf("\n");
  }

  // Le linhas seguintes
  printf("Agora o custo e o limite de cada composto:\n\n");
  for (i = 0; i < quantM; i++)
  {
    printf("composto [%d]\n", i);
    printf("custo = ");
    scanf("%f", &inputF);
    m[i].custo = inputF;

    printf("limite = ");
    scanf("%d", &inputI);
    m[i].limite = inputI;
    printf("\n");
  }

  // Le os c's
  printf("Agora a quantidade por L:\n\n");
  for (i = 0; i < quantN; i++)
  {
    for (j = 0; j < quantM; j++)
    {
      printf("Quantidade de composto [%d] no produto [%d]: ", j, i);
      scanf("%f", &quantPorL[i][j]);
      printf("\n");
    }
  }

  for (i = 0; i < quantN; i++)
  {
    for (j = 0; j < quantM; j++)
    {
      printf("C[%d][%d] = %f ", i, j, quantPorL[i][j]);
    }

    printf("\n");
  }

  fclose(arqIN);
















  // for (i = 0; i < quantM; i++)
  // {
  //   printf("composto [%d]\n", i);
  //   printf("custo = %f\n", m[i].custo);
  //   printf("limite = %d\n\n", m[i].limite);
  // }




  //system("lp_solve -S3 < model.lp");

  


  return 0;
}

