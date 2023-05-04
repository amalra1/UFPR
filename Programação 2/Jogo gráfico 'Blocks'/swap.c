#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "swap.h"

// Funcao interna que verifica a possibilidade de uma match linear
int checkMatchLines(Tile_t board[ROWS][COLS], swapData_t* swapData, int linesNUM)
{
    int i;

    // Checa a linha do primeiro escolhido primeiramente, que ja foi para segunda posicao
    for (i = 2; i < COLS; i++)
    {
        if (board[swapData->FirstROW][i].BlockType == board[swapData->FirstROW][i - 1].BlockType && board[swapData->FirstROW][i].BlockType == board[swapData->FirstROW][i - 2].BlockType)
            return 1;
    }
    
    // Se o movimento foi vertical, precisamos checar duas linhas
    if (linesNUM == 2)
    {
        for (i = 2; i < COLS; i++)
        {
            if (board[swapData->SecondROW][i].BlockType == board[swapData->SecondROW][i - 1].BlockType && board[swapData->SecondROW][i].BlockType == board[swapData->SecondROW][i - 2].BlockType)
                return 1;
        }
    }

    // Se chegou ate aqui, eh porque nao encontrou nenhum match, retorna 0
    return 0;
}

// Funcao interna que verifica a possibilidade de uma match colunar
int checkMatchCols(Tile_t board[ROWS][COLS], swapData_t* swapData, int colsNUM)
{
    int i;

    // Checa a coluna do primeiro escolhido primeiramente, que ja foi para segunda posicao
    for (i = 2; i < ROWS; i++)
    {
        if (board[i][swapData->FirstCOL].BlockType == board[i - 1][swapData->FirstCOL].BlockType && board[i][swapData->FirstCOL].BlockType == board[i - 2][swapData->FirstCOL].BlockType)
            return 1;
    }
    
    // Se o movimento foi horizontal, precisamos checar duas colunas
    if (colsNUM == 2)
    {
        for (i = 2; i < ROWS; i++)
        {
            if (board[i][swapData->SecondCOL].BlockType == board[i - 1][swapData->SecondCOL].BlockType && board[i][swapData->SecondCOL].BlockType == board[i - 2][swapData->SecondCOL].BlockType)
            return 1;
        }
    }

    // Se chegou ate aqui, eh porque nao encontrou nenhum match, retorna 0
    return 0;
}

