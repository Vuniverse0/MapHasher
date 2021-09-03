//
// Created by vuniverse on 9/2/21.
//


//Includes:

#include <cstdint>//for fixed size integers

#include <cstdio>//for working with files

//Debug includes:
#include <iostream>//DEBUG


#ifndef CORDSSORTER_FILEMACRO_ALIASES_H
#define CORDSSORTER_FILEMACRO_ALIASES_H


//Typesefs:

typedef std::uint8_t byte;

typedef std::uint16_t memSize;

typedef std::uint32_t cords;

typedef std::uint64_t position;

//fake macro
extern const position ZERO;

extern const byte HASHSIZE;

extern const byte BITSVARIATIONS;

#endif //CORDSSORTER_FILEMACRO_ALIASES_H
