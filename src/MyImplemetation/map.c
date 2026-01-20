#include "../../include/MyImplemetation/vector.h"
#include "../../include/MyImplemetation/pair.h"
#include "../../include/MyImplemetation/map.h"
#include "../../include/tool.h"

const unsigned int MAP_SIZE = sizeof(void*) + sizeof(unsigned int) * 4;

typedef struct Map{
    Vector* list;
    unsigned int key_size;
} Map;

Pair* current_pair = nullptr;
unsigned int map_current_index = 0;

void* Map_get(void* key, Map* map){
    if(Map_has(key, map))
        return current_pair->second;
    return nullptr;
}

unsigned int Map_get_size(Map* map){
    return Vector_get_size(map->list);
}

bool Map_has(void* key, Map* map){
    current_pair = nullptr;
    while(Vector_get_next(map->list)){
        Pair* current_element = Vector_get_current_data();
        size_t i;
        bool same = true;

        for(i = 0; i < map->key_size; i++){
            char key_char = ((char*)key)[i];
            char element_char = ((char*)current_element->first)[i];
            if(key_char != element_char){
                same = false;
                break;
            }
        }
        if(same){
            current_pair = current_element;
            map_current_index = Vector_get_current_index();
            Vector_get_next(nullptr);
            return true;
        }
    }
    map_current_index = 0;
    Vector_get_next(nullptr);
    return false;
}

bool Map_remove(void* key, Map* map){
    if(Map_has(key, map)){
        delete_pair(current_pair);
        Vector_remove(map_current_index, map->list);
        return true;
    }
    return false;
}

bool Map_add(void* key, void* value, Map* map){
    if(!Map_has(key, map)){
        Vector_push(new_pair(key, value), map->list);
        return true;
    }
    return false;
}

bool Map_set(void* key, void* value, Map* map){
    if(Map_has(key, map)){
        free(current_pair->second);
        current_pair->second = value;
        return true;
    }
    return false;
}

bool Map_copy(Map* map, Map* destination){
    if(Vector_copy(map->list, destination->list));{
        destination->key_size = map->key_size;
        return true;
    }
    return false;
}

void Map_clear(Map* map){
    if(!Vector_is_empty(map->list))
        Vector_clear(map->list);
}

Map* new_map(unsigned int key_size){
    Map* map = malloc(sizeof(Map));
    map->list = new_vector(sizeof(Pair));
    map->key_size = key_size;
    return map;
}

void delete_map(Map* map){
    Map_clear(map);
    free(map);
}