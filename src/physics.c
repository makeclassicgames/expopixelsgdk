#include "physics.h"


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
