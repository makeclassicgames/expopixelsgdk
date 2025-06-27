#include "enemy.h"
#include "physics.h"



void ENEMY_init(Enemy *enemy, u8 x, u8 y)
{
    enemy->entity.position.x = x;
    enemy->entity.position.y = y;
    enemy->entity.velocity.x = 0;
    enemy->entity.velocity.y = 0;
    enemy->direction = ENEMY_DIR_LEFT;
    enemy->status = 1;
    enemy->entity.enabled = TRUE;
   
}
void ENEMY_setPosition(Enemy *enemy, s16 x, s16 y)
{
    ENTITY_setPosition2D(&enemy->entity, (Vector2D){x, y});
}
void ENEMY_setVelocity(Enemy *enemy, s16 vx, s16 vy)
{
    ENTITY_setVelocity2D(&enemy->entity, (Vector2D){vx, vy});
}
void ENEMY_setSprite(Enemy *enemy, Sprite *sprite)
{
    enemy->sprite = sprite;
}

void ENEMY_update(Enemy *enemy,u8 levelIndex, u8 screenIndex)
{
   
    if(enemy->entity.velocity.y < MAX_VELOCITY)
    {
        enemy->entity.velocity.y += GRAVITY;
    }
    if(enemy->entity.position.y> 240)
    {
        ENEMY_setEnabled(enemy, FALSE);
    }
    if(enemy->entity.position.x < -32 || enemy->entity.position.x > 320)
    {
        ENEMY_setEnabled(enemy, FALSE);
    }
    if(ENTITY_isOnFloor(&enemy->entity, levelIndex, screenIndex))
    {
        enemy->entity.velocity.y = 0;
    }
    if(enemy->direction == ENEMY_DIR_LEFT 
        && !ENTITY_isCeilling(&enemy->entity, levelIndex, screenIndex))
    {
        enemy->entity.velocity.x = -1;
    }
    else if(enemy->direction == ENEMY_DIR_RIGHT 
        && !ENTITY_isCeilling(&enemy->entity, levelIndex, screenIndex))
    {
        enemy->entity.velocity.x = 1;
    }

  /*   if(ENTITY_isOnBorder(&enemy->entity, levelIndex, screenIndex))
    {
        enemy->direction = (enemy->direction == ENEMY_DIR_LEFT) ? ENEMY_DIR_RIGHT : ENEMY_DIR_LEFT;
        enemy->entity.velocity.x = 0;
    } */
  
    ENTITY_update(&enemy->entity, 1);
}

void ENEMY_draw(Enemy *enemy)
{
    SPR_setPosition(enemy->sprite, enemy->entity.position.x, enemy->entity.position.y);
    SPR_setHFlip(enemy->sprite, enemy->direction);
}

void ENEMY_setEnabled(Enemy *enemy, u8 enabled)
{
    enemy->entity.enabled = enabled;
    if (enemy->sprite) {
        SPR_setVisibility(enemy->sprite, enabled ? VISIBLE : HIDDEN);
    }
}