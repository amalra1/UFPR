#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "Input.h"

// Funcao que verifica se o botao passado como parametro foi apertado
int mouse_button_down(int button)
{
    ALLEGRO_MOUSE_STATE ms;

    al_get_mouse_state(&ms);
    return al_mouse_button_down(&ms, button);
}

// Funcao interna que verifica se o ponteiro do mouse esta dentro de uma tile
int DentroDaTile(Tile_t board[ROWS][COLS], int i, int j, int mouseX, int mouseY)
{
    // Fora da Tile, eixo x
    if (mouseX <= board[i][j].pos_x || mouseX >= board[i][j].pos_x + TILE_SIZE)
        return 0;

    // Fora da Tile, eixo y
    if (mouseY <= board[i][j].pos_y || mouseY >= board[i][j].pos_y + TILE_SIZE)
        return 0;

    // Se chegou aqui eh porque o mouse esta dentro de uma tile
    return 1;           
}

// Funcao interna que verifica se a Tile selecionada 
// eh adjacente a primeira
// Retorna 1 se eh e 0 se nao
int TileAdjacente(Tile_t board[ROWS][COLS], int i, int j, int mouseX, int mouseY, swapData_t* swapData)
{
    if (DentroDaTile(board, swapData->FirstROW + 1, swapData->FirstCOL, mouseX, mouseY))
        return 1;
    if (DentroDaTile(board, swapData->FirstROW - 1, swapData->FirstCOL, mouseX, mouseY))
        return 1;
    if (DentroDaTile(board, swapData->FirstROW, swapData->FirstCOL + 1, mouseX, mouseY))
        return 1;
    if (DentroDaTile(board, swapData->FirstROW, swapData->FirstCOL - 1, mouseX, mouseY))
        return 1;

    // Se chegou ate aqui e nao retornou,
    // nao esta em nenhuma adjacente
    return 0;
}

void handleInput(Tile_t board[ROWS][COLS], int mouseX, int mouseY, int *ms, State_t* states, swapData_t* swapData, Sounds_t* sounds)
{
    int i, j;
    
    // Nao podemos considerar cliques que ocorrem enquanto as animacoes estao acontecendo
    if (states->gameplayState != IDLE && states->gameplayState != SELECTING)
        return;

    // Tambem nao podemos considerar cliques enquanto a tela de ajuda esta no game
    if (states->helpState == SHOW_HELP)
        return;

   // Se clicou no 'X', volta pro menu
    if (mouseX >= 23 && mouseX <= 73 && mouseY >= 22 && mouseY <= 50)
    {
        al_stop_sample_instance(sounds->SongInstance);
        states->gameState = MAIN_MENU;
        return;
    }

    // Se clicou no zumbi, ativa o easter egg
    if (mouseX >= 151 && mouseX <= 331 && mouseY >= 405 && mouseY <= 661)
        al_play_sample(sounds->Zombie, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

    states->gameplayState = SELECTING;

    // Se finalmente a inicializacao acabou, podemos comecar as pontuacoes
    if (states->initializingState == INITIALIZING)
    {
        states->initializingState = GAME_STARTED;
        states->score = 0;
        states->timeState = TIME_RUNNING;
        states->time = START_TIME;
    }

    // Se o usuario esta no seu primeiro clique nos blocks
    if (states->swapState == NONE && *ms)
    {
        for (i = 0; i < ROWS; i++)
        {
            for (j = 0; j < COLS; j++)
            {
                if (DentroDaTile(board, i, j, mouseX, mouseY))
                {
                    board[i][j].selected = 1;
                    swapData->BlockTypeFirst = board[i][j].BlockType;
                    swapData->FirstROW = i;
                    swapData->FirstCOL = j;

                    states->swapState = CLICKED_ONCE;
                }
                
                if (states->swapState == CLICKED_ONCE)
                    break;
            }

            if (states->swapState == CLICKED_ONCE)
                break;
        }
    }

    // Se o usuario esta no seu segundo clique nos blocks
    else if (states->swapState == CLICKED_ONCE  && *ms)
    {
        for (i = 0; i < ROWS; i++)
        {
            for (j = 0; j < COLS; j++)
            {
                if (DentroDaTile(board, i, j, mouseX, mouseY))
                {
                    if ((TileAdjacente(board, i, j, mouseX, mouseY, swapData)))
                    {
                        swapData->BlockTypeSecond = board[i][j].BlockType;
                        swapData->SecondROW = i;
                        swapData->SecondCOL = j;

                        swapData->dif_x = board[swapData->SecondROW][swapData->SecondCOL].pos_x - board[swapData->FirstROW][swapData->FirstCOL].pos_x;
                        swapData->dif_y = board[swapData->SecondROW][swapData->SecondCOL].pos_y - board[swapData->FirstROW][swapData->FirstCOL].pos_y;

                        // Pegando direcao do movimento
                        if (swapData->dif_x < 0)
                            swapData->dir = LEFT;
                        else if (swapData->dif_x > 0)
                            swapData->dir = RIGHT;

                        if (swapData->dif_y < 0)
                            swapData->dir = UP;
                        else if (swapData->dif_y > 0)
                            swapData->dir = DOWN;

                        states->swapState = CLICKED_TWICE;
                        states->previousGameplayState = IDLE;
                        states->gameplayState = SWAP;
                    }
                    else
                        states->swapState = NONE;

                    board[swapData->FirstROW][swapData->FirstCOL].selected = 0;
                }
                
                if (states->swapState == CLICKED_TWICE)
                    break;
            }
            if (states->swapState == CLICKED_TWICE)
                break;
        }
    }

    // Reseta o botao do mouse para evitar repeticoes
    if(mouse_button_down(1))
        *ms = MOUSE_NOT_PRESSED;
    else
        *ms = MOUSE_PRESSED;
}
