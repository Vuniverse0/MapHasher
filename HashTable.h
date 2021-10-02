//
// Created by vuniverse on 8/21/21.
//

#pragma once

#include "global_and_aliasing.h"

struct HashTable {
private:
    position zero = ZERO;
    std::FILE* file;
    std::FILE* memory;
    position writeData(const memSize& size, std::FILE*& data);
public:
    HashTable();
    ~HashTable();
    void write( const cords& y ,const cords& x,  memSize tempDebugSize, std::FILE*& data);
};