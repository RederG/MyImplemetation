#include <stdio.h>
#include "../include/tool.h"
#include "../include/test/vehicle.h"

int main(int argsi, char* argsc){
    Object* car0 = new_object(VehicleClass());
    Object* car1 = new_object(VehicleClass());
    Object* car2 = new_object(VehicleClass());
    Object* car3 = new_object(VehicleClass());

    double* velocity = nullptr;

    Object_do(VEHICLE_ROLL_OUT, car0, nullptr, (void**)(&VEHICLE_ROLL_OUT_RETURN_VALUE), 102.4f);
    velocity = Object_get(VEHICLE_VELOCITY, car0, nullptr, nullptr);
    Class_terminate();
    return 0;
}