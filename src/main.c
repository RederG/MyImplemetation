#include <stdio.h>
#include "../include/tool.h"
#include "../include/test/car.h"

int main(int argsi, char* argsc){
    Object* vehicle = new_object(Car_class(), 0.25f);

    double* speed = nullptr;
    speed = Object_get(CAR_VELOCITY, speed, vehicle, nullptr);

    Object_do(CAR_SPEED_UP, vehicle);
    speed = Object_get(CAR_VELOCITY, speed, vehicle, nullptr);

    Object_do(CAR_SPEED_UP, vehicle);
    speed = Object_get(CAR_VELOCITY, speed, vehicle, nullptr);

    Object_do(CAR_SPEED_UP, vehicle);
    speed = Object_get(CAR_VELOCITY, speed, vehicle, nullptr);

    Object_do(CAR_SLOW_DOWN, vehicle);
    speed = Object_get(CAR_VELOCITY, speed, vehicle, nullptr);

    Object_do(CAR_SLOW_DOWN, vehicle);
    speed = Object_get(CAR_VELOCITY, speed, vehicle, nullptr);

    return 0;
}