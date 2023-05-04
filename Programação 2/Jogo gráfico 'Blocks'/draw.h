#ifndef __DRAW__
#define __DRAW__

/*
    Biblioteca desenvolvida para funcoes relacionadas a
    desenhar na tela, sempre depois que atualizada a 
    gameplay
*/

// Desenha o menu na tela
void drawMainMenu(State_t* states, Images_t* images, ALLEGRO_FONT* font);

// Desenha o scoreboard na tela
void drawScoreboard(State_t* states, ALLEGRO_FONT* font, Images_t* images);

// Desenha a tela de game ovver na tela
void drawGameOver(State_t* states, Images_t* images, ALLEGRO_FONT* font); 

// Funcao que realiza a parte de 'output' da logica do game
void draw(State_t* states, Tile_t board[ROWS][COLS], int mouseX, int mouseY, ALLEGRO_FONT* font, Images_t* images);

#endif