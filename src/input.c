#include "input.h"

void input_init(Input *input)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        input->values[i] = FALSE;
    }
    JOY_setSupport(PORT_1,JOY_SUPPORT_3BTN|JOY_SUPPORT_6BTN);
    JOY_init();
    JOY_setEventHandler(inputEventHandler);
}

u8 is_button_pressed(Input *input, u16 button)
{
    return input->values[button];
}

void reset_button(Input *input, u16 button)
{
    input->values[button] = FALSE;
}

void input_update(Input *input)
{
    u8 i;
    for (i = 0; i < 4; i++)
    {
        input->values[i] = FALSE;
    }
  
    u16 value = JOY_readJoypad(JOY_1);
    if (value & BUTTON_UP)
    {
        input->values[INPUT_UP] = TRUE;
    }
    
    if (value & BUTTON_DOWN)
    {
        input->values[INPUT_DOWN] = TRUE;
    }
    
    if (value & BUTTON_LEFT)
    {
        input->values[INPUT_LEFT] = TRUE;
    }
   
    if (value & BUTTON_RIGHT)
    {
        input->values[INPUT_RIGHT] = TRUE;
    }
    
}