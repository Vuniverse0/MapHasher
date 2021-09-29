//
// Created by vuniverse on 9/2/21.
//

#ifndef CORDSSORTER_OPENTABLE_H
#define CORDSSORTER_OPENTABLE_H
#include "FileMacro&Aliases.h"
struct OpenTable {
    OpenTable();
    ~OpenTable();
    memSize getData( const cords& y , const cords& x , std::string& s );

private:

    position zero = ZERO;
    FILE* file;
    FILE* memory;
};


#endif //CORDSSORTER_OPENTABLE_H
