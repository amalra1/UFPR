#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "Input.h"
#include "menu.h"

void updateMainMenu(State_t* states, int *ms, int mouseX, int mouseY)
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

    // Se apertei o mouse
    else
    {
        // Se clicou no 'Play Game'
        if (mouseX >= 463 && mouseX <= 817 && mouseY >= 298 && mouseY <= 366) 
            states->gameState = LEVEL_SELECT;

        else if (mouseX >= 463 && mouseX <= 817 && mouseY >= 410 && mouseY <= 478) 
            states->gameState = SCOREBOARD;

        // Se clicou no 'Quit'
        else if (mouseX >= 547 && mouseX <= 733 && mouseY >= 515 && mouseY <= 595) 
            states->loopState = DONE;

        // Reseta o botao do mouse para evitar repeticoes
        if(mouse_button_down(1))
            *ms = MOUSE_NOT_PRESSED;
        else
            *ms = MOUSE_PRESSED;
    }
}