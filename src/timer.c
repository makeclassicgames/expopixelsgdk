#include "timers.h"

void timer_init(Timer *timer, u32 max, u8 repeat, timerCallback *callback)
{
    timer->start = 0;
    timer->elapsed = SECONDS_TO_TICKS(max);
    timer->started = FALSE;
    timer->repeat = repeat;
    timer->callback = callback;
}

void timer_start(Timer *timer)
{
    timer->start = 0;
    timer->started = TRUE;
}

void timer_stop(Timer *timer)
{
    timer->start = 0;
    timer->started = FALSE;
}

void timer_pause(Timer *timer)
{
    timer->started = FALSE;
}

void timer_update(Timer *timer)
{
    if (timer->started)
    {

        timer->start++;
        if (timer->start >= timer->elapsed)
        {
            timer->callback();
            if (timer->repeat)
            {
                timer->start = 0;
            }
            else
            {
                timer->started = FALSE;
            }
        }
    }
}