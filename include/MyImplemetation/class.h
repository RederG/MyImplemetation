#ifndef CLASS_CREATION
    #define CLASS_CREATION 0x88ff
#endif

#ifndef __CLASS_H__
    #define __CLASS_H__

    #include <stdarg.h>
    #include <stdlib.h>
    #include <stdbool.h>

    /*
    A class, it can represents an idea/object/functionality/etc :
    - It builds instances of this idea/object/functionality/etc
    
    It contains : 
    - a constructor
    - all methods
    - all different attributes
    - the number of methods and attributes
    - its parent class (when doing inheritance)
    */
    typedef struct Class Class;

    /*
    An instance of a class

    It contains :
    - its base class
    - its attributes
    */
    typedef struct Object Object;

    /*
    A function that a class provides to do something with its objects
    - the "va_list*" contains every arguments passed in "Object_do(...)"
    [Note] : These arguments are stored in the "...", the last argument of "Object_do(...)"
    - It will return a "void*" that points to the method's return value
    */
    typedef void*   (*ObjectMethod)         (Object*, va_list*);

    /*
    A function that a class provides to set up the base class and all attributes of an object when its creation
    - the "va_list*" contains every arguments passed in "new_object(...)"
    [Note] : These arguments are stored in the "...", the last argument of "new_object(...)"
    - You can define all default values of every attributes on this function
    [Note] : The default values must not be declared in compilation time but dynamically, or you will uncounter a problem
    */
    typedef void    (*ObjectConstructor)    (Object*, va_list*);

    // The different access types of an object's attribute
    typedef enum ObjectAttribAccess{
        public, private
    } ObjectAttribAccess;

    /*
    A representation of an object attribute

    It contains :
    - The pointer to the attribute's id
    - The pointer to the attribute's data
    - The getting and the setting access of the attribute
    - The size of the attribute
    */ 
    typedef struct ObjectAttrib{
        unsigned int* id;
        void* data;
        ObjectAttribAccess getting_access;
        ObjectAttribAccess setting_access;
        unsigned int size;
    } ObjectAttrib;

    /*
    To get each method that a class provides, we will need to assign each with an id.
    ObjectMethodId will give us that.

    It contains :
    - The pointer to the id of the method
    - The pointer to the pointer of the return value
    - The method that related to the id
    */
    typedef struct ObjectMethodId{
        unsigned int* id;
        void** return_value;
        ObjectMethod method;
    } ObjectMethodId;

    /*
    To get the number of methods and attributes, ObjectContentNumber will give us that

    It contains :
    - the methods' number
    - the attributes' number
    */
    typedef struct ObjectContentNumber{
        unsigned int methods_number;
        unsigned int attribs_number;
    } ObjectContentNumber;

    // Creates a new object from a base class
    // - You can pass the arguments of the constructor on the "..."
    Object* new_object(Class* base_class, ...);

    // Deletes an object
    void    delete_object(Object* obj);

    /* 
    Gets the copy of an attribute from the object that corresponds with the "attrib_id"
    - The "context" is a method (function) that it is used to verify if "Object_get(...)" can return the copy of the attrib
    [Note] : Set it to "nullptr" if you don't want to check about the context, especially when using the object outside the "class creation file"
    - If the attrib's getter is public, "Object_get(...)" will return the copy
    - If the attrib's getter is private, "Object_get(...)" will return the copy if the "context" is a method for "obj"
    - If the object doesn't have the attrib with "attrib_id" it will return "nullptr"
    */
    void*   Object_get(unsigned int attrib_id, Object* obj, ObjectMethod context);

    /* 
    Sets the value of an attribute from the object that corresponds with the "attrib_id"
    - The "context" is a method (function) that it is used to verify if "Object_get(...)" can modify the value of the attrib
    [Note] : Set it to "nullptr" if you don't want to check about the context, especially when using the object outside the "class creation file"
    - If the attrib's setter is public, "Object_set(...)" will modify the value
    - If the attrib's setter is private, "Object_set(...)" will modify the value if the "context" is a method for "obj"
    - If the object doesn't have the attrib with "attrib_id", it will return false and true instead
    */
    bool    Object_set(unsigned int attrib_id, void* data, Object* obj, ObjectMethod context);

    /*
    Calls the method that corresponds to "method_id" and puts its return value on the method's id's return value
    - If the object's class doesn't have the method, the "method's return value" will set to "nullptr"
    - The arguments passed in the "..." will be passed to the methods' "va_list*"
    */
    void    Object_do(unsigned int method_id, Object* object, ...);

    // Gets the object's class
    Class*  Object_class(Object* obj);

    // Gets the parent class of a class
    Class*  Class_parent(Class* Class_target);

    // Deletes all objects and then deletes all classes
    void    Class_terminate();

    // Deletes a class
    void    delete_class(Class* some_class);

#endif

#ifdef CLASS_FILE
    #if CLASS_FILE == CLASS_CREATION

        #ifndef Class_create_arg
            #define Class_create_arg(arg_name, arg_type, arg_list_ptr) arg_type* arg_name = malloc(sizeof(arg_type)); *arg_name = va_arg(*arg_list_ptr, arg_type)
        #endif

        /*
        Creates a new class
        */
        Class* new_class(ObjectConstructor constructor, ObjectContentNumber content_number, ObjectMethodId methods[], ObjectAttrib default_attribs[], Class* parent_class);
        
        /*
        Gets the method that corresponds to the id
        - It will return "nullptr" if the "base_class" doesn't have the method
        */
        ObjectMethodId* Class_get_method(unsigned int id, Class* base_class);

        /*
        Gets the object's attribute that corresponds to the id
        - It will return "nullptr" if the "Class_owner" doesn't have the attribute
        */
        ObjectAttrib* Object_get_attrib(unsigned int id, Object* obj);
    #endif

    #undef CLASS_FILE
#endif