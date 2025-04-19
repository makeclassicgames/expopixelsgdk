#ifndef GAME_H
#define GAME_H

#include <genesis.h>

#include "input.h"
#include "player.h"
#include "level.h"

#define MAX_LEVELS 4

#define DEV_MODE 1

/**
 * Game State Enum
 */
typedef enum {
    //Splash Screen 1
    GAME_STATE_SPLASH1,
    //Splash Screen 2
    GAME_STATE_SPLASH2,
    //Menu
    GAME_STATE_MENU,
    //Game Running
    GAME_STATE_RUN,
    //Game Over
    GAME_STATE_END
} GameState;

/**
 * Game struct Definition
 */
typedef struct game
{
    /** Current State */
    GameState currentState;
    /** Input State */
    Input inputState;

    Player player;
    u16 vram_index;
    u8 levelIndex;
    u8 screenIndex;
}Game;

void loadNextState(Game *, GameState);


void updateSplash1(Game *);
void updateSplash2(Game *);
void updateMenu(Game *);
void updateGameRun(Game*);

//Draw

void drawGameRun(Game *);
#endif // GAME_H