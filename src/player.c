#include "player.h"

#include "level.h"

bool is_onfloor(Player *player, u8 levelIndex, u8 screenIndex)
{
    u16 x = player->entity.position.x / 8;
    u16 y = player->entity.position.y / 8;

    u16 tile = getScreen(levelIndex,screenIndex)->collision_map[(y+4) * 40 + (x+1)];
    // Check if the player is on the floor
    return tile!=13;
}

bool is_ceilling(Player *player,u8 levelIndex, u8 screenIndex)
{
    u16 x = player->entity.position.x / 8;
    u16 y = player->entity.position.y / 8;
    if(player->direction==DIR_RIGHT){
        x+=2;
    }else if(player->direction==DIR_LEFT){
        x++;
    }
    u16 tile = getScreen(levelIndex,screenIndex)->collision_map[(y+1) * 40 + (x)];
    // Check if the player is ceilling a tile
    return tile!=13;
}

void PLYR_init(Player *player)
{
    player->lives = 3;
    player->score = 0;
    player->entity.position.x = 0;
    player->entity.position.y = 0;
    player->entity.velocity.x = 0;
    player->entity.velocity.y = 0;
    player->direction = DIR_DOWN;
}

void PLYR_setPosition(Player *player, s16 x, s16 y)
{
    ENTITY_setPosition2D(&player->entity, (Vector2D){x, y});

}
void PLYR_setVelocity(Player *player, s16 vx, s16 vy)
{
    ENTITY_setVelocity2D(&player->entity, (Vector2D){vx, vy});
}

void PLYR_setSprite(Player *player, Sprite *sprite)
{
    player->sprite = sprite;
}

void PLYR_updateRun(Player *player, Input *input, u8 levelIndex, u8 screenIndex)
{
    

    
    player->entity.velocity.y += GRAVITY;
    if(is_onfloor(player,levelIndex,screenIndex)){
        player->entity.velocity.y = 0;
    }

    if(is_button_pressed(input, INPUT_JUMP) && is_onfloor(player,levelIndex,screenIndex)){
        player->entity.velocity.y = -JUMP_FORCE;
        reset_button(input, INPUT_JUMP);
    }
    
    if (is_button_pressed(input, INPUT_LEFT))
    {
        player->entity.velocity.x = -1;
        player->direction = DIR_LEFT;
    }
    else if (is_button_pressed(input, INPUT_RIGHT))
    {
        player->entity.velocity.x = 1;
        player->direction = DIR_RIGHT;
    }
    else
    {
        player->entity.velocity.x = 0;
        player->direction = DIR_IDLE;
    }

    if(is_ceilling(player,levelIndex, screenIndex)){
        player->entity.velocity.x = 0;
    }

    ENTITY_update(&player->entity, 1);
}
