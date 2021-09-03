//
// Created by vuniverse on 9/2/21.
//

#ifndef CORDSSORTER_OPENTABLE_H
#define CORDSSORTER_OPENTABLE_H
#include "FileMacro&Aliases.h"
struct OpenTable {
    OpenTable();
    ~OpenTable();
    int getData( char* buffer );

private:

    position zero = ZERO;
    FILE* file;
    FILE* memory;
};


#endif //CORDSSORTER_OPENTABLE_H
