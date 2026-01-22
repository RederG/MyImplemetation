#include "../../include/test/vehicle.h"

#define CLASS_FILE CLASS_CREATION
#include "../../include/MyImplemetation/class.h"

#include "../../include/tool.h"

Class* Vehicle = nullptr;
unsigned int VEHICLE_VELOCITY;
unsigned int VEHICLE_ROLL_OUT;
bool* VEHICLE_ROLL_OUT_RETURN_VALUE = nullptr;

void Vehicle_constructor(Object* obj, va_list* args){
    double* default_velocity = malloc(sizeof(double));
    *default_velocity = 0.25;
    Object_set(VEHICLE_VELOCITY, default_velocity, obj, (ObjectMethod)Vehicle_constructor, nullptr);
}

void* Vehicle_roll_out(Object* obj, va_list* args){
    Class_create_arg(new_velocity, double, args);
    bool* result = malloc(sizeof(bool));
    if(*new_velocity > 100.0f)
        *result = false;
    else
        *result = true;
    Object_set(VEHICLE_VELOCITY, new_velocity, obj, &Vehicle_roll_out, nullptr);
    return result;
}

ObjectMethodId Vehicle_methods[] = {
    {&VEHICLE_ROLL_OUT, &Vehicle_roll_out}
};

ObjectAttrib Vehicle_attributes[] = {
    {&VEHICLE_VELOCITY, nullptr, public, private, sizeof(double)}
};

ObjectContentNumber Vehicle_content_number = {
    sizeof(Vehicle_methods)/sizeof(ObjectMethodId),
    sizeof(Vehicle_attributes)/sizeof(ObjectAttrib)
};

Class* VehicleClass(){
    if(Vehicle == nullptr)
        Vehicle = Class_create(&Vehicle_constructor, Vehicle_content_number, Vehicle_methods, Vehicle_attributes, nullptr);
    return Vehicle;
}