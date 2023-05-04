#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "Input.h"
#include "scoreboard.h"

void updateScoreboard(State_t* states, int* ms, int mouseX, int mouseY, Sounds_t* sounds)
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
        // Se clicou na flecha para voltar
        if (mouseX >= 18 && mouseX <= 133 && mouseY >= 644 && mouseY <= 704) 
            states->gameState = MAIN_MENU;

         // Reseta o botao do mouse para evitar repeticoes
        if(mouse_button_down(1))
            *ms = MOUSE_NOT_PRESSED;
        else
            *ms = MOUSE_PRESSED;
    }
}