#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "init.h"
#include "draw.h"

void drawGameOver(State_t* states, Images_t* images, ALLEGRO_FONT* font) 
{
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

    if (states->recordState == BEATEN)
    {
        al_draw_bitmap(images->GameOverAboveScore, 0, 0, 0);
        al_draw_textf(font, white, 620, 480, 0, "%d", states->score);
    }
    else
    {
        al_draw_bitmap(images->GameOverBelowScore, 0, 0, 0);
        al_draw_textf(font, white, 620, 480, 0, "%d", states->score);
    }
}

void drawMainMenu(State_t* states, Images_t* images, ALLEGRO_FONT* font) 
{
    al_draw_bitmap(images->MainMenu, 0, 0, 0);
}

void drawScoreboard(State_t* states, ALLEGRO_FONT* font, Images_t* images)
{
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

    FILE* arq;
    char* line = malloc(sizeof(int) * 16);
    int score;

    arq = fopen(PATH_TO_SCOREBOARD , "r");
    // Testa se o arquivo abre
    if (!arq)
    {
        printf("can not open target file\n");
        exit(1);
    }

    al_draw_bitmap(images->scoreboard, 0, 0, 0);

    // Le valores dos scores guardados e os imprime
    fgets(line, 16, arq);
    score = atoi(line);
    al_draw_textf(font, white, 483, 244, 0, "%d", score);

    fgets(line, 16, arq);
    score = atoi(line);
    al_draw_textf(font, white, 483, 400, 0, "%d", score);

    fgets(line, 16, arq);
    score = atoi(line);
    al_draw_textf(font, white, 483, 547, 0, "%d", score);

    fclose(arq);
    free(line);
}


void drawLevelSelect(State_t* states, Images_t* images, ALLEGRO_FONT* font) 
{
    al_draw_bitmap(images->LevelSelect, 0, 0, 0);
}

