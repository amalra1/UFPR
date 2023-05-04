#ifndef __INIT__
#define __INIT__

/*
    Biblioteca definida para funcoes relacionadas as 
    inicializacoes, realizadas no inicio do programa
    principal
*/

// Funcao que verifica as inicializacoes
void must_init(bool test, const char *description);

// Funcoes de inicializacao de sons e imagens
void images_init(Images_t* images);
void sounds_init(Sounds_t* sounds);

// Funcoes de desalocacao de memoria de sons e imagens
void destroyImages(Images_t* images);
void destroySounds(Sounds_t* sounds);

// Funcao que inicializa a matriz que contera os blocks
// Cada campo da matriz recebera um numero, indicando
// o tipo do block
void board_init(Tile_t board[ROWS][COLS], State_t* states);

#endif