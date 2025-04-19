#ifndef INPUT_H
#define INPUT_H

#include <genesis.h>

typedef struct{
    u8 values[8];
}Input;

enum{
    //UP BUTTON
    INPUT_UP=0,
    //DOWN 
    INPUT_DOWN=1,
    //LEFT
    INPUT_LEFT=2,
    //RIGHT
    INPUT_RIGHT=3,
    //JUMP
    INPUT_JUMP,
    //START
    INPUT_START=7
};

/**
 * Initialize the input Element
 * @param input Input element to initialize
 */
void input_init(Input *);
/**
 * Update the input element this function updates the values of the input element from the directions input
 * @param input Input element to update
 */
void input_update(Input *);
/**
 * Check if a button is pressed
 * @param input Input element to check
 * @param button Button to check
 * @return u8 1 if the button is pressed 0 otherwise
 */
u8 is_button_pressed(Input *, u16);
/**
 * Reset a button
 * @param input Input element to reset
 * @param button Button to reset
 */
void reset_button(Input *, u16);

/**
 * Input Event Handler for use with SGDK.
 */
void inputEventHandler(u16,u16,u16);

#endif // INPUT_H