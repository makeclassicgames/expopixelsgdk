#ifndef PHYSICS_H
#define PHYSICS_H

#include <genesis.h>

#define JUMP_FORCE 8
#define GRAVITY 1
#define MAX_VELOCITY 8

typedef struct{
    s16 x;
    s16 y;
} Point2D;

typedef struct{
    s16 x;
    s16 y;
} Vector2D;


typedef struct{
    Vector2D position;
    Vector2D velocity;
    u8 enabled;
} Entity;





void ENTITY_setPosition2D(Entity *, Vector2D );
void ENTITY_setVelocity2D(Entity *, Vector2D );
void ENTITY_update(Entity *, s16 );

bool ENTITY_isOnFloor(Entity *, u8 , u8 );
bool ENTITY_isCeilling(Entity *, u8 , u8 );
bool ENTITY_isOnBorder(Entity *entity, u8 levelIndex, u8 screenIndex);

#endif