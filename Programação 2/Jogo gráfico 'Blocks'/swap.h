#ifndef __SWAP__
#define __SWAP__

/*
    Biblioteca desenvolvida para a funcao 'swap' do jogo 
    'Blocks', desenvolvido por
    Pedro Amaral Chapelin
*/

// Fase de troca da Gameplay, tem variacoes dependendo do ultimo GameplayState
void swapBlocks(Tile_t board[ROWS][COLS], swapData_t* swapData, State_t* states, Sounds_t* sounds);

#endif