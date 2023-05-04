#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "init.h"
#include "Input.c"
#include "gameplay.h"
#include "swap.h"
#include "timeUpdate.h"

int checkColunarMatches(Tile_t board[ROWS][COLS], int col, int* matchQnt) 
{
    int line;
    int match = 0;

    for (line = 2; line < ROWS; line++)
    {
        if (board[line][col].BlockType != EMPTY)
        {
            // Checa Match de 3 Blocks
            if (board[line][col].BlockType == board[line - 1][col].BlockType && board[line][col].BlockType == board[line - 2][col].BlockType)
            {
                // Verifica se eh o ultimo do match
                if (line == ROWS - 1)
                {
                    board[line][col].MatchLastIndex_L = line;
                    board[line][col].MatchLastIndex_C = col;
                    board[line][col].MatchLast = 1; 
                }

                else if (board[line][col].BlockType != board[line + 1][col].BlockType)
                {
                    board[line][col].MatchLastIndex_L = line;
                    board[line][col].MatchLastIndex_C = col;
                    board[line][col].MatchLast = 1;
                }

                // Verifica se eh o primeiro do match
                if (line - 2 == 0)
                {
                    board[line - 2][col].MatchFirstIndex_L = line - 2;
                    board[line - 2][col].MatchFirstIndex_C = col;
                    board[line - 2][col].MatchFirst = 1;
                }

                else if (board[line - 2][col].BlockType != board[line - 3][col].BlockType)
                {
                    board[line - 2][col].MatchFirstIndex_L = line - 2;
                    board[line - 2][col].MatchFirstIndex_C = col;
                    board[line - 2][col].MatchFirst = 1;
                }

                board[line][col].isMatching = 1;
                board[line - 1][col].isMatching = 1;
                board[line - 2][col].isMatching = 1;

                *matchQnt = *matchQnt + 1;

                match = 1;
            }
        }
    }

    return match;
}

int checkLinearMatches(Tile_t board[ROWS][COLS], int line, int* matchQnt) 
{
    int col;
    int match = 0;

    for (col = 2; col < COLS; col++)
    {
        if (board[line][col].BlockType != EMPTY)
        {
            // Checa Match de 3 Blocks
            if (board[line][col].BlockType == board[line][col - 1].BlockType && board[line][col].BlockType == board[line][col - 2].BlockType)
            {
                // Verifica se eh o ultimo do match
                if (col == COLS - 1)
                {
                    board[line][col].MatchLastIndex_L = line;
                    board[line][col].MatchLastIndex_C = col;
                    board[line][col].MatchLast = 1; 
                }

                else if (board[line][col].BlockType != board[line][col + 1].BlockType)
                {
                    board[line][col].MatchLastIndex_L = line;
                    board[line][col].MatchLastIndex_C = col;
                    board[line][col].MatchLast = 1;
                }

                // Verifica se eh o primeiro do match
                if (col - 2 == 0)
                {
                    board[line][col - 2].MatchFirstIndex_L = line;
                    board[line][col - 2].MatchFirstIndex_C = col - 2;
                    board[line][col - 2].MatchFirst = 1;
                }

                else if (board[line][col - 2].BlockType != board[line][col - 3].BlockType)
                {
                    board[line][col - 2].MatchFirstIndex_L = line;
                    board[line][col - 2].MatchFirstIndex_C = col - 2;
                    board[line][col - 2].MatchFirst = 1;
                }

                board[line][col].isMatching = 1;
                board[line][col - 1].isMatching = 1;
                board[line][col - 2].isMatching = 1;

                *matchQnt = *matchQnt + 1;

                match = 1;
            }
        }
    }

    return match;
}

int checkForMatches(Tile_t board[ROWS][COLS], State_t* states, swapData_t* swapData)
{
    int i = 0;
    int matchQntColunar = 0, matchQntLinear = 0;

    // Checa por matches lineares
    for (i = 0; i < ROWS; i++)
        if (checkLinearMatches(board, i, &matchQntLinear))
            break;

    // Se eu ja achei um linear, nao tem porque procurar colunar
    if (!matchQntLinear)
    {
        for (i = 0; i < COLS; i++)
            if (checkColunarMatches(board, i, &matchQntColunar))
                break;
    }

    // Se achei algum match (linear ou colunar), vai pro UPDATE_MATCHES
    if (matchQntLinear != 0 || matchQntColunar != 0)
    {
        states->gameplayState = UPDATE_MATCHES;
        states->previousGameplayState = CHECK_MATCHES;

        return 1;
    }
    else
    {
        // Se nao achei match, e vim do CHECK_FILL, entao nao tem mais o que fazer
        if (states->previousGameplayState == CHECK_FILL)
            states->gameplayState = IDLE;

        // Se nao vim do CHECK_FILL, entao acabaram
        // os matches e eh hora de verificar as que estao caindo
        else
            states->gameplayState = CHECK_FALL;
          
        states->previousGameplayState = CHECK_MATCHES;
        
        return 0;
    }
}

