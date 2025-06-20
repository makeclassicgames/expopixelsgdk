#include "game.h"
#include "timers.h"

#include "gfx.h"
#include "sprt.h"

Timer splash1timer;
Timer splash2timer;
Timer enemyTimer;

Sprite * fireflySprite;

void splash1TimerCallback(void);
void splash2TimerCallback(void);
void enemyTimerCallback(void);


void initSplash1(Game*);
void initSplash2(Game*);
void initRUN(Game*);
void initMenu(Game*);

void loadEnemies(Game *game);




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
    for(int i = 0; i < 10; i++)
    {
        game->enemies[i].loaded = FALSE;
        game->enemies[i].status = 1;
        game->enemies[i].direction = ENEMY_DIR_LEFT;
    }
    fireflySprite = SPR_addSprite(&firefly, 16, 40, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
    loadEnemies(game);
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
    for(int i= 0; i < game->enemiesCount; i++){
        ENEMY_update(&game->enemies[i], game->levelIndex, game->screenIndex);
    }
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
    for (u8 i = 0; i < game->enemiesCount; i++) {
        ENEMY_draw(&game->enemies[i]);
    }
}


void loadEnemies(Game *game){
    Screen *currentScreen = getScreen(game->levelIndex, game->screenIndex);
    game->enemiesCount = currentScreen->enemiesCount;
    
    for (u8 i = 0; i < game->enemiesCount; i++) {
        ENEMY_init(&game->enemies[i], currentScreen->enemiesPosition[i].x, currentScreen->enemiesPosition[i].y);

        if(game->enemies[i].loaded)
        {
            ENEMY_setPosition(&game->enemies[i],currentScreen->enemiesPosition[i].x, currentScreen->enemiesPosition[i].y); // Skip if already loaded
        }else{
             game->enemies[i].sprite = SPR_addSprite(&esq, currentScreen->enemiesPosition[i].x, currentScreen->enemiesPosition[i].y, 
            TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
        }
       
        PAL_setPalette(PAL3, esq.palette->data, CPU);
        game->enemies[i].loaded = TRUE;    
    }
}
