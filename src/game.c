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

void loadNextGame(Game  *game);
void loadPreviousGame(Game *game);

void loadEnemies(Game *game);

void showHUD(Game *game);




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

    if(game->player.entity.position.x>290){
        loadNextGame(game);
    }

    if(game->screenIndex!=0 && game->player.entity.position.x < 8)
    {
        loadPreviousGame(game);
    }
}

void loadNextGame(Game  *game){
    PAL_fadeOut(32, 47, 16, FALSE);
    game->screenIndex++;
    if(game->screenIndex >= 5)
    {
        game->screenIndex = 0;
        game->levelIndex++;
        if(game->levelIndex >= MAX_LEVELS)
        {
            game->levelIndex = 0;
        }
    }
    loadScreen(game->levelIndex, game->screenIndex);
    Screen * currentScreen = getScreen(game->levelIndex, game->screenIndex);
    PLYR_setPosition(&game->player, currentScreen->initial_position.x, currentScreen->initial_position.y);
    loadEnemies(game);
}

void loadPreviousGame(Game  *game){
    PAL_fadeOut(32, 47, 16, FALSE);
    game->screenIndex--;
    if(game->levelIndex != 0)
    {
       
        game->levelIndex--;
      
    }
    loadScreen(game->levelIndex, game->screenIndex);
    Screen * currentScreen = getScreen(game->levelIndex, game->screenIndex);
    PLYR_setPosition(&game->player, currentScreen->initial_position.x, currentScreen->initial_position.y);
    loadEnemies(game);
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
    showHUD(game);
}


void loadEnemies(Game *game){
    Screen *currentScreen = getScreen(game->levelIndex, game->screenIndex);
    game->enemiesCount = currentScreen->enemiesCount;
    
    for (u8 i = 0; i < game->enemiesCount; i++) {
        ENEMY_init(&game->enemies[i], currentScreen->enemiesPosition[i].x, currentScreen->enemiesPosition[i].y);

        if(game->enemies[i].loaded)
        {
            ENEMY_setEnabled(&game->enemies[i], TRUE);
            ENEMY_setPosition(&game->enemies[i],currentScreen->enemiesPosition[i].x, currentScreen->enemiesPosition[i].y); // Skip if already loaded
        }else{
             game->enemies[i].sprite = SPR_addSprite(&esq, currentScreen->enemiesPosition[i].x, currentScreen->enemiesPosition[i].y, 
            TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
        }
       
        PAL_setPalette(PAL3, esq.palette->data, CPU);
        game->enemies[i].loaded = TRUE;    
    }
}


void showHUD(Game *game){
    //VDP_drawTextBG(BG_A,"Score: 000000", 2,1);
    VDP_drawTextEx(BG_A,"Score: 000000", TILE_ATTR(PAL2, FALSE, FALSE, FALSE), 2, 1, CPU);
    char buffer[3];
    sprintf(buffer, "Lives: %d", game->player.lives);
    VDP_drawTextEx(BG_A,buffer, TILE_ATTR(PAL2, FALSE, FALSE, FALSE), 2,3,CPU);
    VDP_drawTextEx(BG_A,"World", TILE_ATTR(PAL2, FALSE, FALSE, FALSE), 20,1,CPU);

    char bufferWorld[20];
    sprintf(bufferWorld, "%d-%d", game->levelIndex + 1, game->screenIndex + 1);
    VDP_drawTextEx(BG_A,bufferWorld, TILE_ATTR(PAL2, FALSE, FALSE, FALSE), 21,3,CPU);
}