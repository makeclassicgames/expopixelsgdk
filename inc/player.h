
#ifndef PLAYER_H
#define PLAYER_H

#include <genesis.h>
#include "input.h"
#include "physics.h"

typedef enum PlayerDir{
    DIR_DOWN=2,
    DIR_LEFT=3,
    DIR_RIGHT=1,
    DIR_IDLE=4
}Player_Direction;

typedef struct{
    u8 lives;
    u16 score;
    Entity entity;
    Sprite * sprite;
    Player_Direction direction;
} Player;


//function prototypes

void PLYR_init(Player *);
void PLYR_setPosition(Player *player, s16 x, s16 y);
void PLYR_setVelocity(Player *player, s16 vx, s16 vy);
void PLYR_setSprite(Player *player, Sprite *sprite);

void PLYR_updateRun(Player *player, Input *input, u8 levelIndex, u8 screenIndex);
#endif