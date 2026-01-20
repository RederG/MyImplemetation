#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/tool.h"
#include "../include/MyImplemetation/map.h"

const unsigned int POINTER_SIZE = sizeof(void*);

Map* all_timer_starts = nullptr;
Map* all_timer_states = nullptr;
Map* all_timer_ends = nullptr;

void Tool_throw_error(char* message){
    printf("[ERROR] : ");
    printf(message);
    printf("\n");
    system("pause");
    exit(EXIT_FAILURE);
}

unsigned long long Tool_get_address(void* pointer){
    return (unsigned long long)pointer;
}

unsigned int Tool_create_id(){
    static unsigned int current_id = 1;
    unsigned int id = Tool_get_address(&current_id);
    id *= current_id++;
    id += id % current_id;
    return id;
}

void Tool_Timer_init(){
    all_timer_ends   = new_map(sizeof(unsigned int));
    all_timer_starts = new_map(sizeof(unsigned int));
    all_timer_states = new_map(sizeof(unsigned int));
}

void Tool_Timer_terminate(){
    delete_map(all_timer_ends);
    delete_map(all_timer_starts);
    delete_map(all_timer_states);
    all_timer_ends   = nullptr;
    all_timer_starts = nullptr;
    all_timer_states = nullptr;
}

bool Tool_Timer_create(unsigned int* id){
    if(!Map_has(id, all_timer_starts)){
        *id = Tool_create_id();

        long long* begin = malloc(sizeof(long long));
        *begin = 0;
        Map_add(id, begin, all_timer_starts);
        Map_add(id, begin, all_timer_ends);

        TimerState* state = (TimerState*)malloc(sizeof(TimerState));
        *state = Stopped;
        Map_add(id, state, all_timer_states);

        return true;
    }
    return false;
}

bool Tool_Timer_start(unsigned int id){
    if(Map_has(&id, all_timer_starts)){
        if(*(TimerState*)Map_get(&id, all_timer_states) != Counting){
            long long* begin = (long long*)malloc(sizeof(long long));
            *begin = time(nullptr);
            Map_set(&id, begin, all_timer_starts);

            TimerState* state = malloc(sizeof(TimerState));
            *state = Counting;
            Map_set(&id, state, all_timer_states);

            return true;
        }
        else
            return false;
    }
    return false;
}

bool Tool_Timer_pause(unsigned int id){
    if(Map_has(&id, all_timer_starts) && *(TimerState*)Map_get(&id, all_timer_states) == Counting){
        TimerState* state = (TimerState*)malloc(sizeof(TimerState));
        *state = Paused;
        Map_set(&id, state, all_timer_states);

        long long* end = (long long*)malloc(sizeof(long long));
        *end = (long long)time(nullptr);
        Map_set(&id, end, all_timer_ends);

        return true;
    }
    return false;
}

bool Tool_Timer_stop(unsigned int id){
    if(Map_has(&id, all_timer_starts) && *(TimerState*)Map_get(&id, all_timer_states) != Stopped){
        TimerState* state = (TimerState*)malloc(sizeof(TimerState));
        *state = Stopped;
        Map_set(&id, state, all_timer_states);

        long long* begin = (long long*)malloc(sizeof(long long));
        *begin = 0;
        Map_set(&id, begin, all_timer_starts);
        
        return true;
    }
    return false;
}

bool Tool_Timer_restart(unsigned int id){
    if(Map_has(&id, all_timer_starts) && Tool_Timer_stop(id) && Tool_Timer_start(id))
        return true;
    return false;
}

bool Tool_Timer_remove(unsigned int id){
    if(Map_has(&id, all_timer_starts)){
        Map_remove(&id, all_timer_starts);
        Map_remove(&id, all_timer_states);
        Map_remove(&id, all_timer_ends);
        return true;
    }
    return false;
}

long long Tool_Timer_get_duration(unsigned int id){
    if(Map_has(&id, all_timer_starts)){
        TimerState* state = Map_get(&id, all_timer_states);
        long long* begin = Map_get(&id, all_timer_starts);

        if(*state == Counting)
            return (long long)time(nullptr) - *begin;
        else if(*state == Stopped)
            return -1.0f;
        else
            return *(long long*)Map_get(&id, all_timer_ends);
    }
    return -1.0f;
}