#ifndef __PAIR_H__
    #define __PAIR_H__

    typedef struct Pair{
        void* first;
        void* second;
    } Pair;

    extern const unsigned int PAIR_SIZE;

    Pair* new_pair(void* first, void* second);
    void delete_pair(Pair* pair);

#endif