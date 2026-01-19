#include "../../include/MyImplemetation/vector.h"
#include "../../include/MyImplemetation/map.h"
#include "../../include/MyImplemetation/class.h"

typedef struct Class{
    Vector* all_attributes;
    AttribAccess access;
} Class;

typedef struct MethodParameters{
    Vector* all_parameters;
} MethodParameters;

Map* all_classes_id = nullptr;

void try_init(){
    if(all_classes_id == nullptr)
        all_classes_id = new_map(POINTER_SIZE, POINTER_SIZE);
}

Class* new_class(unsigned int attrib_number, AttribAccess access){
    Class* the_class = malloc(sizeof(Class));

    the_class->all_attributes = new_vector();
    Vector_resize(attrib_number, the_class->all_attributes);
    Vector_fill(nullptr, 0, attrib_number, the_class->all_attributes);

    the_class->access = access;
    return the_class;
}
