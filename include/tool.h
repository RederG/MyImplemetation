#ifndef __TOOL__
    #define __TOOL__
    
    #define nullptr 0x0

    #include <stdlib.h>
    #include <stdbool.h>

    #define new(x)\
                malloc(sizeof(x));
    
    #define delete(x)\
                free(x);

    typedef enum TimerState{
        Counting, Stopped, Paused
    } TimerState;

    typedef unsigned long long Address;

    extern const unsigned int POINTER_SIZE;

    // Throw an error with the given message
    void Tool_throw_error(char* message);

    // Gets the address stored on the pointer
    unsigned long long Tool_get_address(void* pointer);

    // Creates a new "random" id
    unsigned int Tool_create_id();

    // Inits all utilities for timers
    void Tool_Timer_init();

    // Terminates all utilities for timers
    void Tool_Timer_terminate();

    // Creates a new Timer
    bool Tool_Timer_create(unsigned int* id);

    // Start a Timer
    bool Tool_Timer_start(unsigned int id);

    // Stop a Timer
    bool Tool_Timer_stop(unsigned int id);

    // Pause a Timer
    bool Tool_Timer_pause(unsigned int id);

    // Restart a Timer
    bool Tool_Timer_restart(unsigned int id);

    // Delete a Timer
    bool Tool_Timer_remove(unsigned int id);

    // Gets the duration since the Timer started
    long long Tool_Timer_get_duration(unsigned int id);

#endif