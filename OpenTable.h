//
// Created by vuniverse on 9/2/21.
//
#pragma once

#include "global_and_aliasing.h"

struct OpenTable {
private:
    position zero = ZERO;
    std::FILE* file;
    std::FILE* memory;
public:
    OpenTable();
    ~OpenTable();
    memSize getData( const cords& y , const cords& x , std::string& s );
};