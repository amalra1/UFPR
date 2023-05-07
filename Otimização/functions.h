#ifndef __FUNCTIONS__
#define __FUNCTIONS__

/* 
    Biblioteca feita para o programa que transforma entradas 
    para o modelo .lp para ser interpretado pelo lp solver


    Feita por Pedro Amaral Chapelin
    Data de finalizacao -> 07/05/2023
*/

#define TAM_LINHA 1024

// Estruturas
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

struct tabela
{
  int quantN;
  int quantM;

  produto_t n[1000];
  composto_t m[1000];
  float c[1000][1000];
};
typedef struct tabela tabela_t;

// Funcoes 
void le_produtos_e_compostos(char* linha, tabela_t* tabela);
void le_valores(char* linha, tabela_t* tabela);
void le_custos_e_limites(char* linha, tabela_t* tabela);
void le_quantsPorL(char* linha, tabela_t* tabela);

void imprime_dados(tabela_t* tabela);

#endif
