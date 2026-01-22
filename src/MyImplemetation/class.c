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
} Class;

typedef struct Object{
    Class* base_class;
    ObjectAttribPerClass* attribs;
    unsigned int base_class_number;
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
        Vector_remove_begin(all_classes);
        Vector_get_next(nullptr);
    }
    all_classes = nullptr;
    all_objects = nullptr;
}

ObjectMethod Class_get_method(unsigned int id, Class* base_class){
    size_t i;
    for(i = 0; base_class != nullptr && i < base_class->content_number.methods_number; i++){
        if(*base_class->methods[i].id == id)
            return base_class->methods[i].method;
    }
    return nullptr;
}

ObjectAttrib* Object_get_attrib(unsigned int id, Object* obj, Class* Class_owner){
    size_t i, j;
    if(obj != nullptr && obj->base_class != nullptr){
        Class* base_class = obj->base_class;
        if(Class_owner != nullptr){
            base_class = Class_owner;
            for(i = 0; i <= obj->base_class_number; i++){
                if(obj->attribs[i].base_class == base_class){
                    for(j = 0; j < base_class->content_number.attribs_number; j++){
                        if(*obj->attribs[i].attribs[j].id == id)
                            return &obj->attribs[i].attribs[j];
                    }
                }
            }
        }
        for(j = 0; j < base_class->content_number.attribs_number; j++){
            if(*obj->attribs[0].attribs[j].id == id)
                return &obj->attribs[0].attribs[j];
        }
    }
    return nullptr;
}

void Class_set_methods_id(Class* base_class){
    size_t i;
    for(i = 0; i < base_class->content_number.methods_number; i++)
        (*base_class->methods[i].id) = (Address)(base_class->methods[i].id);
}

void Class_set_attrib_id(Class* base_class){
    size_t i;
    for(i = 0; i < base_class->content_number.attribs_number; i++)
        (*base_class->default_attrib[i].id) = (Address)(base_class->default_attrib[i].id);
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

void Object_set_class_parent_number(Object* obj){
    if(obj != nullptr){
        obj->base_class_number = 0;
        Class* base_class = Class_parent(obj->base_class);
        while(base_class != nullptr){
            base_class = Class_parent(obj->base_class);
            obj->base_class_number++;
        }
    }
}

void Object_set_up_attribs(Object* obj){
    size_t i;
    obj->attribs = calloc(obj->base_class_number, sizeof(ObjectAttribPerClass));
    Class* current_class = obj->base_class;
    for(i = 0; current_class != nullptr; i++){
        ObjectAttribPerClass* current_attrib = malloc(sizeof(ObjectAttribPerClass));
        obj->attribs[i] = *current_attrib;
        obj->attribs[i].attribs = malloc(sizeof(ObjectAttrib) * current_class->content_number.attribs_number);
        obj->attribs[i].base_class = current_class;
        memcpy(obj->attribs[i].attribs, current_class->default_attrib, sizeof(ObjectAttrib) * current_class->content_number.attribs_number);
        current_class = Class_parent(current_class);
    }
}

Object* new_object(Class* base_class, ...){
    Object* new_obj = nullptr;
    if(base_class != nullptr){
        new_obj = malloc(sizeof(Object));
        new_obj->base_class = base_class;
        Object_set_class_parent_number(new_obj);
        Object_set_up_attribs(new_obj);

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
        size_t i, j;
        for(i = 0; i < obj->base_class_number; i++){
            for(j = 0; j < obj->attribs[i].base_class->content_number.attribs_number; j++){
                free(obj->attribs[i].attribs[j].data);
                free(&obj->attribs[i].attribs[j]);
            }
            obj->attribs[i].base_class = nullptr;
            free(&obj->attribs[i]);
        }
        obj->base_class = nullptr;
        unsigned int* index = Vector_get_index(obj, all_objects);
        if(index != nullptr)
            Vector_remove(*index, all_objects);
    }
}

void* Object_get(unsigned int attrib_id, Object* obj, ObjectMethod context, Class* Class_owner_of_attribute){
    ObjectAttrib* attrib = Object_get_attrib(attrib_id, obj, Class_owner_of_attribute);
    if(attrib != nullptr && 
        (attrib->getting_access == public || 
            (attrib->getting_access == private && Class_has_method(context, obj->base_class)))){
        void* value = malloc(attrib->size);
        memcpy(value, attrib->data, attrib->size);
        return value;
    }
    return nullptr;
}

bool Object_set(unsigned int attrib_id, void* data, Object* obj, ObjectMethod context, Class* Class_owner_of_attribute){
    ObjectAttrib* attrib = Object_get_attrib(attrib_id, obj, Class_owner_of_attribute);
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

void Object_do(unsigned int method_id, Object* object, Class* Class_owner_of_method, void** method_return_value, ...){
    void* return_value = nullptr;
    if(object != nullptr && object->base_class != nullptr){
        Class* base_class = object->base_class;
        if(Class_owner_of_method != nullptr)
            base_class = Class_owner_of_method;
        ObjectMethod method = Class_get_method(method_id, base_class);
        if(method != nullptr){
            va_list args;
            va_start(args, method_return_value);
            return_value = method(object, &args);
            va_end(args);
            
            if(method_return_value != nullptr){
                if(*method_return_value != nullptr)
                    free(*method_return_value);
                *method_return_value = return_value;
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

Class* Class_create(ObjectConstructor constructor, ObjectContentNumber content_number, ObjectMethodId methods[], ObjectAttrib default_attribs[], Class* parent_class){
    Class_init();
    Class* new_class = calloc(1, sizeof(Class));
    new_class->constructor = constructor;
    new_class->content_number = content_number;
    new_class->methods = methods;
    new_class->default_attrib = default_attribs;
    new_class->parent_class = parent_class;
    Class_set_methods_id(new_class);
    Class_set_attrib_id(new_class);
    Vector_push(new_class, all_classes);
    return new_class;
}

void delete_class(Class* some_class){
    unsigned int* index = Vector_get_index(some_class, all_classes);
    if(some_class != nullptr && index != nullptr)
        Vector_remove(*index, all_classes);
}