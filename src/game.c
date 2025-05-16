#include "game.h"
#include "timers.h"

#include "gfx.h"
#include "sprt.h"

Timer splash1timer;
Timer splash2timer;
Timer enemyTimer;

void splash1TimerCallback(void);
void splash2TimerCallback(void);
void enemyTimerCallback(void);


void initSplash1(Game*);
void initSplash2(Game*);
void initRUN(Game*);
void initMenu(Game*);





void loadNextState(Game *game, GameState nextState)
{
    game->currentState = nextState;

    switch (nextState)
    {
    case GAME_STATE_SPLASH1:
        /* code */
        initSplash1(game);
        break;
    case GAME_STATE_SPLASH2:
        /* code */
        initSplash2(game);
        break;
    case GAME_STATE_MENU:
        initMenu(game);
        /* code */
        break;
    case GAME_STATE_RUN:
        /* code */
        initRUN(game);
        break;
    case GAME_STATE_END:
        /* code */
        break;
    default:
        break;
    }
}

void initSplash1(Game *game)
{
    //TODO: Implement Splash 1 Initialization
    PAL_fadeIn(0,15, logoBg.palette->data, 30, TRUE);
    VDP_drawImageEx(BG_A,&logoBg, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, game->vram_index), 0, 0, FALSE, FALSE);
    timer_init(&splash1timer, 2, FALSE, splash1TimerCallback);
    timer_start(&splash1timer);
}

void initSplash2(Game * game){
    PAL_fadeIn(0, 15, logArc.palette->data, 30, TRUE);
    VDP_drawImageEx(BG_A,&logArc, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, game->vram_index), 0, 0, FALSE, FALSE);
    timer_init(&splash2timer, 2, FALSE, splash2TimerCallback);
    timer_start(&splash2timer);
}

void initRUN(Game * game){
    
    PLYR_init(&game->player);
    
    loadScreen(game->levelIndex, game->screenIndex);
    Screen * currentScreen = getScreen(game->levelIndex, game->screenIndex);
    PLYR_setPosition(&game->player, currentScreen->initial_position.x, currentScreen->initial_position.y);
    PLYR_setSprite(&game->player,
        SPR_addSprite(&joaq, 400, 100, 
         TILE_ATTR(PAL1, TRUE, FALSE, FALSE)));
    PAL_setPalette(PAL1, joaq.palette->data,CPU);
    ENEMY_init(&game->enemy,150, 100);
    game->enemy.sprite = SPR_addSprite(&esq, 150, 100, 
         TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
    PAL_setPalette(PAL3, esq.palette->data,CPU);
    timer_init(&enemyTimer, 2, TRUE, enemyTimerCallback);
    timer_start(&enemyTimer);
}

void initMenu(Game* game){

    PAL_fadeIn(0, 15, menu.palette->data, 30, TRUE);
    VDP_drawImageEx(BG_A,&menu, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, game->vram_index), 0, 0, FALSE, FALSE);

}

void updateGameRun(Game* game){
    PLYR_updateRun(&game->player, &game->inputState,game->levelIndex, game->screenIndex);
    ENEMY_update(&game->enemy, game->levelIndex, game->screenIndex);
    timer_update(&enemyTimer);
}

void updateSplash1(Game* game){
    timer_update(&splash1timer);
}

void updateSplash2(Game* game){
    timer_update(&splash2timer);
}

void drawGameRun(Game * game){
    SPR_setPosition(game->player.sprite, game->player.entity.position.x, game->player.entity.position.y);
    SPR_setAnim(game->player.sprite, game->player.direction);
    ENEMY_draw(&game->enemy);
}