void updateLinearMatches(Tile_t board[ROWS][COLS], int line, State_t* states, swapData_t* swapData)
{
    int col;
    int FirstFound = 0, SecondFound = 0;

    for (col = 0; col < COLS; col++)
    {
        // Aqui verifica qual eh o matchFirst e o matchLast, para passar para o swap

        if (board[line][col].MatchFirst)
        {
            swapData->FirstROW = line;
            swapData->FirstCOL = col;
            FirstFound = 1;
        }

        else if (board[line][col].MatchLast)
        {
            swapData->SecondROW = line;
            swapData->SecondCOL = col;

            swapData->dif_x = board[swapData->SecondROW][swapData->SecondCOL].pos_x - board[swapData->FirstROW][swapData->FirstCOL].pos_x;
            swapData->dif_y = board[swapData->SecondROW][swapData->SecondCOL].pos_y - board[swapData->FirstROW][swapData->FirstCOL].pos_y;

            // Pegando direcao do movimento
            swapData->dir = RIGHT;

            SecondFound = 1;
        }

        // Se eu ja achei os dois, posso fazer o match 
        if (FirstFound && SecondFound)
        {
            states->gameplayState = SWAP;
            break;
        }
    }
}

void updateColunarMatches(Tile_t board[ROWS][COLS], int col, State_t* states, swapData_t* swapData)
{
    int line;
    int FirstFound = 0, SecondFound = 0;

    for (line = 0; line < ROWS; line++)
    {
        // Verifica qual eh o matchFirst e o matchLast

        if (board[line][col].MatchFirst)
        {
            swapData->FirstROW = line;
            swapData->FirstCOL = col;
            FirstFound = 1;
        }

        else if (board[line][col].MatchLast)
        {
            swapData->SecondROW = line;
            swapData->SecondCOL = col;

            swapData->dif_x = board[swapData->SecondROW][swapData->SecondCOL].pos_x - board[swapData->FirstROW][swapData->FirstCOL].pos_x;
            swapData->dif_y = board[swapData->SecondROW][swapData->SecondCOL].pos_y - board[swapData->FirstROW][swapData->FirstCOL].pos_y;

            // Pegando direcao do movimento
            swapData->dir = DOWN;

            SecondFound = 1;
        }

        // Se ja achou os dois, pronto para o match
        if (FirstFound && SecondFound)
        {
            states->gameplayState = SWAP;
            break;
        }
    }
}

void updateMatchedTiles(Tile_t board[ROWS][COLS], swapData_t* swapData, State_t* states)
{
    int i;

    for (i = 0; i < ROWS; i++)
    {
        if (states->gameplayState != SWAP)
            updateLinearMatches(board, i, states, swapData);
        else
            break;
    }

    if (states->gameplayState != SWAP)
    {
        for (i = 0; i < COLS; i++)
        {
            if (states->gameplayState != SWAP)
                updateColunarMatches(board, i, states, swapData);
            else
                break;
        }
    }

    states->previousGameplayState = UPDATE_MATCHES;
}

int checkFallingTiles(Tile_t board[ROWS][COLS], State_t* states)
{
    int i, j;
    int oneFalling = 0;

    for (i = 0; i < ROWS - 1; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            // Verifica se a Block de baixo eh vazia, sendo esta nao vazia
            if (board[i][j].BlockType != EMPTY && board[i + 1][j].BlockType == EMPTY) 
            {
                board[i][j].isFalling = 1;
                oneFalling = 1;
            }
        }
    }

    states->previousGameplayState = CHECK_FALL;

    if (oneFalling)
    {
        states->gameplayState = UPDATE_FALL;
    }
    else
        states->gameplayState = CHECK_FILL;

    return oneFalling;
}

