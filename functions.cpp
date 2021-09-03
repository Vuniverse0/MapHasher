//
// Created by vuniverse on 9/2/21.
//
#include <cstdio>//for working with files
#include "FileMacro&Aliases.h"
memSize getFileSize(FILE * data)
{
    std::fseek(data, 0, SEEK_END);
    return static_cast< unsigned long >( std::ftell( data ) );
}
