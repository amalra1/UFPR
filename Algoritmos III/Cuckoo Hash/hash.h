/*
    Essa biblioteca implementa o algoritmo Cuckoo Hash
    Desenvolvido por:
        Davi Garcia Lazzarin
        Pedro Amaral Chapelin        
    Data: 29/01/2023
*/
#ifndef LIB_HASH
#define LIB_HASH
 
//Tamanho das Tabelas
#define M 11 

//Estado dos dados dentro da tabela
typedef enum { VAZIO, DELETADO, OCUPADO } estado_t;

//Estrutura de um "index" da tabela
typedef struct Elemento_TabelaHash{
    int chave;
    estado_t estado;
} Elemento_TabelaHash_t;

//Estrutura do Cuckoo Hash
typedef struct Cuckoo_Hash{
    Elemento_TabelaHash_t* T1;
    Elemento_TabelaHash_t* T2;
} Cuckoo_Hash_t;

//Aloca memória 
Cuckoo_Hash_t* Hash_init();

//limpa a memória alocada
void destroy_Cuckoo_hash(Cuckoo_Hash_t* T);

//Insere a chave nas tabelas
int inserir_hash_aberto(Cuckoo_Hash_t* T, int k);

//Remove a chave das tabelas
int remove_hash(Cuckoo_Hash_t* T, int chave);

//Imprime a saída no padrão solicitado
void imprime_saida(Cuckoo_Hash_t* T);

#endif
