//
// Created by vuniverse on 9/3/21.
//
#pragma once

#include <cstdio>//for working with files
#include "global_and_aliasing.h"

void setHashTablePosition(const byte& column, const byte& row, std::FILE* file);

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