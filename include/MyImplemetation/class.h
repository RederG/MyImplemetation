#ifndef CLASS_CREATION
    #define CLASS_CREATION 0x88ff
#endif

#ifndef CLASS_DEFINITION
    #define CLASS_DEFINITION 0xf8f8
#endif

#ifndef __CLASS_H__
    #define __CLASS_H__

    #include <stdarg.h>
    #include <stdlib.h>
    #include <stdbool.h>

    /*
    A class, it can represents an idea/object/functionality/etc :
    - It builds instances of this idea/object/functionality/etc
    
    It will contain : 
    - a constructor
    - all methods
    - all default attributes
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
    (These arguments are stored in the "...", the last argument of "Object_do(...)")
    - It will return a "void*" that points to the method's return value
    */
    typedef void*   (*ObjectMethod)         (Object*, va_list*);

    /*
    A function that a class provides to set up all attributes of an object when its creation
    - the "va_list*" contains every arguments passed in "new_object(...)"
    (These arguments are stored in the "...", the last argument of "new_object(...)")
    - It will return an "Object*" that points to the object that has been created
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
    When doing inheritance, each class has diffrent default attributes that the object copies.
    ObjectAttribPerClass will provide an organization to see the class owner of the attribute and the object's attributes itself.

    It contains :
    - The class owner
    - The object's attrib that is related to the class owner
    */
    typedef struct ObjectAttribPerClass{
        Class* base_class;
        ObjectAttrib* attribs;
    } ObjectAttribPerClass;

    /*
    To get each method that a class provide, we will need to assign each by an id.
    ObjectMethodId will give us that.

    It contains :
    - The pointer to the id of the method
    - The method that related to the id
    */
    typedef struct ObjectMethodId{
        unsigned int* id;
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
    Object* new_object(Class* base_class, ...);

    // Deletes an object
    void    delete_object(Object* obj);

    /* 
    Gets the copy of an attribute from the object that corresponds with the "attrib_id"
    - The "context" is a method (function) that it is used to verify if "Object_get(...)" can return the copy of the attrib
    (Set it to "nullptr" if you don't want to check about the context, especially when using the object outside the Class creation file)
    - If the attrib's getter is public, "Object_get(...)" will return the copy
    - If the attrib's getter is private, "Object_get(...)" will return the copy if the "context" is a method for "obj"
    - If the object doesn't have the attrib with "attrib_id" it will return "nullptr"
    - The "Class_owner_of_attribute" is a "Class*" that points to the class that have the attribute corresponding to "attrib_id"
    (Set it to "nullptr" if the attribute is on the Class of the object)
    */
    void*   Object_get(unsigned int attrib_id, Object* obj, ObjectMethod context, Class* Class_owner_of_attribute);

    /* 
    Sets the value of an attribute from the object that corresponds with the "attrib_id"
    - The "context" is a method (function) that it is used to verify if "Object_get(...)" can modify the value of the attrib
    (Set it to "nullptr" if you don't want to check about the context, especially when using the object outside the Class creation file)
    - If the attrib's setter is public, "Object_set(...)" will modify the value
    - If the attrib's setter is private, "Object_set(...)" will modify the value if the "context" is a method for "obj"
    - If the object doesn't have the attrib with "attrib_id", it will return false and true instead
    - The "Class_owner_of_attribute" is a "Class*" that points to the class that have the attribute corresponding to "attrib_id"
    (Set it to "nullptr" if the attribute is on the Class of the object)
    */
    bool    Object_set(unsigned int attrib_id, void* data, Object* obj, ObjectMethod context, Class* Class_owner_of_attribute);

    /*
    Calls the method that corresponds to "method_id" and return its return value
    - The "Class_owner_of_method" is a "Class*" that points to the class having the method with "method_id"
    (Setting it to "nullptr" indicates that the method is on the base_class of the object)
    - If the object's class doesn't have the method, it will return "nullptr"
    - The arguments passed in the "..." will be passed to the methods' "va_list*"
    */
    void    Object_do(unsigned int method_id, Object* object, Class* Class_owner_of_method, void** method_return_value, ...);

    // Gets the object's class
    Class*  Object_class(Object* obj);

    // Gets the parent class of a class
    Class*  Class_parent(Class* Class_target);

    // Deletes all objects and then deletes all classes
    void    Class_terminate();

    // Deletes a class
    void delete_class(Class* some_class);

#endif

#ifdef CLASS_FILE
    #if CLASS_FILE == CLASS_CREATION

        #ifndef Class_create_arg
            #define Class_create_arg(arg_name, arg_type, arg_list_ptr) arg_type* arg_name = malloc(sizeof(arg_type)); *arg_name = va_arg(*arg_list_ptr, arg_type)
        #endif

        /*
        Creates a new class
        */
        Class* Class_create(ObjectConstructor constructor, ObjectContentNumber content_number, ObjectMethodId methods[], ObjectAttrib default_attribs[], Class* parent_class);
        
        /*
        Gets the method that corresponds to the id
        - It will return "nullptr" if the "base_class" doesn't have the method
        */
        ObjectMethod Class_get_method(unsigned int id, Class* base_class);

        /*
        Gets the object's attribute that corresponds to the id
        - It will return "nullptr" if the "Class_owner" doesn't have the attribute
        - If "Class_owner" is "nullptr", the attribute must in the obj's base_class
        */
        ObjectAttrib* Object_get_attrib(unsigned int id, Object* obj, Class* Class_owner);
    #endif

    #undef CLASS_FILE
#endif