void updateFallingTiles(Tile_t board[ROWS][COLS], State_t* states, swapData_t* swapData)
{
    int i, j;

    for (i = 0; i < ROWS - 1; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            if (board[i][j].isFalling)
            {
                swapData->FirstCOL = j;
                swapData->FirstROW = i;
                swapData->BlockTypeFirst = board[i][j].BlockType;

                swapData->SecondCOL = j;
                swapData->SecondROW = i + 1;
                swapData->BlockTypeSecond = board[i + 1][j].BlockType; // EMPTY

                swapData->dir = DOWN;
                swapData->dif_x = board[swapData->SecondROW][swapData->SecondCOL].pos_x - board[swapData->FirstROW][swapData->FirstCOL].pos_x;
                swapData->dif_y = board[swapData->SecondROW][swapData->SecondCOL].pos_y - board[swapData->FirstROW][swapData->FirstCOL].pos_y;    
            }
        }
    }

    // Se entrou aqui eh certeza que eh pra cair alguma
    // entao muda para swap depois de tudo feito
    states->gameplayState = SWAP;
    states->previousGameplayState = UPDATE_FALL;
}

int checkEmptyTiles(Tile_t board[ROWS][COLS], State_t* states)
{
    int i, j;
    int oneFill = 0;

    for (i = 0; i < ROWS - 1; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            if (board[i][j].BlockType == EMPTY)
                oneFill = 1;
        }
    }

    states->previousGameplayState = CHECK_FILL;

    // Se chegou ate aqui, eh porque nao tem vazias
    if (oneFill)
        states->gameplayState = UPDATE_FILL;
    else
        states->gameplayState = CHECK_MATCHES;

    return oneFill;
}

void fillEmptyTiles(Tile_t board[ROWS][COLS], State_t* states, swapData_t* swapData)
{
    int i, j;

    for (i = 0; i < ROWS - 1; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            if (board[i][j].BlockType != EMPTY && board[i - 1][j].BlockType == EMPTY)
            {
                // A Block vai cair la de cima
                swapData->FirstROW = 0;
                swapData->FirstCOL = j;
                swapData->BlockTypeFirst = rand() % NUM_BLOCK_TYPES_EASY;
                board[0][j].BlockType = swapData->BlockTypeFirst;

                swapData->SecondROW = i - 1;
                swapData->SecondCOL = j;
                swapData->BlockTypeSecond = board[i - 1][j].BlockType;  // EMPTY;

                swapData->dir = DOWN;

                swapData->dif_y = board[swapData->SecondROW][swapData->SecondCOL].pos_y - board[swapData->FirstROW][swapData->FirstCOL].pos_y;    
            }
        }
    }

    states->previousGameplayState = UPDATE_FILL;
    states->gameplayState = SWAP;
}

void updateGameplay(Tile_t board[ROWS][COLS], int mouseX, int mouseY, int *ms, State_t* states, swapData_t* swapData, Sounds_t* sounds)
{
    // Se não clicou o mouse, apenas atualiza
    if (!mouse_button_down(1) || *ms == MOUSE_NOT_PRESSED)
    {
        if (states->helpState == SHOW_HELP)
            return;

        // Comeca por aqui, quando inicializa vai direto checar matches
        // mas o jogo so comeca de vez depois que as checagens sao feitas
        // e as blocks ajustadas
        if (states->gameplayState == INIT)
            states->gameplayState = CHECK_MATCHES;

        // Fase de troca -- Troca blocks de posicoes
        // de acordo com seu ultmo estado
        if (states->gameplayState == SWAP)
            swapBlocks(board, swapData, states, sounds);
        
        // Fase checa matches
        if (states->gameplayState == CHECK_MATCHES)
            checkForMatches(board, states, swapData);

        // Fase atualiza os matches
        if (states->gameplayState == UPDATE_MATCHES)
            updateMatchedTiles(board, swapData, states);

        // Fase checa se alguma block vai cair
        if (states->gameplayState == CHECK_FALL)
            checkFallingTiles(board, states);
       
        // Fase atualiza as blocks que caem
        if (states->gameplayState == UPDATE_FALL)
            updateFallingTiles(board, states, swapData);

        // Fase checa por espacos vazios restantes
        if (states->gameplayState == CHECK_FILL)
           checkEmptyTiles(board, states);

        // Fase atualiza esses espacos vazios com blocks novas
        if (states->gameplayState == UPDATE_FILL)    
            fillEmptyTiles(board, states, swapData);
        
        // Atualiza tempo
        if (states->helpState != SHOW_HELP)
            updateTime(states, sounds);

        if(mouse_button_down(1))
            *ms = MOUSE_NOT_PRESSED;
        else
            *ms = MOUSE_PRESSED;
        return;
    }

    // Fase de clique -- lida com os cliques do usuario
    else
        handleInput(board, mouseX, mouseY, ms, states, swapData, sounds);
}
