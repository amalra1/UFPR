#ifndef __GAMEPLAY__
#define __GAMEPLAY__

/*
    Biblioteca definida para funcoes relacionadas a gameplay
    do jogo em si
*/

// Funcao que verifica se o botao passado como parametro foi apertado
//int mouse_button_down(int button);

// Funcao que atualiza o menu conforme o usuario quiser
//void updateMainMenu(State_t* states, int *ms, int mouseX, int mouseY);

// Funcao que atualiza a tela de level select
//void updateLevelSelect(State_t* states, int *ms, int mouseX, int mouseY, Tile_t board[ROWS][COLS], Sounds_t* sounds);

// Fase de clique -- lida com os cliques do usuario
//void handleInput(Tile_t board[ROWS][COLS], int mouseX, int mouseY, int *ms, State_t* states, swapData_t* swapData, Sounds_t* sounds);

// Fase checa matches
int checkForMatches(Tile_t board[ROWS][COLS], State_t* states, swapData_t* swapData);

// Fase atualiza os matches
void updateMatchedTiles(Tile_t board[ROWS][COLS], swapData_t* swapData, State_t* states);

// Fase checa se algum block vai cair
int checkFallingTiles(Tile_t board[ROWS][COLS], State_t* states);

// Fase atualiza os blocks que caem
void updateFallingTiles(Tile_t board[ROWS][COLS], State_t* states, swapData_t* swapData);

// Fase checa por espacos vazios restantes
int checkEmptyTiles(Tile_t board[ROWS][COLS], State_t* states);

// Fase atualiza esses espacos vazios com blocks novas
void fillEmptyTiles(Tile_t board[ROWS][COLS], State_t* states, swapData_t* swapData);

// Funcao que atualiza o jogo conforme o que o usuario clicou
void updateGameplay(Tile_t board[ROWS][COLS], int mouseX, int mouseY, int *ms, State_t* states, swapData_t* swapData, Sounds_t* sounds);

// Funcao que atualiza a tela de 'Scoreboard' do menu
void updateScoreboard(State_t* states, int* ms, int mouseX, int mouseY, Sounds_t* sounds);

// Funcao que atualiza a tela de Game over de acordo com a pontuacao obtida
//void updateGame_Over(int mouseX, int mouseY, int *ms, State_t* states, Sounds_t* sounds);
#endif