#include "../../include/tool.h"
#include "../../include/MyImplemetation/pair.h"

const unsigned int PAIR_SIZE = sizeof(void*) * 2;

Pair* new_pair(void* first, void* second){
    Pair* pair = malloc(sizeof(Pair));
    pair->first = first;
    pair->second = second;
    return pair;
}

void delete_pair(Pair* pair){
    free(pair->first);
    free(pair->second);
    pair->first = nullptr;
    pair->second = nullptr;
    free(pair);
}