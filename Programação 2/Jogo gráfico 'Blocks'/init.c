#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "gameplay.h"
#include "init.h"

void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

// Funcao que carrega as sprites dos blocos
void load_blocks(Images_t* images)
{
    images->fireBlock = al_load_bitmap("resources/images/Blocks/fireBlock.png");
    images->iceBlock = al_load_bitmap("resources/images/Blocks/iceBlock.png");
    images->waterBlock = al_load_bitmap("resources/images/Blocks/waterBlock.png");
    images->leafBlock = al_load_bitmap("resources/images/Blocks/leafBlock.png");
    images->airBlock = al_load_bitmap("resources/images/Blocks/airBlock.png");
    images->lightBlock = al_load_bitmap("resources/images/Blocks/lightBlock.png");
    images->eyeBlock = al_load_bitmap("resources/images/Blocks/eyeBlock.png");
    images->dirtBlock = al_load_bitmap("resources/images/Blocks/dirtBlock.png");
    images->roachBlock = al_load_bitmap("resources/images/Blocks/roachBlock.png");
    images->spiritBlock = al_load_bitmap("resources/images/Blocks/spiritBlock.png");
    images->dragonBlock = al_load_bitmap("resources/images/Blocks/dragonBlock.png");
}

// Funcao que carrega os Backgrounds
void load_backgrounds(Images_t* images)
{
    images->MainMenu = al_load_bitmap("resources/images/Backgrounds/main-menu.png");
    must_init(images->MainMenu, "main-menu.png");

    images->LevelSelect = al_load_bitmap("resources/images/Backgrounds/level-select.png");
    must_init(images->LevelSelect, "level-select.png");

    images->scoreboard = al_load_bitmap("resources/images/Backgrounds/scoreboard.png");
    must_init(images->scoreboard, "scoreboard.png");

    images->GameOverAboveScore = al_load_bitmap("resources/images/Backgrounds/GameOverAboveScore.png");
    must_init(images->GameOverAboveScore, "GameOverAboveScore.png");

    images->GameOverBelowScore = al_load_bitmap("resources/images/Backgrounds/GameOverBelowScore.png");
    must_init(images->GameOverBelowScore, "GameOverBelowScore.png");

    images->GameplayEasy = al_load_bitmap("resources/images/Backgrounds/GameplayEasy.png");
    must_init(images->GameplayEasy, "GameplayEasy.png");

    images->HelpEasy = al_load_bitmap("resources/images/Backgrounds/HelpEasy.png");
    must_init(images->HelpEasy, "HelpEasy.png");

    images->INITEasy = al_load_bitmap("resources/images/Backgrounds/INITEasy.png");
    must_init(images->INITEasy, "INITEasy.png");

    images->GameplayMedium = al_load_bitmap("resources/images/Backgrounds/GameplayMedium.png");
    must_init(images->GameplayMedium, "GameplayMedium.png");

    images->HelpMedium = al_load_bitmap("resources/images/Backgrounds/HelpMedium.png");
    must_init(images->HelpMedium, "HelpMedium.png");

    images->INITMedium = al_load_bitmap("resources/images/Backgrounds/INITMedium.png");
    must_init(images->INITMedium, "INITMedium.png");

    images->GameplayHard = al_load_bitmap("resources/images/Backgrounds/GameplayHard.png");
    must_init(images->GameplayHard, "GameplayHard.png");

    images->HelpHard = al_load_bitmap("resources/images/Backgrounds/HelpHard.png");
    must_init(images->HelpHard, "HelpHard.png");

    images->INITHard = al_load_bitmap("resources/images/Backgrounds/INITHard.png");
    must_init(images->INITHard, "INITHard.png");
}

void images_init(Images_t* images)
{
    load_blocks(images);
    load_backgrounds(images);
}

