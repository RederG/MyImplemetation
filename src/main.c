#include <stdio.h>
#include "../include/tool.h"
#include "../src/test/car.h"

int main(int argsi, char* argsc){
    Object* car = new_object(Car_class(), 0.5f);
    Object_do(CAR_ROLL_OUT, car);
    float* velocity = Object_get(CAR_VELOCITY, car, nullptr);
    terminate_classes();
    return 0;
}