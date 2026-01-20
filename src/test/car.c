#include "../../include/tool.h"
#include "car.h"

Class* Car = nullptr;
unsigned int CAR_VELOCITY;
unsigned int CAR_ROLL_OUT;
unsigned int CAR_STOP;

void* Car_roll_out(Object* car, va_list* args);
void* Car_stop(Object* car, va_list* args);

Method methods[] = {
    Car_roll_out,
    Car_stop
};

Attribute attribs[] = {
    {&CAR_VELOCITY, public}
};

void Car_constructor(Class* base_class, Object* obj, va_list* args){
    float velocity = va_arg(*args, double);
    Object_set_class(base_class, obj, &Car_constructor);
    Object_set(CAR_VELOCITY, &velocity, obj, (Method)(&Car_constructor));
}

void* Car_roll_out(Object* car, va_list* args){
    float* velocity = malloc(sizeof(float));
    *velocity = 1000.75f;
    Object_set(CAR_VELOCITY, &velocity, car, &Car_roll_out);
    return nullptr;
}

void* Car_stop(Object* car, va_list* args){
    float* velocity = malloc(sizeof(float));
    *velocity = 0.0f;
    Object_set(CAR_VELOCITY, &velocity, car, &Car_stop);
    return nullptr;
}

Class* Car_class(){
    if(Car == nullptr){
        Car = new_class(1, 0, 1, &Car_constructor, nullptr, attribs, methods);
        Class_set_method(0, &CAR_ROLL_OUT, Car);
        Class_set_method(1, &CAR_STOP, Car);
    }
    return Car;
}