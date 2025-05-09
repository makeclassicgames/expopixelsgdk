#ifndef ENEMY_H
#define ENEMY_H
#include <genesis.h>

#include "sprt.h"

#include "physics.h"
#include "timers.h"

typedef struct{
    Entity entity;
    Sprite * sprite;
    u8 direction;
    u8 status;
}Enemy;

enum ENEMY_DIR{
    ENEMY_DIR_LEFT=1,
    ENEMY_DIR_RIGHT=0
};

void ENEMY_init(Enemy *, u8 , u8 );
void ENEMY_setPosition(Enemy *enemy, s16 x, s16 y);
void ENEMY_setVelocity(Enemy *enemy, s16 vx, s16 vy);
void ENEMY_setSprite(Enemy *enemy, Sprite *sprite);
void ENEMY_update(Enemy *enemy);
void ENEMY_draw(Enemy *enemy);

#endif