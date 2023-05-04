#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "init.h"
#include "gameplay.h"
#include "menu.h"
#include "scoreboard.h"
#include "levelSelect.h"
#include "gameOver.h"
#include "draw.h"

int main()
{  
    Tile_t board[ROWS][COLS];
    State_t* states = malloc(sizeof(State_t));
    swapData_t* swapData = malloc(sizeof(swapData_t));
    Images_t* images = malloc(sizeof(Images_t));
    Sounds_t* sounds = malloc(sizeof(Sounds_t));

    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    ALLEGRO_EVENT event;
    ALLEGRO_MOUSE_STATE ms;

    int msInt = MOUSE_PRESSED;   
    const float FPS = 60.0;
    bool redraw = false;
    int mouse_x, mouse_y;

    // Randomiza a seed
    srand(clock());

    // Inicia a allegro
    must_init(al_init(), "allegro");

    // Inicia a captura das imagens
    must_init(al_init_image_addon(), "images");

    // Inicia a captura dos audios
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codec");
    must_init(al_reserve_samples(16), "canais de audio");

    // Inicia as imagens em si
    images_init(images);

    // Inicia os sons
    sounds_init(sounds);

    // Inicia a captura do teclado
    must_init(al_install_keyboard(), "keyboard");

    // Inicia as fontes TTF
    must_init(al_init_font_addon(), "font addon");
    al_init_ttf_addon();
    al_init_font_addon();

    // Inicia a captura do mouse
    must_init(al_install_mouse(), "mouse");

    // Inicia o timer
    timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");

    // Inicia a queue de eventos
    queue = al_create_event_queue();
    must_init(queue, "queue");

    // Inicia o display
    disp = al_create_display(ScreenWidth, ScreenHeight);
    al_set_window_title(disp, "Blocks");
    must_init(disp, "display");

    // Inicia os primitives
    must_init(al_init_primitives_addon(), "primitives");

    // Inicia as fontes
    font = al_load_font("resources/fonts/PublicPixel.ttf", FONT_SIZE, 0);
    must_init(font, "font");

    // Registra os eventos
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_mouse_event_source());

    // Estado inicial = menu
    states->gameState = MAIN_MENU;
    states->loopState = NOT_DONE;

    al_get_mouse_state(&ms);
    mouse_x = ms.x;
    mouse_y = ms.y;

    al_start_timer(timer);

    // Loop principal do jogo
    while (states->loopState == NOT_DONE) 
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
            // Loop principal, executado 60 vezes por segundo
            case ALLEGRO_EVENT_TIMER:
                switch (states->gameState)
                {       
                case MAIN_MENU:
                    updateMainMenu(states, &msInt, mouse_x, mouse_y);
                    break;
                case LEVEL_SELECT:
                    updateLevelSelect(states, &msInt, mouse_x, mouse_y, board, sounds);
                    break;
                case SCOREBOARD:
                    updateScoreboard(states, &msInt, mouse_x, mouse_y, sounds);
                    break;
                case GAMEPLAY:
                    updateGameplay(board, mouse_x, mouse_y, &msInt, states, swapData, sounds);
                    break;
                case GAME_OVER:
                    updateGame_Over(mouse_x, mouse_y, &msInt, states, sounds);
                    break;
                }

                // So imprime na tela se estiver realmente mudando algo
                redraw = true;
                break;

            // Atualiza as posicoes do mouse 
            case ALLEGRO_EVENT_MOUSE_AXES:
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;              
                break;

            // Se clicar no X, fecha o jogo
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                states->loopState = DONE;
                break;

            // Caso tenha apertado H ou F1 para ajuda
            case ALLEGRO_EVENT_KEY_DOWN:
                // Caso eu ja esteja mostrando a tela de ajuda e tenha teclado um botao
                if (states->helpState == SHOW_HELP)
                {
                    if (event.keyboard.keycode == ALLEGRO_KEY_H || event.keyboard.keycode == ALLEGRO_KEY_F1 || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                        states->helpState = NOT_SHOW_HELP;
                }
                // Caso eu nao esteja mostrando a tela de ajuda e teclei (e não estou inicializando)
                else if (states->initializingState != INITIALIZING && states->helpState == NOT_SHOW_HELP)
                {
                    if (event.keyboard.keycode == ALLEGRO_KEY_H || event.keyboard.keycode == ALLEGRO_KEY_F1)
                        states->helpState = SHOW_HELP;
                }
                break;
        }

        if(redraw) 
        {
            draw(states, board, mouse_x, mouse_y, font, images);
            redraw = false;
        }
    }

    // Destroys
    free(swapData);
    free(states);
    
    destroyImages(images);
    destroySounds(sounds);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}