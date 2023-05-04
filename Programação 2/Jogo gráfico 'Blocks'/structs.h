#ifndef __STRUCTS__
#define __STRUCTS__

// includes necessarios da allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


/*
    Biblioteca definida para definicao de estruturas e 
    algumas constantes a serem utilizadas no programa
    principal
*/

//DISPLAY-----
#define ScreenWidth 1280
#define ScreenHeight 720
//------------

//GAMEPLAY-------
#define BOARD_SCALE 1.7
#define BOARD_WIDTH 400 * BOARD_SCALE
#define BOARD_HEIGHT 400 * BOARD_SCALE
#define TILE_SIZE 40 * BOARD_SCALE
#define BOARD_POS_X 648
#define BOARD_POS_Y 50

#define SWAP_SPEED 6 
#define MATCH_SWAP_SPEED 8
#define FALL_SPEED 22
#define FILL_SPEED 15

#define BLOCK_WIDTH 40 * BOARD_SCALE
#define BLOCK_HEIGHT 40 * BOARD_SCALE
#define ROWS 8
#define COLS 8

#define NUM_BLOCK_TYPES_EASY 6
#define NUM_BLOCK_TYPES_MEDIUM 7
#define NUM_BLOCK_TYPES_HARD 8

#define BLOCK_IMG_WIDTH 15
#define BLOCK_IMG_HEIGHT 14

// mouse
#define MOUSE_PRESSED 1
#define MOUSE_NOT_PRESSED 0

// font
#define FONT_SIZE 25

// music
#define START_TIME 20
#define TIME_INCREMENT_PER_BLOCK 0.7
#define EASY_MUSIC_VOLUME 0.1
//------------

//MENU_OPTIONS
#define PATH_TO_SCOREBOARD "resources/scoreboard.txt"
#define PATH_TO_TEMP "resources/temp.txt"
//------------

typedef enum { MAIN_MENU, LEVEL_SELECT, SCOREBOARD, GAMEPLAY, GAME_OVER } GameState_t;
typedef enum { INIT, IDLE, SELECTING, SWAP, CHECK_MATCHES, UPDATE_MATCHES, CHECK_FALL, UPDATE_FALL, CHECK_FILL, UPDATE_FILL, CHECK_LEVEL_END } GameplayState_t;
typedef enum { NONE, CLICKED_ONCE, CLICKED_TWICE } opt_swap_t;
typedef enum { SHOW_HELP, NOT_SHOW_HELP } HelpState_t;
typedef enum { INITIALIZING, CHANGING_LEVELS, GAME_STARTED } initialization_t;
typedef enum { TIME_INIT, TIME_RUNNING, TIME_STOP } TimeState_t;
typedef enum { EASY, MEDIUM, HARD } difficulty_t;
typedef enum { DONE, NOT_DONE } LoopState_t;
typedef enum { BEATEN, NOT_BEATEN } RecordState_t;

typedef struct state
{
    GameState_t gameState;
    GameplayState_t gameplayState;
    GameplayState_t previousGameplayState;
    opt_swap_t swapState;
    initialization_t initializingState;
    difficulty_t gameDifficulty;
    HelpState_t helpState;
    TimeState_t timeState;
    LoopState_t loopState;
    RecordState_t recordState;

    int score; 
    float time;
} State_t;

typedef enum { AIR, ICE, FIRE, LEAF, WATER, LIGHT, EYE, DIRT, ROACH, SPIRIT, DRAGON, EMPTY } BlockType_t;
typedef struct Tile
{
    BlockType_t BlockType;
    int pos_x;
    int pos_y;
    double mov_x;
    double mov_y;

    int selected;

    int isMatching;
    int MatchFirst;
    int MatchLast;
    int MatchFirstIndex_L;
    int MatchFirstIndex_C;
    int MatchLastIndex_L;
    int MatchLastIndex_C;

    int isFalling;
} Tile_t;

typedef enum { LEFT, RIGHT, UP, DOWN } swapDirection_t;
typedef struct 
{
    BlockType_t BlockTypeFirst;
    int FirstROW;
    int FirstCOL;

    BlockType_t BlockTypeSecond;
    int SecondROW;
    int SecondCOL;
    int BlocksQnt;

    swapDirection_t dir;
    int dif_x;
    int dif_y;
} swapData_t;

typedef struct 
{
    ALLEGRO_BITMAP* MainMenu;
    ALLEGRO_BITMAP* LevelSelect;
    ALLEGRO_BITMAP* scoreboard;
    ALLEGRO_BITMAP* GameOverAboveScore;
    ALLEGRO_BITMAP* GameOverBelowScore;    

    ALLEGRO_BITMAP* GameplayEasy;
    ALLEGRO_BITMAP* HelpEasy;
    ALLEGRO_BITMAP* INITEasy;

    ALLEGRO_BITMAP* GameplayMedium;
    ALLEGRO_BITMAP* HelpMedium;
    ALLEGRO_BITMAP* INITMedium;

    ALLEGRO_BITMAP* GameplayHard;
    ALLEGRO_BITMAP* HelpHard;
    ALLEGRO_BITMAP* INITHard;

    ALLEGRO_BITMAP* jewelsImage;
    ALLEGRO_BITMAP* YellowJewel;
    ALLEGRO_BITMAP* GreenJewel;
    ALLEGRO_BITMAP* BlueJewel;
    ALLEGRO_BITMAP* RedJewel;
    ALLEGRO_BITMAP* PurpleJewel;

    ALLEGRO_BITMAP* airBlock;
    ALLEGRO_BITMAP* dirtBlock;
    ALLEGRO_BITMAP* dragonBlock;
    ALLEGRO_BITMAP* eyeBlock;
    ALLEGRO_BITMAP* fireBlock;
    ALLEGRO_BITMAP* iceBlock;
    ALLEGRO_BITMAP* leafBlock;
    ALLEGRO_BITMAP* lightBlock;
    ALLEGRO_BITMAP* roachBlock;
    ALLEGRO_BITMAP* spiritBlock;
    ALLEGRO_BITMAP* waterBlock;
    
} Images_t;

typedef struct 
{
    ALLEGRO_SAMPLE* swap_fail;
    ALLEGRO_SAMPLE* match;
    ALLEGRO_SAMPLE* Music;
    ALLEGRO_SAMPLE* Zombie;
    ALLEGRO_SAMPLE_INSTANCE* SongInstance;

} Sounds_t;

#endif