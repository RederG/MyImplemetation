#include "../../include/MyImplemetation/class.h" // including all class bases

#define CLASS_FILE CLASS_CREATION
#include "../../include/MyImplemetation/class.h" // including all needed for creating a new class

#include <string.h>
#include "../../include/tool.h"
#include "../../include/MyImplemetation/vector.h"

typedef struct Class{
    ObjectConstructor constructor;
    ObjectMethodId* methods;
    ObjectAttrib* default_attrib;
    ObjectContentNumber content_number;
    Class* parent_class;
    unsigned int parent_class_number;
} Class;

typedef struct Object{
    Class* base_class;
    ObjectAttrib* attribs;
} Object;

Vector* all_classes;
Vector* all_objects;

void Class_init(){
    if(all_classes == nullptr)
        all_classes = new_vector(sizeof(Class));
    if(all_objects == nullptr)
        all_objects = new_vector(sizeof(Object));
}

void Class_terminate(){
    Vector_get_next(nullptr);
    while(Vector_get_next(all_objects)){
        delete_object(Vector_get_current_data());
        Vector_get_next(nullptr);
    }
    while(Vector_get_next(all_classes)){
        delete_class(Vector_get_current_data());
        Vector_get_next(nullptr);
    }
    all_classes = nullptr;
    all_objects = nullptr;
}

ObjectMethodId* Class_get_method(unsigned int id, Class* base_class){
    size_t i;
    for(i = 0; base_class != nullptr && i < base_class->content_number.methods_number; i++){
        if(*base_class->methods[i].id == id)
            return &base_class->methods[i];
    }
    return nullptr;
}

ObjectAttrib* Object_get_attrib(unsigned int id, Object* obj){
    size_t i;
    for(i = 0; i < obj->base_class->content_number.attribs_number; i++){
        if(*obj->attribs[i].id == id)
            return &obj->attribs[i];
    }
}

void set_methods_id(ObjectMethodId* new_methods, unsigned int new_methods_number){
    size_t i;
    for(i = 0; i < new_methods_number; i++)
        (*new_methods->id) = (Address)(&*new_methods->id);
}

void set_attrib_id(ObjectAttrib* new_attribs, unsigned int new_attribs_number){
    size_t i;
    for(i = 0; i < new_attribs_number; i++)
        (*new_attribs->id) = (Address)(&*new_attribs->id);
}

bool Class_has_method(ObjectMethod method, Class* base_class){
    size_t i;
    for(i = 0; method != nullptr && base_class != nullptr && i < base_class->content_number.methods_number; i++){
        if((ObjectConstructor)method == base_class->constructor)
            return true;
        if(base_class->methods[i].method == method)
            return true;
    }
    return false;
}

void Class_set_parent_class(Class* base_class, Class* parent_class){
    base_class->parent_class_number = 0;
    base_class->parent_class = parent_class;
    Class* current_class = parent_class;
    while(current_class != nullptr){
        current_class = current_class->parent_class;
        base_class->parent_class_number++;
    }
}

void Class_set_up_attribs(Class* base_class, ObjectAttrib* new_attribs, unsigned int new_attribs_number){
    Class* current_class = base_class->parent_class;
    size_t i;
    unsigned int current_index = new_attribs_number;
    base_class->content_number.attribs_number = new_attribs_number;

    while(current_class != nullptr){
        base_class->content_number.attribs_number += current_class->content_number.attribs_number;
        current_class = current_class->parent_class;
    }
    base_class->default_attrib = calloc(base_class->content_number.attribs_number, sizeof(ObjectAttrib));
    current_class = base_class;

    while(current_class != nullptr){
        if(current_class == base_class){
            for(i = 0; i < new_attribs_number; i++)
                base_class->default_attrib[i] = new_attribs[i];
            current_class = base_class->parent_class;
            continue;
        }
        for(; i < i + current_class->content_number.attribs_number; i++)
            memcpy(&base_class->default_attrib[i], &current_class->default_attrib[i - current_class->content_number.attribs_number], sizeof(ObjectAttrib));
        current_class = current_class->parent_class;
    }
}

