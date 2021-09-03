//
// Created by vuniverse on 8/21/21.
//

#ifndef CORDSSORTER_HASHTABLE_H
#define CORDSSORTER_HASHTABLE_H
#include "FileMacro&Aliases.h"

struct HashTable {
    HashTable();
    ~HashTable();
    void write( const cords& y ,const cords& x, FILE* data );
private:
    position zero = ZERO;
    FILE* file;
    FILE* memory;
    position writeData(const memSize& size, FILE* data);
};


#endif //CORDSSORTER_HASHTABLE_H
