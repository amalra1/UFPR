#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Implementtação da Árvore AVL com algumas operações.

    Desenvolvida por Pedro Amaral Chapelin
    Data de finalização = 02/12/2022
*/

// Arvore AVL
typedef struct no {

    int chave;  // Um valor
    struct no* esq;  // Um ponteiro pro seu filho da esquerda
    struct no* dir;  // Um ponteiro pro seu filho da direita
    struct no* pai;  // Um ponteiro pro seu pai
    int alt;  // Um numero indicando a altura do no 
}tNo;

tNo* cria_nodo(int chave);
tNo* inclui (tNo* raiz, tNo* no, int chave);
tNo* TreeMinimum(tNo* x);
tNo* TreeMaximum(tNo* x); 
tNo* TreeDelete(tNo* raiz, tNo* no, int chave);
void printTreeEmOrdem(tNo* n);
void printTreePreOrdem(tNo* n);
void printTreePosOrdem(tNo* n);
tNo* rotEsq(tNo* raiz, tNo* x);
tNo* rotDir(tNo* raiz, tNo* x);
tNo* search(tNo* raiz, int chave); 
int altura(tNo* n); 

int main ()
{
    tNo* raiz = NULL;
    tNo* aux;
    char chave[17] = "";
    int ind, chaveINT;
    char input[20];

    printf("Operações com Árvore AVL\n\n");
    printf("Digite a opcao [r] para remover, [i] para inserir, [s] para sair, e o número desta forma:\n");
    printf("[r, i ou s] [espaço] [número] [enter], e digite a opcao [s] quando quiser parar.\n\n: ");
    fgets(input, sizeof(input), stdin);

    // Enquanto o usuário não digita 's'
    while (input[0] != 's')
    {
        // Verifica se a opção foi passada corretamente
        while (input[0] != 'i' && input[0] != 'r' && input[0] != 's')
        {
            printf("opção inválida, digite novamente.\n");
            fgets(input, sizeof(input), stdin);
        }

        // Pega o número passado e o transforma em inteiro
        ind = 2;
        while (input[ind] != '\0')
        {
            strncat(chave, &input[ind], 1);
            ind++;
        }

        chaveINT = atoi(chave);
        strcpy(chave, "");

        if (input[0] == 'i')
            raiz = inclui(raiz, raiz, chaveINT);

        else if (input[0] == 'r')
        {
            // Veriifcando se o valor existe na árvore
            aux = search(raiz, chaveINT);

            if (!aux)
                printf("Valor não encontrado na árvore, prosseguindo\n");
            else
                raiz = TreeDelete(raiz, aux, chaveINT);
        }

    printf("Digite novamente.\n: ");
    fgets(input, sizeof(input), stdin);
    }

    printf("\n");
    printTreeEmOrdem(raiz);
    free(raiz);
    
    return 0;  
}

// Funcao que cria um nodo da arvore e o retorna
tNo* cria_nodo(int chave)
{
    tNo* n = (tNo*)malloc(sizeof(tNo));

    n->chave = chave;
    n->esq = NULL;
    n->dir = NULL;
    n->pai = NULL;
    n->alt = 1;

    return n;
}

// Funcao que verifica se uma chave está na árvore
// Retorna 1 se sim e 0 se não
tNo* search(tNo* raiz, int chave) 
{ 
    while (raiz != NULL)
    {
        if (chave > raiz->chave) 
            raiz = raiz->dir; 

        else if (chave < raiz->chave) 
            raiz = raiz->esq; 

        else
            return raiz;
    } 
    return NULL; 
} 

// Funcao que pega a altura da subarvore passada
int altura(tNo* n)
{
    if (n == NULL)
        return 0;

    return n->alt;
}

// Funcao que retorna o maximo entre dois inteiros
int max(int a, int b)
{
    if (a > b)
        return a;

    return b;
}

// Pega o fator de balanceamento (BF) de um nodo
int pegaBF(tNo* n)
{
    if (n == NULL)
        return 0;

    return altura(n->esq) - altura(n->dir);
}

