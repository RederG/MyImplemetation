#include "../../include/MyImplemetation/stack.h"
#include "../../include/MyImplemetation/map.h"
#include "../../include/MyImplemetation/vector.h"
#include "../../include/tool.h"

typedef struct Vector Vector;
typedef struct Stack{
    unsigned int value_size;
} Stack;

const unsigned int STACK_SIZE = 0;

Map* all_stacks_vector = nullptr;

void verify_stacks_vector(){
    if(all_stacks_vector == nullptr)
        all_stacks_vector = new_map(POINTER_SIZE);
}

Stack* new_stack(unsigned int value_size){
    verify_stacks_vector(nullptr);

    Stack* stack = malloc(sizeof(Stack));
    stack->value_size = value_size;
    unsigned long long* address = malloc(sizeof(unsigned long long));
    *address = Tool_get_address(stack);
    Map_add(address, new_vector(value_size), all_stacks_vector);

    return stack;
}

void delete_stack(Stack* stack){
    verify_stacks_vector();
    unsigned long long address = Tool_get_address(stack);
    if(Map_has(&address, all_stacks_vector)){
        Vector* stack_content = Map_get(&address, all_stacks_vector);
        Map_remove(&address, all_stacks_vector);
    }
}

void* Stack_get_top(Stack* stack){
    verify_stacks_vector();
    unsigned long long address = Tool_get_address(stack);
    return Vector_get_top(Map_get(&address, all_stacks_vector));
}

unsigned int Stack_get_size(Stack* stack){
    verify_stacks_vector();
    unsigned long long address = Tool_get_address(stack);
    return Vector_get_size(Map_get(&address, all_stacks_vector));
}

unsigned int Stack_get_capacity(Stack* stack){
    verify_stacks_vector();
    unsigned long long address = Tool_get_address(stack);
    return Vector_get_capacity(Map_get(&address, all_stacks_vector));
}

void Stack_push(void* data, Stack* stack){
    verify_stacks_vector();
    unsigned long long address = Tool_get_address(stack);
    Vector_insert(0, data, Map_get(&address, all_stacks_vector));
}

void Stack_pop(Stack* stack){
    verify_stacks_vector();
    unsigned long long address = Tool_get_address(stack);
    Vector_remove_begin(Map_get(&address, all_stacks_vector));
}

void Stack_clear(Stack* stack){
    verify_stacks_vector();
    unsigned long long address = Tool_get_address(stack);
    Vector_clear(Map_get(&address, all_stacks_vector));
}

bool Stack_is_empty(Stack* stack){
    verify_stacks_vector();
    unsigned long long address = Tool_get_address(stack);
    return Vector_is_empty(Map_get(&address, all_stacks_vector));
}