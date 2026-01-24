#include <stdio.h>
#include "../include/tool.h"
#include "../include/MyImplemetation/vector.h"

int main(int argsi, char* argsc){
    Vector* vector = new_vector(sizeof(unsigned int));
    unsigned int value1 = 1400;
    unsigned int value2 = 140;
    unsigned int value3 = 14;
    unsigned int value4 = 41;
    unsigned int value5 = 410;
    unsigned int value6 = 4100;
    unsigned int value7 = 4114;
    unsigned int value8 = 4141;
    unsigned int value9 = 1414;
    unsigned int value10 = 1441;

    Vector_push(&value1, vector);
    Vector_push(&value2, vector);
    Vector_push(&value3, vector);
    Vector_push(&value5, vector);
    Vector_push(&value6, vector);
    Vector_push(&value7, vector);
    Vector_push(&value8, vector);
    Vector_push(&value9, vector);
    Vector_push(&value10, vector);

    unsigned int* index = nullptr;
    Vector_get_index(&value4, &index, vector);
    if(index != nullptr)
        printf("Value4 is on the %dth case of the vector\n", *index + 1);
    else
        printf("Value4 is not on the vector");

    delete_vector(vector);
    return 0;
}