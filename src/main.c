/**
 * Expopisel Game
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>

#include "game.h"
#include "timers.h"

void init(void);
void update(void);
void draw(void);

Game game;


void splash2TimerCallback(void)
{
    PAL_fadeOut(0, 16, 32, TRUE);
    loadNextState(&game, GAME_STATE_MENU);
}

void splash1TimerCallback(void)
{
    PAL_fadeOut(0, 16, 32, TRUE);
    loadNextState(&game, GAME_STATE_SPLASH2);
    
    
}

void enemyTimerCallback(void)
{
    for(int i= 0; i < game.enemiesCount; i++)
    {
        game.enemies[i].direction = !game.enemies[i].direction;
    }
}



int main()
{
    init();
    while (1)
    {
        update();
        draw();
        SPR_update();
        SYS_doVBlankProcess();
    }

    return (0);
}

void init(void)
{
    input_init(&game.inputState);
    SPR_init();
    loadNextState(&game, GAME_STATE_RUN);
    game.vram_index = TILE_USER_INDEX;
    game.levelIndex = 0;
    game.screenIndex = 0;
   

}

void update(void)
{
    input_update(&game.inputState);
    switch (game.currentState)
    {
    case GAME_STATE_SPLASH1:
        // Handle splash screen 1 logic
        updateSplash1(&game);
        break;
    case GAME_STATE_SPLASH2:
        // Handle splash screen 2 logic
        updateSplash2(&game);
        break;
    case GAME_STATE_MENU:
        // Handle menu logic
        if (is_button_pressed(&game.inputState, INPUT_START))
        {
           
            loadNextState(&game, GAME_STATE_RUN);
            game.inputState.values[INPUT_START] = FALSE;
        }
        break;
    case GAME_STATE_RUN:

        //Update sprite position
        updateGameRun(&game);
       
        
     
        break;
    case GAME_STATE_END:
        // Handle game over logic
        if (is_button_pressed(&game.inputState, INPUT_START))
        {
            
            loadNextState(&game, GAME_STATE_SPLASH1);
            game.inputState.values[INPUT_START] = FALSE;
        }
        break;

    default:
        break;
    }
}

void draw(void)
{
    switch (game.currentState)
    {
    case GAME_STATE_SPLASH1:

        break;
    case GAME_STATE_SPLASH2:
        // draw splash screen 2

        break;
    case GAME_STATE_MENU:

        break;
    case GAME_STATE_RUN:
        // draw game screen
            drawGameRun(&game);
        break;
    case GAME_STATE_END:
        // Handle game over logic
        VDP_drawText("END    ", 10, 13);

        break;

    default:
        break;
    }
}

void inputEventHandler(u16 joy, u16 changed, u16 status)
{

    if (joy == JOY_1)
    {
        if (changed & BUTTON_A )
        {
            if(status & BUTTON_A)
            {
                game.inputState.values[INPUT_JUMP] = TRUE;
            }
        
        }
       
        if (changed & BUTTON_B)
        { 
            if(status & BUTTON_B)
            {
                game.inputState.values[INPUT_JUMP] = TRUE;
            }
        }
    

        if (changed & BUTTON_C)
        {
            if(status & BUTTON_C)
            {
                game.inputState.values[INPUT_JUMP] = TRUE;
            }
        }
       

        if (changed & BUTTON_START)
        {
           if(status & BUTTON_START)
           {
               game.inputState.values[INPUT_START] = TRUE;
           }
        }
        
    }
}