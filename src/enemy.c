#include "enemy.h"



void ENEMY_init(Enemy *enemy, u8 x, u8 y)
{
    enemy->entity.position.x = x;
    enemy->entity.position.y = y;
    enemy->entity.velocity.x = 0;
    enemy->entity.velocity.y = 0;
    enemy->direction = ENEMY_DIR_LEFT;
    enemy->status = 1;
   
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

void ENEMY_update(Enemy *enemy)
{
   
    
    ENTITY_update(&enemy->entity, 1);
}

void ENEMY_draw(Enemy *enemy)
{
    SPR_setPosition(enemy->sprite, enemy->entity.position.x, enemy->entity.position.y);
    SPR_setHFlip(enemy->sprite, enemy->direction);
}