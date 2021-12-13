//
// Created by vuniverse on 9/2/21.
//

#pragma once

//Includes:

#include <cstdint>//for fixed size integers

#include <cstdio>//for working with files

//Debug includes:
#include <iostream>//DEBUG

//Typedefs:

typedef std::uint8_t byte;

typedef std::uint16_t memSize;

typedef std::uint32_t cords;

typedef std::uint64_t position;

//globals
extern const position ZERO;

extern const std::uint16_t HASHSIZE;

extern const byte BITSVARIATIONS;