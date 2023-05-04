#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "Input.h"
#include "init.h"
#include "levelSelect.h"

void updateLevelSelect(State_t* states, int *ms, int mouseX, int mouseY, Tile_t board[ROWS][COLS], Sounds_t* sounds)
{
    // Se nao apertei o mouse
    if (!mouse_button_down(1) || *ms == MOUSE_NOT_PRESSED)
    {
        if(mouse_button_down(1))
            *ms = MOUSE_NOT_PRESSED;
        else
            *ms = MOUSE_PRESSED;
        return;
    }

    // Se apertei
    else
    {
        // Mouse esta dentro do 'easy'
        if (mouseX >= 489 && mouseX <= 789 && mouseY >= 159 && mouseY <= 309) 
        {
            states->gameDifficulty = EASY;

            // Toca musica
            al_play_sample_instance(sounds->SongInstance);

            states->gameState = GAMEPLAY;
            board_init(board, states);
        }

        // Mouse dentro do 'medium'
        else if (mouseX >= 489 && mouseX <= 789 && mouseY >= 323 && mouseY <= 473) 
        {
            states->gameDifficulty = MEDIUM;

            // Toca musica
            al_play_sample_instance(sounds->SongInstance);

            states->gameState = GAMEPLAY;
            board_init(board, states);
        }

        // Mouse dentro do 'hard'
        else if (mouseX >= 489 && mouseX <= 789 && mouseY >= 487 && mouseY <= 637) 
        {
            states->gameDifficulty = HARD;

            // Toca musica
            al_play_sample_instance(sounds->SongInstance);

            states->gameState = GAMEPLAY;
            board_init(board, states);
        }

        // Mouse dentro do botao de voltar
        else if (mouseX >= 20 && mouseX <= 135 && mouseY >= 637 && mouseY <= 697) 
            states->gameState = MAIN_MENU;

        // Reseta o botao do mouse para evitar repeticoes
        if(mouse_button_down(1))
            *ms = MOUSE_NOT_PRESSED;
        else
            *ms = MOUSE_PRESSED;
    }
}