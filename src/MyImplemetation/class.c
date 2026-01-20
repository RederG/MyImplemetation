#include <stdarg.h>
#include "../../include/tool.h"
#include "../../include/MyImplemetation/vector.h"
#include "../../include/MyImplemetation/map.h"
#include "../../include/MyImplemetation/class.h"

typedef struct Class{
    Map* all_default_attributes;
    Map* all_attributes_access;
    Class* parent_class;
    Constructor constructor;
    Method* methods;
    unsigned int methods_number;
    unsigned int facultative_attrib_number;
} Class;

typedef struct Object{
    Class* base_class;
    Map* all_attributes;
} Object;

Vector* all_classes = nullptr;
bool class_initiated = false;

bool Object_can_be_modified(Method method, Object* obj);

void init_classes(){
    all_classes = new_vector(sizeof(Class));
    class_initiated = true;
}

void terminate_classes(){
    Vector_get_next(nullptr);
    while(Vector_get_next(all_classes))
        delete_class(Vector_get_current_data());
    all_classes = nullptr;
    class_initiated = false;
}

Class* new_class(unsigned int attrib_number, unsigned int facultative_attrib_number, unsigned int methods_number, Constructor constructor, Class* parent_class, Attribute* attribs, Method* methods){
    if(!class_initiated) init_classes();

    Class* the_class = malloc(sizeof(Class));

    the_class->all_default_attributes = new_map(POINTER_SIZE);
    the_class->all_attributes_access = new_map(POINTER_SIZE);
    the_class->parent_class = parent_class;
    the_class->facultative_attrib_number = facultative_attrib_number;
    the_class->constructor = constructor;
    the_class->methods = malloc(sizeof(Method) * methods_number);
    the_class->methods = methods;
    the_class->methods_number = methods_number;
    for(int i = 0; i < attrib_number; i++){
        *attribs[i].id = (Address)(attribs[i].id);
        Map_add(attribs[i].id, &attribs[i].access, the_class->all_attributes_access);
        Map_add(attribs[i].id, nullptr, the_class->all_default_attributes);
    }

    Vector_push(the_class, all_classes);

    return the_class;
}

Object* new_object(Class* base_class, ...){
    if(!class_initiated) init_classes();

    Object* obj = malloc(sizeof(Object));

    va_list args;
    va_start(args, base_class);
    base_class->constructor(base_class, obj, &args);
    va_end(args);

    return obj;
}

void delete_object(Object* obj){
    if(!class_initiated) init_classes();
    Map_clear(obj->all_attributes);
    obj->base_class = nullptr;
    free(obj);
}

void delete_class(Class* class_to_delete){
    if(!class_initiated) init_classes();
    Map_clear(class_to_delete->all_default_attributes);
    class_to_delete->parent_class = nullptr;
    class_to_delete->constructor = nullptr;
    free(class_to_delete);
}

Class* Class_get_parent(Class* c){
    if(!class_initiated) init_classes();
    return c->parent_class;
}

void Class_set_method(unsigned int index, unsigned int* id, Class* base_class){
    if(base_class->methods[index] != nullptr)
        *id = index;
}

Class* Object_get_class(Object* obj){
    if(!class_initiated) init_classes();
    return obj->base_class;
}

void* Object_get(unsigned int attribute_id, Object* obj, Method method){
    if(!class_initiated) init_classes();
    AttribAccess* access = Map_get(&attribute_id, Object_get_class(obj)->all_attributes_access);
    if(*access == public && Object_can_be_modified(method, obj))
        return Map_get(&attribute_id, obj->all_attributes);
    return nullptr;
}

void Object_set(unsigned int attribute_id, void* data, Object* obj, Method method){
    if(!class_initiated) init_classes();
    AttribAccess* access = Map_get(&attribute_id, Object_get_class(obj)->all_attributes_access);
    if(*access == public && Object_can_be_modified(method, obj))
        Map_set(&attribute_id, data, obj->all_attributes);
}

void Object_set_class(Class* base_class, Object* obj, Constructor constructor){
    if(base_class->constructor == constructor){
        obj->base_class = base_class;
        obj->all_attributes = new_map(POINTER_SIZE);
        Map_copy(base_class->all_default_attributes, obj->all_attributes);
    }
}

void* Object_do(unsigned int method_id, Object* obj, ...){
    if(!class_initiated) init_classes();
    va_list args;

    va_start(args, obj);
    void* return_value = Object_get_class(obj)->methods[method_id](obj, &args);
    va_end(args);

    return return_value;
}

bool Object_can_be_modified(Method method, Object* obj){
    for(int i = 0; i < obj->base_class->methods_number && method != nullptr; i++){
        Method current_method = obj->base_class->methods[i];
        if((&current_method != nullptr && &current_method == &method) || (Constructor)(&method) == obj->base_class->constructor)
            return true;
    }
    return false;
}
