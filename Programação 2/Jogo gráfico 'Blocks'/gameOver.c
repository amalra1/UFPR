#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "Input.h"
#include "gameOver.h"

void updateGame_Over(int mouseX, int mouseY, int *ms, State_t* states, Sounds_t* sounds)
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

    // Se eu apertei
    else
    {
        // Esta dentro do botao de voltar ao menu
        if (mouseX >= 584 && mouseX <= 699 && mouseY >= 630 && mouseY <= 690)
            states->gameState = MAIN_MENU;

        // Reseta o botao do mouse para evitar repeticoes
        if(mouse_button_down(1))
            *ms = MOUSE_NOT_PRESSED;
        else
            *ms = MOUSE_PRESSED;
    }
}