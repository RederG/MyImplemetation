#include <stdlib.h>
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
} Vector;

Vector* current_vector = nullptr;
unsigned int current_index = 0;
void* current_data;

VectorElement* new_vector_elements(unsigned int size){
    VectorElement* new_elements = malloc(sizeof(VectorElement)*size);
    size_t i;
    for(i = 0; i < size; i++){
        VectorElement* element = malloc(sizeof(VectorElement));
        element->data = nullptr;
        new_elements[i] = *element;
    }
    return new_elements;
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
        vector->elements = nullptr;

        VectorElement* new_element = malloc(sizeof(VectorElement));
        if(data != nullptr)
            new_element->data = malloc(sizeof(data));
        new_element->data = data;
        vector->elements = new_element;
    }
    else if(vector->size > 0){
        if(vector->capacity <= vector->size + 1){
            vector->capacity *= 2;

            VectorElement* new_elements = new_vector_elements(vector->capacity);
            size_t i;
            for(i = 0; i < vector->size; i++)
                new_elements[i].data = vector->elements[i].data;
            
            vector->elements = new_elements;
        }
        vector->elements[vector->size].data = data;
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
        for(int i = 0; i < index; i++)
            new_elements[i].data = vector->elements[i].data;
        
        VectorElement* element = malloc(sizeof(VectorElement));
        element->data = malloc(sizeof(data));
        element->data = data;
        new_elements[index] = *element;

        for(int i = index + 1; i < vector->size + 1; i++)
            new_elements[i].data = vector->elements[i - 1].data;

        vector->elements = new_elements;
        vector->size += 1;
    }
    return true;
}

bool Vector_set(unsigned int index, void* data, Vector* vector){
    if(index >= vector->size)
        return false;
    vector->elements[index].data = data;
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
    for(int i = 0; i < index; i++)
        new_elements[i].data = vector->elements[i].data;
    for(int i = index + 1; i < vector->size; i++)
        new_elements[i - 1].data = vector->elements[i].data;

    free(vector->elements);
    vector->elements = new_elements;
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
    for(int i = 0; i < vector->size - 1; i++)
        new_elements[i].data = vector->elements[i].data;
    
    unsigned int capacity = vector->capacity;
    unsigned int size = vector->size;
    Vector_clear(vector);
    vector->elements = new_elements;
    vector->capacity = capacity;
    vector->size = size;
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
    
    VectorElement* new_elements = new_vector_elements(vector->capacity);
    for(int i = 1; i < vector->size; i++){
        void* new_data = new_elements[i - 1].data;
        void* data = vector->elements[i].data;
        new_elements[i - 1].data = vector->elements[i].data;
    }
    
    free(vector->elements);
    vector->elements = new_elements;
    vector->size--;
    if(vector->size == 0)
        vector->capacity = 0;
    return true;
}

void Vector_clear(Vector* vector){
    size_t i;
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
        vector->elements[i].data = data;
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
        if(i < new_size)
            new_elements[i].data = vector->elements[i].data;
    }
    free(vector->elements);
    vector->elements = new_elements;
    vector->size = new_size;
}

bool Vector_copy(Vector* vector, Vector* destination){
    if(vector == destination)
        return false;
    free(destination->elements);
    destination->elements = new_vector_elements(vector->capacity);
    for(int i = 0; i < vector->size; i++)
        destination->elements[i].data = vector->elements[i].data;
    destination->size = vector->size;
    destination->capacity = vector->capacity;
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

Vector* new_vector(){
    Vector* vector = malloc(sizeof(Vector));
    vector->capacity = 0;
    vector->size = 0;
    vector->elements = nullptr;
    return vector;
}

void delete_vector(Vector* vector){
    Vector_clear(vector);
    free(vector);
}