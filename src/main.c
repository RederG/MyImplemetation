#include <stdio.h>
#include "../include/tool.h"
#include "../include/MyImplemetation/vector.h"

int main(int argsi, char* argsc){
    Vector* vector1 = new_vector(sizeof(unsigned int));
    Vector* vector2 = new_vector(sizeof(unsigned int));
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

    Vector_push(&value1, vector1);
    Vector_push(&value2, vector1);
    Vector_push(&value3, vector1);
    Vector_push(&value4, vector1);
    Vector_push(&value5, vector1);
    Vector_push(&value6, vector1);
    Vector_push(&value7, vector1);
    Vector_push(&value8, vector1);
    Vector_push(&value9, vector1);
    Vector_push(&value10, vector1);

    Vector_copy(vector1, vector2);
    unsigned int* valu5_ptr = Vector_get(4, vector2);

    delete_vector(vector1);
    delete_vector(vector2);
    return 0;
}