void sounds_init(Sounds_t* sounds)
{
    // Carrega os efeitos de match e fail
    sounds->swap_fail = al_load_sample("resources/sounds/swap-fail.wav");
    must_init(sounds->swap_fail, "swap-fail.wav");

    sounds->match = al_load_sample("resources/sounds/match.ogg");
    must_init(sounds->match, "match.ogg");

    sounds->Zombie = al_load_sample("resources/sounds/Zombie Sound.wav");
    must_init(sounds->Zombie, "Zombie Sound.wav");

    // Carrega a musica de fundo
    sounds->Music = al_load_sample("resources/sounds/urgent.ogg");
    must_init(sounds->Music, "urgent.ogg");

    sounds->SongInstance = al_create_sample_instance(sounds->Music);
    must_init(sounds->SongInstance, "music instance");

    al_set_sample_instance_playmode(sounds->SongInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(sounds->SongInstance, al_get_default_mixer());
    al_set_sample_instance_gain(sounds->SongInstance, 0.1);
}

void board_init(Tile_t board[ROWS][COLS], State_t* states)
{
    int i, j, posx = BOARD_POS_X , posy = BOARD_POS_Y;
    int NumBlockTypes;

    // Seta a qnt de tipos de blocos de acordo com a dificuldade
    if (states->gameDifficulty == EASY)
        NumBlockTypes = NUM_BLOCK_TYPES_EASY;
    else if (states->gameDifficulty == MEDIUM)
        NumBlockTypes = NUM_BLOCK_TYPES_MEDIUM;
    else
        NumBlockTypes = NUM_BLOCK_TYPES_HARD;

    for (i = 0; i < ROWS; i++) 
    {
        for (j = 0; j < COLS; j++) 
        {
            board[i][j].BlockType = rand() % NumBlockTypes;
            board[i][j].pos_x = posx;
            board[i][j].pos_y = posy;
            board[i][j].isMatching = 0;
            board[i][j].isFalling = 0;
            board[i][j].selected = 0;
            board[i][j].mov_x = 0;
            board[i][j].mov_y = 0;
            board[i][j].MatchFirstIndex_L = 0;
            board[i][j].MatchFirstIndex_C = 0;
            board[i][j].MatchLastIndex_L = 0;
            board[i][j].MatchLastIndex_C = 0;
            board[i][j].MatchFirst = 0;
            board[i][j].MatchLast = 0;

            posx += TILE_SIZE + 10; // 'esse 10 eh um vao entre as tiles'
        }

        posy += TILE_SIZE + 10;
        posx = BOARD_POS_X;
    }

    states->gameplayState = INIT;
    states->swapState = NONE;
    states->helpState = NOT_SHOW_HELP;
    states->previousGameplayState = IDLE;
    states->initializingState = INITIALIZING;
    states->time = START_TIME;
    states->timeState = TIME_INIT;
    states->recordState = NOT_BEATEN;

    states->score = 0;
}

void destroyImages(Images_t* images)
{
    al_destroy_bitmap(images->MainMenu);
    al_destroy_bitmap(images->LevelSelect);
    al_destroy_bitmap(images->scoreboard);
    al_destroy_bitmap(images->GameOverAboveScore);
    al_destroy_bitmap(images->GameOverBelowScore);

    al_destroy_bitmap(images->GameplayEasy);
    al_destroy_bitmap(images->INITEasy);
    al_destroy_bitmap(images->HelpEasy);
    al_destroy_bitmap(images->GameplayMedium);
    al_destroy_bitmap(images->INITMedium);
    al_destroy_bitmap(images->HelpMedium);
    al_destroy_bitmap(images->GameplayHard);
    al_destroy_bitmap(images->INITHard);
    al_destroy_bitmap(images->HelpHard);

    al_destroy_bitmap(images->fireBlock);
    al_destroy_bitmap(images->airBlock);
    al_destroy_bitmap(images->waterBlock);
    al_destroy_bitmap(images->iceBlock);
    al_destroy_bitmap(images->leafBlock);
    al_destroy_bitmap(images->lightBlock);
    al_destroy_bitmap(images->eyeBlock);
    al_destroy_bitmap(images->dirtBlock);
    al_destroy_bitmap(images->roachBlock);
    al_destroy_bitmap(images->spiritBlock);
    al_destroy_bitmap(images->dragonBlock);

    free(images);
}

void destroySounds(Sounds_t* sounds)
{
    al_destroy_sample(sounds->swap_fail);
    al_destroy_sample(sounds->match);
    al_destroy_sample(sounds->Music);
    al_destroy_sample(sounds->Zombie);
    al_destroy_sample_instance(sounds->SongInstance);
    free(sounds);
}