// Funcao de inclusao na arvore, passar como parametro inicial o no raiz
tNo* inclui(tNo* raiz, tNo* no, int chave)
{
    int BF;

    // 1 - Inclusao normal da BST

    // Se a arvore for vazia, cria um nodo e adiciona a chave
    if (no == NULL)
        return cria_nodo(chave);

    // Se a chave for menor do que a em questao, vai para a esquerda
    if (chave < no->chave)
    {
        no->esq = inclui(raiz, no->esq, chave);
        no->esq->pai = no;
    }

    // Se for maior, vai para a direita
    else
    {
        no->dir = inclui(raiz, no->dir, chave);
        no->dir->pai = no;
    }

    // 2 - Atualizar tamanho do nodo atual

    no->alt = 1 + max(altura(no->esq), altura(no->dir));

    // 3. Pega o fator de balanceamento (BF) desse no para checar se
    // ficou desbalanceado
    BF = pegaBF(no);

    // Se o no ficar desbalanceado, temos os 4 casos de ZigZig e ZigZag

    // EsqEsq (ZigZig)
    if (BF > 1 && chave < no->esq->chave)
        return rotDir(raiz, no);
 
    // DirDir (ZigZig)
    if (BF < -1 && chave > no->dir->chave)
        return rotEsq(raiz, no);
 
    // EsqDir (ZigZag)
    if (BF > 1 && chave > no->esq->chave)
    {
        //printf("ZIGZAG\n");
        no->esq = rotEsq(raiz, no->esq);
        return rotDir(raiz, no);
    }
 
    // DirEsq (ZigZag)
    if (BF < -1 && chave < no->dir->chave)
    {
        //printf("ZIGZAG\n");
        no->dir = rotDir(raiz, no->dir);
        return rotEsq(raiz, no);
    }

    return no;
}

// Funcao que retorna o menor valor de uma arvore
// Passando o 'x' como 'no->dir', acha o sucessor 
// de uma subarvore
tNo* TreeMinimum(tNo* x)
{
    while (x->esq != NULL)
        x = x->esq;

    return x;
}

// Funcao que retorna o maior valor de uma arvore
// Passando o 'x' como 'no->esq', acha o antecessor 
// de uma subarvore
tNo* TreeMaximum(tNo* x)
{
    while (x->dir != NULL)
        x = x->dir;

    return x;
}

// Funcao auxiliar do 'TreeDelete' que realiza a troca dos
// ponteiros de dois nós
tNo* Transplant(tNo* raiz, tNo* u, tNo* v)
{   
    if (u->pai == NULL)
        raiz = v;

    // 'u' eh o filho da esquerda
    else if (u == u->pai->esq)
        u->pai->esq = v;

    // 'u' eh o filho da direita
    else
        u->pai->dir = v;

    if (v != NULL)
        v->pai = u->pai;

    return raiz;
}

