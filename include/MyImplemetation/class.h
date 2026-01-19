#ifndef __CLASS_H__
    #define __CLASS_H__

    typedef struct Class Class;

    typedef struct MethodParameters MethodParameters;

    typedef struct Object{
        void* (*get)(unsigned int, Object*);
        void  (*set)(unsigned int, void*, Object*);
        void* (*execute)(unsigned int, MethodParameters*);
    } Object;

    typedef enum AttribAccess{
        private, public
    } AttribAccess;

    Class* new_class(unsigned int attrib_number, AttribAccess access);
    Object* new_object(Class* parent_class);

#endif