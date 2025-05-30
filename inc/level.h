
#ifndef LEVEL_H
#define LEVEL_H
#include <genesis.h>

#define SCREENS_PER_LEVEL 4

#define COLLISION_TILE 14

typedef struct{
    u16* collision_map;
    const Image* background;
    const Image* foreground;
    struct{
        s16 x;
        s16 y;
    }initial_position;
}Screen;

typedef struct{
    Screen screens[SCREENS_PER_LEVEL];
}Level;



void loadScreen(u16 levelIndex, u16 screenIndex);
Level* getLevel(u16 levelIndex);
Screen * getScreen(u16 levelIndex, u16 screenIndex);


#endif // LEVEL_H