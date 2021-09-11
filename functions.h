//
// Created by vuniverse on 9/3/21.
//

#ifndef CORDSSORTER_FUNCTIONS_H
#define CORDSSORTER_FUNCTIONS_H
#include <cstdio>//for working with files
#include "FileMacro&Aliases.h"

void setHashTablePosition(const byte& column,const byte& row,FILE* file);



struct bitIndetificator {
    bitIndetificator( const cords& y, const cords& x );
    byte get() const;
private :
    union {
        byte hash;
        struct {
            byte yHx : 1;
            byte y : 1;
            byte x : 1;
        };
    } flags;
};
#endif //CORDSSORTER_FUNCTIONS_H
