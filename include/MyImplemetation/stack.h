#ifndef __STACK_H__
    #define __STACK_H__

    #include "../tool.h"

    typedef struct Stack Stack;
    extern const unsigned int STACK_SIZE;

    Stack* new_stack(unsigned int value_size);
    void delete_stack(Stack* stack);

    void* Stack_get_top(Stack* stack);
    unsigned int Stack_get_size(Stack* stack);
    unsigned int Stack_get_capacity(Stack* stack);
    void Stack_push(void* data, Stack* stack);
    void Stack_pop(Stack* stack);
    void Stack_clear(Stack* stack);
    bool Stack_is_empty(Stack* stack);

#endif