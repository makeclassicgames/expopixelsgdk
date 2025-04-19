#ifndef TIMER_H
#define TIMER_H

#include <genesis.h>

/**
 * Seconds Passed
 */
#define SECONDS_PASSED(startFrame, seconds) ((game.frame - (startFrame)) >= ((SYS_isPAL()) ? (seconds) * 50 : (seconds) * 60))

/**
 * Ticks Per Second
 */
#define TICKS_PER_SECOND ((SYS_isPAL()) ? 50 : 60)

/**
 * Convert Seconds to Ticks
 */
#define SECONDS_TO_TICKS(seconds) seconds*TICKS_PER_SECOND

/**
 * Timer Callback Function
 */
typedef void (timerCallback)(void);

/**
 * Timer Structure
 */
typedef struct{
    //Start Time
    u32 start;
    //Max Elapsed Time
    u32 elapsed;
    // Timer Started Flag
    u8 started;
    // Repeat Timer Flag
    u8 repeat;
    // Callback Function
    timerCallback *callback;
}Timer;

/**
 * Timer Initialization Function
 * 
 * @param timer Timer to Initialize
 * @param max Max Elapsed Time
 * @param repeat Repeat Timer Flag
 * @param callback Callback Function
 */
void timer_init(Timer *, u32, u8, timerCallback *);

/**
 * Timer Start Function
 * 
 * @param timer Timer to Start
 */
void timer_start(Timer *);

/**
 * Timer Stop Function
 * 
 * @param timer Timer to Stop
 */
void timer_stop(Timer *);

/**
 * Timer Update Function
 * 
 * @param timer Timer to Update
 */
void timer_update(Timer *);

/**
 * Timer Pause Function
 * 
 * @param timer Timer to Pause
 */
void timer_pause(Timer *);


#endif // TIMER_H