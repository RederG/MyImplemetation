#include <stdio.h>
#include "../include/MyImplemetation/map.h"

int main(int argsi, char* argsc){
    Map* map = new_map(POINTER_SIZE, POINTER_SIZE);

    delete_map(map);
    return 0;
}