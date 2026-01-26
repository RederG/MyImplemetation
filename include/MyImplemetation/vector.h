#ifndef __VECTOR_H__
    #define __VECTOR_H__

    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>

    #ifndef nullptr
        #define nullptr 0x0
    #endif

    #ifndef Vector_create_implemetation
        #define Vector_create_implemetation(type)\
            \
            Vector_##type* current_vector_##type = nullptr;\
            type current_##type;\
            unsigned int current_##type##_index = 0;\
            \
            type* type##_at(unsigned int index, Vector_##type* this){\
                if(index >= this->size)\
                    return nullptr;\
                return &this->elements[index];\
            };\
            \
            type* type##_first(Vector_##type* this){\
                if(this->size == 0)\
                    return nullptr;\
                return &this->elements[0];\
            };\
            \
            type* type##_last(Vector_##type* this){\
                if(this->size == 0)\
                    return nullptr;\
                return &this->elements[this->size - 1];\
            };\
            \
            bool type##_is_empty(Vector_##type* this){\
                if(this->size == 0)\
                    return true;\
                return false;\
            };\
            \
            bool type##_push(type data, Vector_##type* this){\
                if(this->size == 0){\
                    this->size = 1;\
                    this->capacity = 1;\
                    this->elements = malloc(sizeof(type));\
                    memcpy(this->elements, &data, sizeof(type));\
                    return true;\
                }\
                if(this->size > 0){\
                    if(this->size + 1 > this->capacity){\
                        this->capacity *= 2;\
                        type* elements = malloc(this->capacity * sizeof(type));\
                        memcpy(elements, this->elements, sizeof(type) * this->size);\
                        free(this->elements);\
                        this->elements = elements;\
                    }\
                    this->size += 1;\
                    memcpy(&this->elements[this->size - 1], &data, sizeof(type));\
                    return true;\
                }\
            };\
            \
            bool type##_insert(unsigned int index, type data, Vector_##type* this){\
                if(index >= this->size)\
                    return false;\
                if(this->size + 1 > this->capacity)\
                    this->capacity *= 2;\
                type* elements = malloc(sizeof(type) * this->capacity);\
                if(index > 0)\
                    memcpy(elements, this->elements, sizeof(type) * index);\
                memcpy(&elements[index], &data, sizeof(type));\
                memcpy(elements + index + 1, this->elements + index, sizeof(type) * (this->size - index - 1));\
                free(this->elements);\
                this->elements = elements;\
                this->size += 1;\
                return true;\
            };\
            \
            bool type##_modify(unsigned int index, type data, Vector_##type* this){\
                if(index >= this->size)\
                    return false;\
                memcpy(&this->elements[index], &data, sizeof(type));\
                return true;\
            };\
            \
            bool type##_erase(unsigned int index, Vector_##type* this){\
                if(index >= this->size)\
                    return false;\
                if(this->size - 1 < this->capacity)\
                    this->capacity /= 2;\
                type* elements = malloc(sizeof(type) * this->capacity);\
                if(index > 0)\
                    memcpy(elements, this->elements, sizeof(type) * index);\
                memcpy(elements + index, this->elements + index + 1, sizeof(type) * (this->size - index - 1));\
                free(this->elements);\
                this->elements = elements;\
                this->size -= 1;\
                return true;\
            };\
            \
            bool type##_erase_begin(Vector_##type* this){\
                return type##_erase(0, this);\
            };\
            \
            bool type##_erase_last(Vector_##type* this){\
                return type##_erase(this->size - 1, this);\
            };\
            \
            void type##_copy(Vector_##type* this, Vector_##type* destination){\
                if(destination->elements != nullptr)\
                    free(destination->elements);\
                destination->elements = malloc(sizeof(type) * this->capacity);\
                if(this->elements != nullptr)\
                    memcpy(destination->elements, this->elements, sizeof(type) * this->capacity);\
                destination->size = this->size;\
                destination->capacity = this->capacity;\
            };\
            \
            type* type##_get_next(Vector_##type* this){\
                if(this == nullptr){\
                    current_vector_##type = nullptr;\
                    current_##type##_index = 0;\
                    return nullptr;\
                }\
                if(current_vector_##type != this){\
                    current_vector_##type = this;\
                    current_##type##_index = 0;\
                }\
                if(current_##type##_index >= this->size){\
                    current_##type##_index = 0;\
                    return nullptr;\
                };\
                current_##type = this->elements[current_##type##_index];\
                current_##type##_index++;\
                return &this->elements[current_##type##_index - 1];\
            };\
            \
            type type##_current_##type(){\
                return current_##type;\
            };\
            \
            unsigned int type##_current_index(){\
                return current_##type##_index;\
            };\
            \
            bool type##_fill(unsigned int begin, unsigned int end, type data, Vector_##type* this){\
                if(begin >= this->size || end > this->size || end < begin)\
                return false;\
                for(int i = begin; i < end; i++)\
                memcpy(&this->elements[i], &data, sizeof(type));\
                return true;\
            };\
            \
            void type##_resize(unsigned int size, Vector_##type* this){\
                this->capacity = 1;\
                for(int i = 0; i < size; i++){\
                    if(i > this->capacity)\
                        this->capacity *= 2;\
                }\
                if(size == 0){\
                    free(this->elements);\
                    this->elements = nullptr;\
                    this->size = 0;\
                    this->capacity = 0;\
                    return;\
                }\
                type* elements = malloc(sizeof(type) * this->capacity);\
                if(this->elements != nullptr){\
                    if(size <= this->size)\
                        memcpy(elements, this->elements, sizeof(type) * size);\
                    else{\
                        memcpy(elements, this->elements, sizeof(type) * this->size);\
                        for(int i = this->size; i < this->capacity; i++)\
                            elements[i] = 0;\
                    }\
                }\
                free(this->elements);\
                this->elements = elements;\
                this->size = size;\
            };\
            \
            void type##_clear(Vector_##type* this){\
                type##_resize(0, this);\
            };\
            \
            void type##_search(type data, unsigned int** result, Vector_##type* this){\
                if(result == nullptr)\
                    return;\
                for(int i = 0; i < this->size; i++){\
                    if(this->elements[i] == data){\
                        if(*result != nullptr)\
                            free(*result);\
                        *result = malloc(sizeof(type));\
                        **result = i;\
                        return;\
                    }\
                }\
                if(*result != nullptr)\
                    free(*result);\
                *result = nullptr;\
            };\
            \
            void Vector_##type##_configure(Vector_##type* vector){\
                vector->elements = nullptr;\
                vector->size = 0;\
                vector->capacity = 0;\
            }\
            \
            void Vector_controller_##type##_configure(Vector_controller_##type* vector_ctrl){\
                vector_ctrl->at = &type##_at;\
                vector_ctrl->first = &type##_first;\
                vector_ctrl->last = &type##_last;\
                vector_ctrl->is_empty = &type##_is_empty;\
                vector_ctrl->push = &type##_push;\
                vector_ctrl->insert = &type##_insert;\
                vector_ctrl->set = &type##_modify;\
                vector_ctrl->erase = &type##_erase;\
                vector_ctrl->erase_begin = &type##_erase_begin;\
                vector_ctrl->erase_last = &type##_erase_last;\
                vector_ctrl->copy = &type##_copy;\
                vector_ctrl->get_next = &type##_get_next;\
                vector_ctrl->current_##type = &type##_current_##type;\
                vector_ctrl->current_index = &type##_current_index;\
                vector_ctrl->resize = &type##_resize;\
                vector_ctrl->fill = &type##_fill;\
                vector_ctrl->clear = &type##_clear;\
                vector_ctrl->search = &type##_search;\
            }\
            \
            Vector_##type* new_vector_##type(){\
                Vector_##type* vector = malloc(sizeof(Vector_##type));\
                Vector_##type##_configure(vector);\
                return vector;\
            }\
            \
            Vector_controller_##type* new_vector_controller_##type(){\
                Vector_controller_##type* vector_ctrl = malloc(sizeof(Vector_controller_##type));\
                Vector_controller_##type##_configure(vector_ctrl);\
                return vector_ctrl;\
            }\
            \
            void delete_vector_##type(Vector_##type* this){\
                free(this->elements);\
                free(this);\
            }\
            \
            void delete_vector_controller_##type(Vector_controller_##type* vector_ctrl){\
                free(vector_ctrl);\
            }\

    #endif

    #ifndef Vector_create_header
        #define Vector_create_header(type)\
            \
            typedef struct Vector_##type Vector_##type;\
            \
            typedef struct Vector_##type{\
                type* elements;\
                unsigned int size;\
                unsigned int capacity;\
            } Vector_##type;\
            \
            typedef struct Vector_controller_##type{\
                type*           (*at)(unsigned int index, Vector_##type* this);\
                type*           (*first)(Vector_##type* this);\
                type*           (*last)(Vector_##type* this);\
                bool            (*is_empty)(Vector_##type* this);\
                bool            (*push)(type data, Vector_##type* this);\
                bool            (*insert)(unsigned int index, type data, Vector_##type* this);\
                bool            (*set)(unsigned int index, type data, Vector_##type* this);\
                bool            (*erase)(unsigned int index, Vector_##type* this);\
                bool            (*erase_begin)(Vector_##type* this);\
                bool            (*erase_last)(Vector_##type* this);\
                void            (*copy)(Vector_##type* this, Vector_##type* destination);\
                type*           (*get_next)(Vector_##type* this);\
                type            (*current_##type)();\
                unsigned int    (*current_index)();\
                void            (*resize)(unsigned int size, Vector_##type* this);\
                bool            (*fill)(unsigned int begin, unsigned int end, type data, Vector_##type* this);\
                void            (*clear)(Vector_##type* this);\
                void            (*search)(type data, unsigned int** result, Vector_##type* this);\
            } Vector_controller_##type;\
            \
            void Vector_##type##_configure(Vector_##type* vector);\
            void Vector_controller_##type##_configure(Vector_controller_##type* vector_ctrl);\
            Vector_##type* new_vector_##type();\
            Vector_controller_##type* new_vector_controller_##type();\
            void delete_vector_##type(Vector_##type* this);\
            void delete_vector_controller_##type(Vector_controller_##type* vector_ctrl);
    #endif

    #ifndef Vector
        #define Vector(type, vector_name)\
            Vector_##type vector_name;\
            Vector_##type##_configure(&vector_name)

        #define Vector_controller(type, vector_ctrl_name)\
            Vector_controller_##type vector_ctrl_name;\
            Vector_controller_##type##_configure(&vector_ctrl_name)
    #endif

#endif