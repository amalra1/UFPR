#include <stdio.h>
#include <stdlib.h>

// Uma arvore constitui:
typedef struct no {

    int chave;  // Um valor
    struct no* esq;  // Um ponteiro pro seu filho da esquerda
    struct no* dir;  // Um ponteiro pro seu filho da direita
    struct no* pai;  // E um ponteiro pro seu pai
}tNo;


tNo* cria_nodo(int chave);
tNo* inclui (tNo* no, int chave);
void printTreeEmOrdem(tNo* n);
void printTreePreOrdem(tNo* n);
void printTreePosOrdem(tNo* n);

int main ()
{
    tNo* BinTree = cria_nodo(4);

    // Primeiro criar nodo com a chave raiz
    // Depois fazer as inclusoes

    inclui(BinTree, 6);

    printTreeEmOrdem(BinTree);

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

    return n;
}

// Funcao de inclusao na arvore, passar como parametro inicial o no raiz
tNo* inclui (tNo* no, int chave)
{
    // Se a arvore for vazia, cria um nodo e adiciona a chave
    if (no == NULL)
        return cria_nodo(chave);

    // Se a chave for menor do que a em questao, vai para a esquerda
    if (chave < no->chave)
    {
        no->esq = inclui(no->esq, chave);
        no->esq->pai = no;
    }

    // Se for maior, vai para a direita
    else
    {
        no->dir = inclui(no->dir, chave);
        no->dir->pai = no;
    }

    return no;
}

void printTreeEmOrdem(tNo* n)
{
    if (n == NULL)
        return;

    printTreeEmOrdem(n->esq);
    printf("%d", n->chave);
    printTreeEmOrdem(n->dir);
}

void printTreePreOrdem(tNo* n)
{
    if (n == NULL)
        return;

    printf("%d", n->chave);
    printTreePreOrdem(n->esq);
    printTreePreOrdem(n->dir);
}

void printTreePosOrdem(tNo* n)
{
    if (n == NULL)
        return;

    printTreePosOrdem(n->esq);
    printTreePosOrdem(n->dir);
    printf("%d", n->chave);
}