// Funcao que deleta um no especifico da arvore AVL e a reorganiza
// com substituicao pelo sucessor
tNo* TreeDelete(tNo* raiz, tNo* no, int chave)
{
    int BF;
    tNo* y;

    // DELETANDO O NODO

    // Caso 'A'
    if (no->esq == NULL)
        raiz = Transplant(raiz, no, no->dir);

    // Caso 'B'
    else if (no->dir == NULL)
        raiz = Transplant(raiz, no, no->esq);

    else
    {
        // Substituindo pelo antecessor
        y = TreeMaximum(no->esq);

        // Caso 'D'
        if (y->pai != no)
        {
            raiz = Transplant(raiz, y, y->dir);
            y->dir = no->dir;
            y->dir->pai = y;
        }

        // Caso 'C'
        raiz = Transplant(raiz, no, y);
        y->esq = no->esq;
        y->esq->pai = y;

    }

    // Se a árvore posuia apenas um nodo, retorna
    if (no == NULL)
      return raiz;

    // Aqui vamos verificando o BF de cada nodo, do substituido, ate o 
    // começo da árvore, para ver o que rotacionar
    while (no != NULL)
    {
        // RE-BALANCEANDO ÁRVORE

        // Atualiza altura
        no->alt = 1 + max(altura(no->esq), altura(no->dir));
    
        BF = pegaBF(no);
        
        // ZigZig (EsqEsq)
        if (BF > 1 && pegaBF(no->esq) >= 0)
            return rotDir(raiz, no);
    
        // ZigZag (EsqDir)
        if (BF > 1 && pegaBF(no->esq) < 0)
        {
            no->esq = rotEsq(raiz, no->esq);
            return rotDir(raiz, no);
        }
    
        // ZigZig (DirDir)
        if (BF < -1 && pegaBF(no->dir) <= 0)
            return rotEsq(raiz, no);
    
        // ZigZag (DirEsq)
        if (BF < -1 && pegaBF(no->dir) > 0)
        {
            no->dir = rotDir(raiz, no->dir);
            return rotEsq(raiz, no);
        }

        no = no->pai;
    }
  
    return raiz;
}

// Função que rotaciona a árvore para a esquerda
tNo* rotEsq(tNo* raiz, tNo* x) 
{
   tNo* y = x->dir, *aux = x;

    x->dir = y->esq;
    if (y->esq != NULL)
        y->esq->pai = x;

    y->pai = x->pai;    
    if (x->pai == NULL)
        raiz = y;
    else
    {
        if (x == x->pai->dir) {
            x->pai->dir = y;
        }

        else
            x->pai->esq = y;
    }

    y->esq = aux;
    x->pai = y;

    // Atualiza alturas
    x->alt = max(altura(x->esq), altura(x->dir)) + 1;
    y->alt = max(altura(y->esq), altura(y->dir)) + 1;
    raiz->alt = max(altura(raiz->esq), altura(raiz->dir)) + 1;

    //printf("Rotaciona para a esquerda\n");

    return y;
}

// Função que rotaciona a árvore para a direita
tNo* rotDir(tNo* raiz, tNo* x)
{
    tNo* y = x->esq, *aux = x;

    x->esq = y->dir;
    if (y->dir != NULL)
        y->dir->pai = x;

    y->pai = x->pai;    
    if (x->pai == NULL)
        raiz = y;
    else
    {
        if (x == x->pai->esq)
            x->pai->esq = y;

        else
            x->pai->dir = y;
    }

    y->dir = aux;
    x->pai = y;

    // Atualiza alturas
    x->alt = max(altura(x->esq), altura(x->dir)) + 1;
    y->alt = max(altura(y->esq), altura(y->dir)) + 1;
    raiz->alt = max(altura(raiz->esq), altura(raiz->dir)) + 1;

    //printf("Rotaciona para a direita\n");

    return y;
}

int nivelNo(tNo* n)
{
    int nivel = 0;

    if (n->pai == NULL)
        return 0;
        
    else
    {
        // O nivel de um no eh a quantidade de
        // ancestrais que ele tem
        while (n->pai != NULL)
        {
            nivel++;
            n = n->pai;
        }

        return nivel;
    }
}

void printTreeEmOrdem(tNo* n)
{
  if (n != NULL)
    {
        printTreeEmOrdem(n->esq);
        printf("%d,%d\n", n->chave, nivelNo(n));
        printTreeEmOrdem(n->dir);
    }
}

void printTreePreOrdem(tNo* n)
{
   if (n != NULL)
    {
        printf("No : %d, ", n->chave);
        if (n->pai == NULL)
            printf("Pai : NULL\n");
        else
            printf("Pai : %d\n", n->pai->chave);
        printTreePreOrdem(n->esq);
        printTreePreOrdem(n->dir);
    }
}

void printTreePosOrdem(tNo* n)
{
    if (n != NULL)
    {
        printTreePosOrdem(n->esq);
        printTreePosOrdem(n->dir);
        printf("%d", n->chave);
    }
}
