#include <stdio.h>
#include "../include/tool.h"
#include "../include/test/vehicle.h"

int main(int argsi, char* argsc){
    Object* car = new_object(VehicleClass());

    double* velocity = nullptr;

    Object_do(VEHICLE_ROLL_OUT, car, 75.4f);
    if(VEHICLE_ROLL_OUT_RETURN_VALUE != nullptr)
        printf((*VEHICLE_ROLL_OUT_RETURN_VALUE == true) ? "Velocity OK\n" : "Velocity too high\n");

    Object_do(VEHICLE_ROLL_OUT, car, 200.04f);
    if(VEHICLE_ROLL_OUT_RETURN_VALUE != nullptr)
        printf((*VEHICLE_ROLL_OUT_RETURN_VALUE == true) ? "Velocity OK\n" : "Velocity too high\n");
        
    velocity = Object_get(VEHICLE_VELOCITY, car, nullptr);

    Class_terminate();
    return 0;
}