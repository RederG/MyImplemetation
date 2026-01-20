#ifndef __CLASS_H__
    #define __CLASS_H__

    #include <stdarg.h>

    typedef struct Class Class;

    typedef struct Object Object;

    typedef void (*Constructor)(Class*, Object*, va_list*);
    typedef void* (*Method)(Object*, va_list*);

    typedef enum AttribAccess{
        private, public
    } AttribAccess;

    typedef struct Attribute{
        unsigned int* id;
        AttribAccess access;
    } Attribute;

    void terminate_classes();

    Class* new_class(unsigned int attrib_number, unsigned int facultative_attrib_number, unsigned int methods_number, Constructor constructor, Class* parent_class, Attribute* attribs, Method* methods);
    Object* new_object(Class* base_class, ...);
    void delete_object(Object* obj);
    void delete_class(Class* c);

    Class* Class_get_parent(Class* c);
    void Class_set_method(unsigned int index, unsigned int* id, Class* base_class);
    Class* Object_get_class(Object* obj);
    void* Object_get(unsigned int attribute_id, Object* obj, Method method);
    void  Object_set(unsigned int attribute_id, void* data, Object* obj, Method method);
    void Object_set_class(Class* base_class, Object* obj, Constructor constructor);
    void* Object_do(unsigned int method_id, Object* obj, ...);

#endif