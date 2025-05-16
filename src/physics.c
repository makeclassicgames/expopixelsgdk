#include "physics.h"
#include "level.h"


void ENTITY_setPosition2D(Entity *entity, Vector2D position)
{
    entity->position.x = position.x;
    entity->position.y = position.y;
}

void ENTITY_setVelocity2D(Entity *entity, Vector2D velocity)
{
    entity->velocity.x = velocity.x;
    entity->velocity.y = velocity.y;
}

void ENTITY_update(Entity * entity, s16 deltatime)
{
    // Update the entity's position based on its velocity and the delta time
    entity->position.x += entity->velocity.x * deltatime;
    entity->position.y += entity->velocity.y * deltatime;
}

bool ENTITY_isOnFloor(Entity *entity, u8 levelIndex, u8 screenIndex)
{
    // Check if the entity is on the floor

    Screen *screen = getScreen(levelIndex, screenIndex);
    u16 *collision_map = screen->collision_map;
    s16 x = entity->position.x / 8;
    s16 y = entity->position.y  / 8; // Check the tile below the entity
    return collision_map[(y+4) * 40 + (x+1)] ==14;
}

bool ENTITY_isCeilling(Entity *entity, u8 levelIndex, u8 screenIndex)
{
    // Check if the entity is on the ceiling
    Screen *screen = getScreen(levelIndex, screenIndex);
    u16 *collision_map = screen->collision_map;
    s16 x = entity->position.x / 8;
    s16 y = entity->position.y / 8; // Check the tile above the entity
    if(entity->velocity.x >= 0)
    {
        x+=3;
    }
    return collision_map[((y+1) * 40) + x] ==14;
}