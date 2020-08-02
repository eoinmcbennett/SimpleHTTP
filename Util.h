//
// Created by Eoin on 23/07/2020.
//

#ifndef SERVERTEST_UTIL_H
#define SERVERTEST_UTIL_H

#include<malloc.h>

class Util {

public:
    /**
     * Returns a pointer to a location with size amount of bytes allocated
     * Automatically adds a null terminator
     * @param size
     * @return
     */
    static char* allocateString(unsigned int size){
        char* mem = (char*)malloc(size + 1);
        if(!mem){
            return nullptr;
        }
        mem[size] = '\0';
        return mem;
    }
};


#endif //SERVERTEST_UTIL_H
