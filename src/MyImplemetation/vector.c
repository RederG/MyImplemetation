#include <stdlib.h>
#include <string.h>
#include "../../include/MyImplemetation/vector.h"
#include "../../include/tool.h"

const unsigned int VECTOR_SIZE = sizeof(void*) + sizeof(unsigned int) * 2;

typedef struct VectorElement{
    void* data;
} VectorElement;

typedef struct Vector{
    VectorElement* elements;
    unsigned int size;
    unsigned int capacity;
    unsigned int value_size;
} Vector;

Vector* current_vector = nullptr;
unsigned int current_index = 0;
void* current_data;

VectorElement* new_vector_elements(unsigned int size){
    return malloc(sizeof(VectorElement) * size);
}

void Vector_set_elements(VectorElement* new_elements, Vector* vector){
    unsigned int capacity = vector->capacity;
    unsigned int size = vector->size;
    Vector_clear(vector);
    vector->elements = new_elements;
    vector->capacity = capacity;
    vector->size = size;
}

void* Vector_get(unsigned int index, Vector* vector){
    if(index < vector->size)
        return vector->elements[index].data;
    return nullptr;
}

void* Vector_get_top(Vector* vector){
    if(vector->size > 0)
        return vector->elements->data;
    return nullptr;
}

void* Vector_get_last(Vector* vector){
    if(vector->size > 0)
        return vector->elements[vector->size - 1].data;
    return nullptr;
}

unsigned int Vector_get_size(Vector* vector){
    if(vector != nullptr)
        return vector->size;
    return 0;
}

unsigned int Vector_get_capacity(Vector* vector){
    if(vector != nullptr)
        return vector->capacity;
    return 0;
}

void* Vector_get_next(Vector* vector){
    if(vector == nullptr){
        current_vector = nullptr;
        current_index = 0;
        current_data = nullptr;
        return nullptr;
    }
    if(current_vector != vector){
        current_vector = vector;
        current_index = 0;
        current_data = nullptr;
    }
    current_index++;
    if(current_index - 1 < vector->size)
        current_data = vector->elements[current_index - 1].data;
    else{
        current_vector = nullptr;
        current_index = 0;
        current_data = nullptr;
    }
    return current_data;
}

void* Vector_get_current_data(){
    return current_data;
}

unsigned int Vector_get_current_index(){
    if(current_index > 0)
        return current_index - 1;
    else    
        return 0;
}

bool Vector_push(void* data, Vector* vector){
    if(vector->size > vector->capacity)
        return false;
    if((vector->size > 0 || vector->capacity > 0) && vector->elements == nullptr)
        return false;
    if(vector->size == 0 && vector->elements == nullptr){
        vector->size = 1;
        vector->capacity = 2;
        vector->elements = new_vector_elements(2);
        vector->elements[0].data = malloc(vector->value_size);
        memcpy(vector->elements[0].data, data, vector->value_size);
    }
    else if(vector->size > 0){
        if(vector->capacity <= vector->size + 1){

            VectorElement* new_elements = new_vector_elements(vector->capacity * 2);
            size_t i;
            for(i = 0; i < vector->size; i++){
                new_elements[i].data = malloc(vector->value_size);
                memcpy(new_elements[i].data, vector->elements[i].data, vector->value_size);
            }
            
            Vector_set_elements(new_elements, vector);
            vector->capacity *= 2;
        }
        vector->elements[vector->size].data = malloc(vector->value_size);
        memcpy(vector->elements[vector->size].data, data, vector->value_size);
        vector->size += 1;
    }
    return true;
}

bool Vector_insert(unsigned int index, void* data, Vector* vector){
    if(vector->size > vector->capacity)
        return false;
    if((vector->size > 0 || vector->capacity > 0) && vector->elements == nullptr)
        return false;
    if(index >= vector->size && vector->size > 0)
        return false;
    if(vector->size == 0)
        Vector_push(data, vector);
    else if(vector->size > 0){
        if(vector->capacity <= vector->size + 1)
            vector->capacity *= 2;

        VectorElement* new_elements = new_vector_elements(vector->capacity);
        for(int i = 0; i < index; i++){
            new_elements[i].data = malloc(vector->value_size);
            memcpy(new_elements[i].data, vector->elements[i].data, vector->value_size);
        }
        
        VectorElement* element = malloc(sizeof(VectorElement));
        element->data = malloc(vector->value_size);
        memcpy(element->data, data, vector->value_size);
        new_elements[index] = *element;

        for(int i = index + 1; i < vector->size + 1; i++)
            new_elements[i].data = vector->elements[i - 1].data;

        Vector_set_elements(new_elements, vector);
        vector->size += 1;
    }
    return true;
}

bool Vector_set(unsigned int index, void* data, Vector* vector){
    if(index >= vector->size)
        return false;
    memcpy(vector->elements[index].data, data, vector->value_size);
    return true;
}