void drawBlocks(Tile_t board[ROWS][COLS], Images_t* images)
{
    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
    int i, j;

    for (i = 0; i < ROWS; i++) 
    {
        for (j = 0; j < COLS; j++) 
        {
            if (board[i][j].BlockType == AIR)
            {
                if (!board[i][j].selected)
                    al_draw_scaled_bitmap(images->airBlock, 0, 0, al_get_bitmap_width(images->airBlock), al_get_bitmap_height(images->airBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
                else
                    al_draw_tinted_scaled_bitmap(images->airBlock, black, 0, 0, al_get_bitmap_width(images->airBlock), al_get_bitmap_height(images->airBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
            }
            else if (board[i][j].BlockType == LEAF)
            {
                if (!board[i][j].selected)
                    al_draw_scaled_bitmap(images->leafBlock, 0, 0, al_get_bitmap_width(images->leafBlock), al_get_bitmap_height(images->leafBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
                else
                    al_draw_tinted_scaled_bitmap(images->leafBlock, black, 0, 0, al_get_bitmap_width(images->leafBlock), al_get_bitmap_height(images->leafBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
            }
            else if (board[i][j].BlockType == WATER)
            {
                if (!board[i][j].selected)
                    al_draw_scaled_bitmap(images->waterBlock, 0, 0, al_get_bitmap_width(images->waterBlock), al_get_bitmap_height(images->waterBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
                else
                    al_draw_tinted_scaled_bitmap(images->waterBlock, black, 0, 0, al_get_bitmap_width(images->waterBlock), al_get_bitmap_height(images->waterBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);                
            }
            else if (board[i][j].BlockType == FIRE)
            {
                if (!board[i][j].selected)
                    al_draw_scaled_bitmap(images->fireBlock, 0, 0, al_get_bitmap_width(images->fireBlock), al_get_bitmap_height(images->fireBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
                else
                    al_draw_tinted_scaled_bitmap(images->fireBlock, black, 0, 0, al_get_bitmap_width(images->fireBlock), al_get_bitmap_height(images->fireBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
            }
            else if (board[i][j].BlockType == ICE)
            {
                if (!board[i][j].selected)
                    al_draw_scaled_bitmap(images->iceBlock, 0, 0, al_get_bitmap_width(images->iceBlock), al_get_bitmap_height(images->iceBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
                else
                    al_draw_tinted_scaled_bitmap(images->iceBlock, black, 0, 0, al_get_bitmap_width(images->iceBlock), al_get_bitmap_height(images->iceBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
            }
            else if (board[i][j].BlockType == LIGHT)
            {
                if (!board[i][j].selected)
                    al_draw_scaled_bitmap(images->lightBlock, 0, 0, al_get_bitmap_width(images->lightBlock), al_get_bitmap_height(images->lightBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
                else
                    al_draw_tinted_scaled_bitmap(images->lightBlock, black, 0, 0, al_get_bitmap_width(images->lightBlock), al_get_bitmap_height(images->lightBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
            }
            else if (board[i][j].BlockType == EYE)
            {
                if (!board[i][j].selected)
                    al_draw_scaled_bitmap(images->eyeBlock, 0, 0, al_get_bitmap_width(images->eyeBlock), al_get_bitmap_height(images->eyeBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
                else
                    al_draw_tinted_scaled_bitmap(images->eyeBlock, black, 0, 0, al_get_bitmap_width(images->eyeBlock), al_get_bitmap_height(images->eyeBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
            }
            else if (board[i][j].BlockType == DIRT)
            {
                if (!board[i][j].selected)
                    al_draw_scaled_bitmap(images->dirtBlock, 0, 0, al_get_bitmap_width(images->dirtBlock), al_get_bitmap_height(images->dirtBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
                else
                    al_draw_tinted_scaled_bitmap(images->dirtBlock, black, 0, 0, al_get_bitmap_width(images->dirtBlock), al_get_bitmap_height(images->dirtBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
            }
            else if (board[i][j].BlockType == ROACH)
            {
                if (!board[i][j].selected)
                    al_draw_scaled_bitmap(images->roachBlock, 0, 0, al_get_bitmap_width(images->roachBlock), al_get_bitmap_height(images->roachBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
                else
                    al_draw_tinted_scaled_bitmap(images->roachBlock, black, 0, 0, al_get_bitmap_width(images->roachBlock), al_get_bitmap_height(images->roachBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
            }
            else if (board[i][j].BlockType == SPIRIT)
            {
                if (!board[i][j].selected)
                    al_draw_scaled_bitmap(images->spiritBlock, 0, 0, al_get_bitmap_width(images->spiritBlock), al_get_bitmap_height(images->spiritBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
                else
                    al_draw_tinted_scaled_bitmap(images->spiritBlock, black, 0, 0, al_get_bitmap_width(images->spiritBlock), al_get_bitmap_height(images->spiritBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
            }
            else if (board[i][j].BlockType == DRAGON)
            {
                if (!board[i][j].selected)
                    al_draw_scaled_bitmap(images->dragonBlock, 0, 0, al_get_bitmap_width(images->dragonBlock), al_get_bitmap_height(images->dragonBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
                else
                    al_draw_tinted_scaled_bitmap(images->dragonBlock, black, 0, 0, al_get_bitmap_width(images->dragonBlock), al_get_bitmap_height(images->dragonBlock), board[i][j].pos_x + board[i][j].mov_x, board[i][j].pos_y + board[i][j].mov_y, BLOCK_WIDTH, BLOCK_HEIGHT, 0);
            }
        }
    }

}

void drawGameplay(State_t* states, Tile_t board[ROWS][COLS], int mouseX, int mouseY, ALLEGRO_FONT* font, Images_t* images)
{
    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR green = al_map_rgb(0, 255, 0);

    if (states->gameDifficulty == EASY)
    {
        // Background de inicializacao e ajuda
        if (states->initializingState == INITIALIZING)
            al_draw_bitmap(images->INITEasy, 0, 0, 0);
        else if (states->helpState == SHOW_HELP)
            al_draw_bitmap(images->HelpEasy, 0, 0, 0);

        // Background de gameplay
        else 
            al_draw_bitmap(images->GameplayEasy, 0, 0, 0);
    }
    
    else if (states->gameDifficulty == MEDIUM)
    {
        // Background de inicializacao e ajuda
        if (states->initializingState == INITIALIZING)
            al_draw_bitmap(images->INITMedium, 0, 0, 0);
        else if (states->helpState == SHOW_HELP)
            al_draw_bitmap(images->HelpMedium, 0, 0, 0);

        // Background de gameplay
        else 
            al_draw_bitmap(images->GameplayMedium, 0, 0, 0);
    }

    else if (states->gameDifficulty == HARD)
    {
        // Background de inicializacao e ajuda
        if (states->initializingState == INITIALIZING)
            al_draw_bitmap(images->INITHard, 0, 0, 0);
        else if (states->helpState == SHOW_HELP)
            al_draw_bitmap(images->HelpHard, 0, 0, 0);

        // Background de gameplay
        else 
            al_draw_bitmap(images->GameplayHard, 0, 0, 0);
    }

    if (states->helpState == NOT_SHOW_HELP)
        drawBlocks(board, images);

    // Se esta inicializando, desenha um aviso
    if (states->initializingState == INITIALIZING)
    {
        al_draw_filled_rectangle(640, 5, 1264, 40, black);
        al_draw_text(font, red, 980, 8, ALLEGRO_ALIGN_CENTRE, "Initializing...");

        if (states->gameplayState == IDLE)
        {
            al_draw_filled_rectangle(640, 5, 1264, 40, black);
            al_draw_text(font, green, 970, 8, ALLEGRO_ALIGN_CENTRE, "READY!");
        }
    }

    else
    {
        // Escreve os scores
        al_draw_textf(font, white, 200, 100, 0, "%d", states->score);

        // Desenha o timer
        al_draw_textf(font, red, 447, 130, 0, "%.2lf", states->time);
    }
}

void draw(State_t* states, Tile_t board[ROWS][COLS], int mouseX, int mouseY, ALLEGRO_FONT* font, Images_t* images)
{
    switch (states->gameState) 
    {
        case MAIN_MENU:
            drawMainMenu(states, images, font);
            break;
        case GAMEPLAY:
            drawGameplay(states, board, mouseX, mouseY, font, images);
            break;
        case SCOREBOARD:
            drawScoreboard(states, font, images);
            break;
        case LEVEL_SELECT:
            drawLevelSelect(states, images, font);
            break;
        case GAME_OVER:
            drawGameOver(states, images, font);
            break;
    }
    al_flip_display();
}

