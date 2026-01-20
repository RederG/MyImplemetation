#ifndef __VECTOR__
    #define __VECTOR__

    #include "stdbool.h"

    typedef struct Vector Vector;
    extern const unsigned int VECTOR_SIZE;

    // Gets the data from the given index of the vector
    void* Vector_get(unsigned int index, Vector* from_vector);
    
    // Gets the last data of the vector
    void* Vector_get_last(Vector* of_vector);
    
    // Gets the first data of the vector
    void* Vector_get_top(Vector* of_vector);

    // Gets the size of the vector
    unsigned int Vector_get_size(Vector* vector);

    // Gets the capacity of the vector
    unsigned int Vector_get_capacity(Vector* vector);
    
    // Gets the next data of the vector
    // - The "next data" can be get by the
    // Vector_get_current_data() function
    void* Vector_get_next(Vector* vector);
    
    // Gets the current data stored after calling 
    //the Vector_get_next(Vector* vector) function
    void* Vector_get_current_data();

    // Gets the current index stored after calling 
    //the Vector_get_next(Vector* vector) function
    unsigned int Vector_get_current_index();
    
    // Clears the content of the vector
    void Vector_clear(Vector* vector);
    
    // Resize the vector and fill it properly
    void Vector_resize(unsigned int new_size, Vector* vector);
    
    // Fill the vector with the given data
    bool Vector_fill(void* with_data, unsigned int from_begin, unsigned int to_last, Vector* vector_target);
    
    // Add a new data to the vector
    bool Vector_push(void* data, Vector* on_vector);
    
    // Insert a new data at the given index of the vector
    bool Vector_insert(unsigned int at_index, void* data, Vector* to_vector);

    // Modify a data at the given index of the vector
    bool Vector_set(unsigned int index, void* data, Vector* vector_target);
    
    // Remove a data from the given index of the vector
    bool Vector_remove(unsigned int index, Vector* from_vector);
    
    // Remove the last data of the vector
    bool Vector_remove_last(Vector* of_vector);
    
    // Remove the first data of the vector
    bool Vector_remove_begin(Vector* of_vector);
    
    // Verifies if the vector is empty
    // - Returns True if empty
    // - Returns False if not
    bool Vector_is_empty(Vector* vector);

    // Copies the data on the vector to one another
    bool Vector_copy(Vector* vector, Vector* to_vector);

    // Gets all of the data in "char*"
    char* Vector_get_data_block(Vector* vector);

    // Gets the index of the given element
    unsigned int* Vector_get_index(void* data, Vector* vector);
    
    // Create dynamicaly a new vector
    Vector* new_vector(unsigned int value_size);

    // Delete dynamicaly a vector
    void delete_vector(Vector* vector);

#endif