bool Vector_remove(unsigned int index, Vector* vector){
    if(vector->size == 0 || vector->capacity == 0 || vector->elements == nullptr)
        return false;
    if(index >= vector->size)
        return false;
    if((vector->size - 1) < (vector->capacity/2))
        vector->capacity /= 2;

    VectorElement* new_elements = new_vector_elements(vector->capacity);
    for(int i = 0; i < index; i++){
        new_elements[i].data = malloc(vector->value_size);
        memcpy(new_elements[i].data, vector->elements[i].data, vector->value_size);
    }
    for(int i = index + 1; i < vector->size; i++){
        new_elements[i - 1].data = malloc(vector->value_size);
        memcpy(new_elements[i - 1].data, vector->elements[i].data, vector->value_size);
    }

    Vector_set_elements(new_elements, vector);
    vector->size--;
    if(vector->size == 0)
        vector->capacity = 0;
    return true;
}

bool Vector_remove_last(Vector* vector){
    if(vector->size == 0 || vector->capacity == 0 || vector->elements == nullptr)
        return false;
    if((vector->size - 1) < (vector->capacity/2))
        vector->capacity /= 2;
    
    VectorElement* new_elements = new_vector_elements(vector->capacity);
    for(int i = 0; i < vector->size - 1; i++){
        new_elements[i].data = malloc(vector->value_size);
        memcpy(new_elements[i].data, vector->elements[i].data, vector->value_size);
    }
    
    Vector_set_elements(new_elements, vector);
    vector->size--;
    if(vector->size == 0)
        vector->capacity = 0;
    return true;
}

bool Vector_remove_begin(Vector* vector){
    if(vector->size == 0 || vector->capacity == 0 || vector->elements == nullptr)
        return false;
    if((vector->size - 1) < (vector->capacity/2))
        vector->capacity /= 2;
    unsigned int capacity = 0;
    unsigned int size = 0;
    
    VectorElement* new_elements = new_vector_elements(vector->capacity);
    for(int i = 1; i < vector->size; i++){
        new_elements[i - 1].data = malloc(vector->value_size);
        memcpy(new_elements[i - 1].data, vector->elements[i].data, vector->value_size);
    }

    Vector_set_elements(new_elements, vector);
    vector->size--;
    if(vector->size == 0)
        vector->capacity = 0;
    return true;
}

void Vector_clear(Vector* vector){
    free(vector->elements);
    vector->size = 0;
    vector->capacity = 0;
    vector->elements = nullptr;
}

bool Vector_is_empty(Vector* vector){
    if(vector->size > 0 && vector->capacity > 0)
        return false;
    return true;
}

bool Vector_fill(void* data, unsigned int begin, unsigned int last, Vector* vector){
    if(begin >= vector->size || last > vector->size)
        return false;
    for(int i = begin; i < last; i++)
        memcpy(vector->elements[i].data, data, vector->value_size);
    return true;
}

void Vector_resize(unsigned int new_size, Vector* vector){
    size_t i;
    vector->capacity = 1;
    for(i = 0; i < new_size; i++){
        if(vector->capacity < i + 1)
            vector->capacity *= 2;
    }
    VectorElement* new_elements = new_vector_elements(vector->capacity);
    for(i = 0; i < vector->size; i++){
        if(i < new_size){
            new_elements[i].data = malloc(vector->value_size);
            memcpy(new_elements[i].data, vector->elements[i].data, vector->value_size);
        }
    }
    Vector_set_elements(new_elements, vector);
    vector->size = new_size;
}

bool Vector_copy(Vector* vector, Vector* destination){
    if(vector == destination)
        return false;
    Vector_set_elements(nullptr, destination);
    destination->elements = malloc(sizeof(VectorElement) * vector->capacity);
    for(int i = 0; i < vector->size; i++){
        destination->elements[i].data = malloc(sizeof(vector->value_size));
        memcpy(destination->elements[i].data, vector->elements[i].data, vector->value_size);
    }
    destination->size = vector->size;
    destination->capacity = vector->capacity;
    destination->value_size = vector->value_size;
    return true;
}

char* Vector_get_data_block(Vector* vector){
    char* data_block = malloc(sizeof(char) * vector->size);
    size_t i;
    for(i = 0; i < vector->size; i++)
        data_block[i] = *(char*)(vector->elements[i].data);
    data_block[vector->size] = '\0';
    return data_block;
}

unsigned int* Vector_get_index(void* data, Vector* vector){
    unsigned int* index = nullptr;
    for(int i = 0; i < vector->size; i++){
        if(vector->elements[i].data == data){
            index = malloc(sizeof(unsigned int));
            *index = i;
            break;
        }
    }
    return index;
}

Vector* new_vector(unsigned int value_size){
    Vector* vector = malloc(sizeof(Vector));
    vector->capacity = 0;
    vector->size = 0;
    vector->elements = nullptr;
    vector->value_size = value_size;
    return vector;
}

void delete_vector(Vector* vector){
    Vector_clear(vector);
    free(vector);
}