void Class_set_up_methods(Class* base_class, ObjectMethodId* new_methods, unsigned int new_methods_number){
    Class* current_class = base_class->parent_class;
    size_t i;
    base_class->content_number.methods_number = new_methods_number;

    while(current_class != nullptr){
        base_class->content_number.methods_number += current_class->content_number.methods_number;
        current_class = current_class->parent_class;
    }
    base_class->methods = calloc(base_class->content_number.methods_number, sizeof(ObjectMethodId));
    current_class = base_class;

    while(current_class != nullptr){
        if(current_class == base_class){
            for(i = 0; i < new_methods_number; i++)
                base_class->methods[i] = new_methods[i];
            current_class = base_class->parent_class;
            continue;
        }
        for(; i < i + current_class->content_number.methods_number; i++)
            memcpy(&base_class->methods[i], &current_class->methods[i - current_class->content_number.methods_number], sizeof(ObjectMethodId));
        current_class = current_class->parent_class;
    }
}

void Object_set_class(Class* base_class, Object* obj){
    obj->attribs = malloc(sizeof(ObjectAttrib) * base_class->content_number.attribs_number);
    memcpy(obj->attribs, base_class->default_attrib, sizeof(ObjectAttrib) * base_class->content_number.attribs_number);
    obj->base_class = base_class;
}

Object* new_object(Class* base_class, ...){
    Object* new_obj = nullptr;
    if(base_class != nullptr){
        new_obj = malloc(sizeof(Object));
        Object_set_class(base_class, new_obj);
        
        va_list args;
        va_start(args, base_class);
        base_class->constructor(new_obj, &args);
        va_end(args);

        Vector_push(new_obj, all_objects);
    }
    return new_obj;
}

void delete_object(Object* obj){
    if(obj != nullptr){
        int i;
        for(i = obj->base_class->content_number.attribs_number - 1; i >= 0; i--)
            free(&obj->attribs[i]);
        obj->base_class = nullptr;
        obj->attribs = nullptr;
        unsigned int* index = nullptr;
        Vector_get_index(obj, &index, all_objects);
        if(index != nullptr)
            Vector_remove(*index, all_objects);
    }
}

void* Object_get(unsigned int attrib_id, Object* obj, ObjectMethod context){
    ObjectAttrib* attrib = Object_get_attrib(attrib_id, obj);
    if(attrib != nullptr && 
        (attrib->getting_access == public || 
            (attrib->getting_access == private && Class_has_method(context, obj->base_class)))){
        void* value = malloc(attrib->size);
        memcpy(value, attrib->data, attrib->size);
        return value;
    }
    return nullptr;
}

bool Object_set(unsigned int attrib_id, void* data, Object* obj, ObjectMethod context){
    ObjectAttrib* attrib = Object_get_attrib(attrib_id, obj);
    if(attrib != nullptr && 
        (attrib->setting_access == public || 
            (attrib->setting_access == private && Class_has_method(context, obj->base_class)))){
        if(attrib->data != nullptr)
            free(attrib->data);
        attrib->data = malloc(attrib->size);
        attrib->data = data;
        return true;
    }
    return false;
}

void Object_do(unsigned int method_id, Object* object, ...){
    void* return_value = nullptr;
    if(object != nullptr && object->base_class != nullptr){
        ObjectMethodId* method = Class_get_method(method_id, object->base_class);
        if(method != nullptr){
            va_list args;
            va_start(args, object);
            return_value = method->method(object, &args);
            va_end(args);
            
            if(method->return_value != nullptr){
                if(*method->return_value != nullptr)
                    free(*method->return_value);
                *method->return_value = return_value;
            }
            else if(return_value != nullptr){
                free(return_value);
                return_value = nullptr;
            }
        }
    }
}

Class* Object_class(Object* obj){
    if(obj != nullptr)
        return obj->base_class;
    return nullptr;
}

Class* Class_parent(Class* Class_target){
    if(Class_target != nullptr)
        return Class_target->parent_class;
    return nullptr;
}

Class* new_class(ObjectConstructor constructor, ObjectContentNumber content_number, ObjectMethodId methods[], ObjectAttrib default_attribs[], Class* parent_class){
    Class_init();
    Class* new_class = calloc(1, sizeof(Class));
    new_class->constructor = constructor;
    Class_set_parent_class(new_class, parent_class);
    set_methods_id(methods, content_number.methods_number);
    Class_set_up_methods(new_class, methods, content_number.methods_number);
    set_attrib_id(default_attribs, content_number.attribs_number);
    Class_set_up_attribs(new_class, default_attribs, content_number.attribs_number);
    Vector_push(new_class, all_classes);
    return new_class;
}

void delete_class(Class* some_class){
    if(some_class != nullptr){
        unsigned int* index = nullptr;
        Vector_get_index(some_class, &index, all_classes);
        if(index != nullptr)
            Vector_remove(*index, all_classes);
    }
}