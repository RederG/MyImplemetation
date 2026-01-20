#include "../../include/tool.h"
#include "../../include/test/car.h"

Class* Car = nullptr;
unsigned int CAR_VELOCITY;
unsigned int CAR_ROLL_OUT;
unsigned int CAR_STOP;
unsigned int CAR_SPEED_UP;
unsigned int CAR_SLOW_DOWN;

void* Car_roll_out(Object* car, va_list* args);
void* Car_stop(Object* car, va_list* args);
void* Car_speed_up(Object* car, va_list* args);
void* Car_slow_down(Object* car, va_list* args);

Method methods[] = {
    Car_roll_out,
    Car_stop,
    Car_speed_up,
    Car_slow_down
};

Attribute attribs[] = {
    {&CAR_VELOCITY, public}
};

unsigned int attribs_size[] = {
    sizeof(double)
};

void Car_constructor(Class* base_class, Object* obj, va_list* args){
    arg_value(*args, double, velocity);
    Object_set_class(base_class, obj, &Car_constructor);
    Object_set(CAR_VELOCITY, velocity, obj, (Method)(&Car_constructor));
}

void* Car_roll_out(Object* car, va_list* args){
    float* velocity = malloc(sizeof(float));
    *velocity = 20.0f;
    Object_set(CAR_VELOCITY, velocity, car, &Car_roll_out);
    return nullptr;
}

void* Car_stop(Object* car, va_list* args){
    float* velocity = malloc(sizeof(float));
    *velocity = 0.0f;
    Object_set(CAR_VELOCITY, velocity, car, &Car_roll_out);
    return nullptr;
}

void* Car_speed_up(Object* car, va_list* args){
    double* velocity = nullptr;
    velocity = Object_get(CAR_VELOCITY, velocity, car, &Car_speed_up);
    *velocity *= 2;
    Object_set(CAR_VELOCITY, velocity, car, &Car_speed_up);
    return nullptr;
}

void* Car_slow_down(Object* car, va_list* args){
    double* velocity = nullptr;
    velocity = Object_get(CAR_VELOCITY, velocity, car, &Car_slow_down);
    *velocity /= 2;
    Object_set(CAR_VELOCITY, velocity, car, &Car_slow_down);
    return nullptr;
}

Class* Car_class(){
    if(Car == nullptr){
        Car = new_class(1, 0, 4, &Car_constructor, nullptr, attribs, attribs_size, methods);
        Class_set_method(0, &CAR_ROLL_OUT,  Car);
        Class_set_method(1, &CAR_STOP,      Car);
        Class_set_method(2, &CAR_SPEED_UP,  Car);
        Class_set_method(3, &CAR_SLOW_DOWN, Car);
    }
    return Car;
}