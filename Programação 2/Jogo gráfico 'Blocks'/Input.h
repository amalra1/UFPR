#ifndef __INPUT__
#define __INPUT__

/*
    Biblioteca desenvolvida para lidar com o Input do
    jogo Blocks
    Pedro Amaral Chapelin
*/

// Funcao que verifica se o botao passado como parametro foi apertado
int mouse_button_down(int button);

// Fase de clique da gameplay -- lida com os cliques do usuario
void handleInput(Tile_t board[ROWS][COLS], int mouseX, int mouseY, int *ms, State_t* states, swapData_t* swapData, Sounds_t* sounds);

#endif