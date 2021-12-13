//
// Created by vuniverse on 9/2/21.
//
#include "global_and_aliasing.h"
#include "functions.h"
#include <limits>

void setHashTablePosition(const byte& column, const byte& row, std::FILE*& file)
{
    position hashtablePosition = ( column * sizeof( position ) ) + ( row * BITSVARIATIONS * sizeof( position ) );
    std::fseek( file, hashtablePosition, SEEK_SET ); //Set position in hashtable
}

const position ZERO = 0;
const std::uint16_t HASHSIZE = std::numeric_limits<uint16_t>::max();
const byte BITSVARIATIONS = 8;

//Bytes flags generator defintion

bitIdentification::bitIdentification(const cords& y, const cords& x )
{
    flags.hash = 0;
    flags.yHx = ( y >= x ) ? 1 : 0;
    flags.y = ( y%2 == 0 ) ? 1 : 0;
    flags.x = ( x%2 == 0 ) ? 1 : 0;
}

byte bitIdentification::get() const
{
    return flags.hash;
}