void swapBlocks(Tile_t board[ROWS][COLS], swapData_t* swapData, State_t* states, Sounds_t* sounds)
{
    int i, aux, ReverseMov = 1;

    if (states->previousGameplayState == UPDATE_MATCHES)
    {
        // Atualiza a movimentacao do primeiro block de acordo com a direcao
        if (swapData->dir == RIGHT && board[swapData->FirstROW][swapData->FirstCOL].mov_x < swapData->dif_x)
        {
            board[swapData->FirstROW][swapData->FirstCOL].mov_x += MATCH_SWAP_SPEED;
            board[swapData->SecondROW][swapData->SecondCOL].mov_x -= MATCH_SWAP_SPEED;
        }
        else if (swapData->dir == DOWN && board[swapData->FirstROW][swapData->FirstCOL].mov_y < swapData->dif_y)
        {
            board[swapData->FirstROW][swapData->FirstCOL].mov_y += MATCH_SWAP_SPEED;
            board[swapData->SecondROW][swapData->SecondCOL].mov_y -= MATCH_SWAP_SPEED;
        }

        // Quando ja chegou
        else
        {
            // Toca som
            al_play_sample(sounds->match, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

            if (swapData->dir == RIGHT)
            {
                for (i = swapData->FirstCOL; i < swapData->SecondCOL + 1; i++)
                {
                    board[swapData->FirstROW][i].BlockType = EMPTY;
                    board[swapData->FirstROW][i].isMatching = 0;

                    // Incrementa pontuacoes
                    states->score += 10;
                    states->time += TIME_INCREMENT_PER_BLOCK;
                }
            }
            else
            {
                for (i = swapData->FirstROW; i < swapData->SecondROW + 1; i++)
                {
                    board[i][swapData->FirstCOL].BlockType = EMPTY;
                    board[i][swapData->FirstCOL].isMatching = 0;
                    
                    // Incrementa pontuacoes
                    states->score += 10;
                    states->time += TIME_INCREMENT_PER_BLOCK;
                }
            }

            board[swapData->FirstROW][swapData->FirstCOL].MatchFirstIndex_C = 0;
            board[swapData->FirstROW][swapData->FirstCOL].MatchFirstIndex_L = 0;
            board[swapData->FirstROW][swapData->FirstCOL].MatchFirst = 0;

            board[swapData->SecondROW][swapData->SecondCOL].MatchLastIndex_C = 0;
            board[swapData->SecondROW][swapData->SecondCOL].MatchLastIndex_L = 0;
            board[swapData->SecondROW][swapData->SecondCOL].MatchLast = 0;
            
            // Zera variaveis especificas do movimento
            board[swapData->FirstROW][swapData->FirstCOL].mov_x = 0;
            board[swapData->FirstROW][swapData->FirstCOL].mov_y = 0;

            board[swapData->SecondROW][swapData->SecondCOL].mov_x = 0;
            board[swapData->SecondROW][swapData->SecondCOL].mov_y = 0;

            swapData->dif_x = 0;
            swapData->dif_y = 0;

            swapData->FirstROW = 0;
            swapData->FirstCOL = 0;
            swapData->SecondROW = 0;
            swapData->SecondCOL = 0;

            // Atualiza estados
            states->gameplayState = CHECK_MATCHES;
            states->previousGameplayState = SWAP;
            states->swapState = NONE;
        }
    }

    else if (states->previousGameplayState == IDLE || states->previousGameplayState == SWAP)
    {
        // Atualiza a movimentacao do primeiro block de acordo com a direcao
        if (swapData->dir == RIGHT && board[swapData->FirstROW][swapData->FirstCOL].mov_x < swapData->dif_x)
        {
            board[swapData->FirstROW][swapData->FirstCOL].mov_x += SWAP_SPEED;
            board[swapData->SecondROW][swapData->SecondCOL].mov_x -= SWAP_SPEED;
        }
        else if (swapData->dir == LEFT && board[swapData->FirstROW][swapData->FirstCOL].mov_x > swapData->dif_x)
        {
            board[swapData->FirstROW][swapData->FirstCOL].mov_x -= SWAP_SPEED;
            board[swapData->SecondROW][swapData->SecondCOL].mov_x += SWAP_SPEED;
        }
        else if (swapData->dir == UP && board[swapData->FirstROW][swapData->FirstCOL].mov_y > swapData->dif_y)
        {
            board[swapData->FirstROW][swapData->FirstCOL].mov_y -= SWAP_SPEED;
            board[swapData->SecondROW][swapData->SecondCOL].mov_y += SWAP_SPEED;
        }
        else if (swapData->dir == DOWN && board[swapData->FirstROW][swapData->FirstCOL].mov_y < swapData->dif_y)    
        {
            board[swapData->FirstROW][swapData->FirstCOL].mov_y += SWAP_SPEED;
            board[swapData->SecondROW][swapData->SecondCOL].mov_y -= SWAP_SPEED;
        }

        // Quando ja chegou
        else
        {
            // Quando acaba, troca efetivamente as BlockTypes
            board[swapData->FirstROW][swapData->FirstCOL].BlockType = swapData->BlockTypeSecond;     
            board[swapData->SecondROW][swapData->SecondCOL].BlockType = swapData->BlockTypeFirst;

            // Verifica se possui algum match resultante da troca
            if (swapData->dir == LEFT || swapData->dir == RIGHT)
            {
                if (checkMatchLines(board, swapData, 1) || checkMatchCols(board, swapData, 2))
                    ReverseMov = 0;
            }
            else
            {
                if (ReverseMov)
                {
                    if (checkMatchLines(board, swapData, 2) || checkMatchCols(board, swapData, 1))
                        ReverseMov = 0;
                }
            }

            if (states->previousGameplayState == SWAP)
                ReverseMov = 0;

            if (!ReverseMov)
            {
                // Zera variaveis especificas do movimento
                board[swapData->FirstROW][swapData->FirstCOL].mov_x = 0;
                board[swapData->FirstROW][swapData->FirstCOL].mov_y = 0;

                board[swapData->SecondROW][swapData->SecondCOL].mov_x = 0;
                board[swapData->SecondROW][swapData->SecondCOL].mov_y = 0;

                swapData->dif_x = 0;
                swapData->dif_y = 0;

                // Atualiza estados

                states->swapState = NONE;
                states->gameplayState = CHECK_MATCHES;
                states->previousGameplayState = SWAP;
            }
            else
            {
                // Inverte tudo e chama SWAP novamente

                // Toca som
                al_play_sample(sounds->swap_fail, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                aux = swapData->BlockTypeFirst;
                swapData->BlockTypeFirst = swapData->BlockTypeSecond;
                swapData->BlockTypeSecond = aux;

                board[swapData->FirstROW][swapData->FirstCOL].mov_x = 0;
                board[swapData->SecondROW][swapData->SecondCOL].mov_x = 0;
                board[swapData->FirstROW][swapData->FirstCOL].mov_y = 0;
                board[swapData->SecondROW][swapData->SecondCOL].mov_y = 0;

                swapData->dif_x = board[swapData->SecondROW][swapData->SecondCOL].pos_x - board[swapData->FirstROW][swapData->FirstCOL].pos_x;
                swapData->dif_y = board[swapData->SecondROW][swapData->SecondCOL].pos_y - board[swapData->FirstROW][swapData->FirstCOL].pos_y;

                // Vai pro SWAP de novo
                states->swapState = CLICKED_TWICE;
                states->gameplayState = SWAP;
                states->previousGameplayState = SWAP;
            }       
        }
    } 

    else if (states->previousGameplayState == UPDATE_FALL)
    {
        // Atualiza a movimentacao do primeiro block de acordo com a direcao
        if (swapData->dir == DOWN && board[swapData->FirstROW][swapData->FirstCOL].mov_y < swapData->dif_y)    
            board[swapData->FirstROW][swapData->FirstCOL].mov_y += FALL_SPEED;

        // Quando ja chegou
        else
        {
            // Quando acaba, troca efetivamente as BlockTypes
            board[swapData->FirstROW][swapData->FirstCOL].BlockType = swapData->BlockTypeSecond;     
            board[swapData->SecondROW][swapData->SecondCOL].BlockType = swapData->BlockTypeFirst;

            board[swapData->FirstROW][swapData->FirstCOL].isFalling = 0;

            // Zera variaveis especificas do movimento
            board[swapData->FirstROW][swapData->FirstCOL].mov_x = 0;
            board[swapData->FirstROW][swapData->FirstCOL].mov_y = 0;

            board[swapData->SecondROW][swapData->SecondCOL].mov_x = 0;
            board[swapData->SecondROW][swapData->SecondCOL].mov_y = 0;

            swapData->dif_x = 0;
            swapData->dif_y = 0;

            // Atualiza estados
            states->swapState = NONE;
            states->gameplayState = CHECK_FALL;
            states->previousGameplayState = SWAP;
        }
    }

    else if (states->previousGameplayState == UPDATE_FILL)
    {
        // Atualiza a movimentacao do primeiro block de acordo com a direcao
        if (swapData->dir == DOWN && board[swapData->FirstROW][swapData->FirstCOL].mov_y < swapData->dif_y)
            board[swapData->FirstROW][swapData->FirstCOL].mov_y += FILL_SPEED;

        // Quando ja chegou
        else
        {
            // Quando acaba, troca efetivamente as BlockTypes
            board[swapData->FirstROW][swapData->FirstCOL].BlockType = swapData->BlockTypeSecond;     
            board[swapData->SecondROW][swapData->SecondCOL].BlockType = swapData->BlockTypeFirst;

            // Zera variaveis especificas do movimento
            board[swapData->FirstROW][swapData->FirstCOL].mov_x = 0;
            board[swapData->FirstROW][swapData->FirstCOL].mov_y = 0;

            board[swapData->SecondROW][swapData->SecondCOL].mov_x = 0;
            board[swapData->SecondROW][swapData->SecondCOL].mov_y = 0;

            swapData->dif_x = 0;
            swapData->dif_y = 0;

            // Atualiza estados
            states->swapState = NONE;
            states->gameplayState = CHECK_FILL;
            states->previousGameplayState = SWAP;
        }

    }
}