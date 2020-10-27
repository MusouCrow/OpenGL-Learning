#ifndef UTIL_ARRAY_H
#define UTIL_ARRAY_H

#include <cstring>
#include "common.h"

template <class T> struct Array {
public:
    T* list;
    int count;

    void Clone(Array<T>& array) {
        this->list = new T[array.count];
        this->count = array.count;
        
        memcpy(this->list, array.list, array.count * sizeof(T));
    }
};

#endif