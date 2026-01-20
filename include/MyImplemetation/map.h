#ifndef __MAP_H__
    #define __MAP_H__

    #include "stdbool.h"

    typedef struct Map Map;
    extern const unsigned int MAP_SIZE;

    void* Map_get(void* key, Map* map);
    unsigned int Map_get_size(Map* map);
    bool Map_has(void* key, Map* map);
    bool Map_remove(void* key, Map* map);
    bool Map_add(void* key, void* value, Map* map);
    bool Map_set(void* key, void* value, Map* map);
    bool Map_copy(Map* map, Map* destination);
    void Map_clear(Map* map);
    Map* new_map(unsigned int key_size);
    void delete_map(Map* map);

#endif