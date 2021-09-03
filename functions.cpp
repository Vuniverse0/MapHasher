//
// Created by vuniverse on 9/2/21.
//
#include "FileMacro&Aliases.h"
#include "functions.h"

memSize getFileSize(FILE * data)
{
    std::fseek(data, 0, SEEK_END);
    return static_cast< unsigned long >( std::ftell( data ) );
}
void setHashTablePosition(const byte& column,const byte& row,FILE* file)
{
    position hashtablePosition = ( column * sizeof( position ) ) + ( row * BITSVARIATIONS * sizeof( position ) );
    std::fseek( file, hashtablePosition, SEEK_SET ); //Set position in hashtable
}
void checkPosition(FILE* file)
{
    position pos=static_cast< unsigned long >( ftell( file ) );
    std::cout<<"Current position : "<<pos<<std::endl;
}
//Fake macro lol ;) But if i will change this, I should not recompile all project.
const position ZERO = 0;

const byte HASHSIZE = 255;

const byte BITSVARIATIONS = 8;


//Bytes flags generator defintion

bitIndetificator::bitIndetificator( const cords& y, const cords& x )
{
    flags.hash = 0;
    flags.yHx = ( y >= x ) ? 1 : 0;
    flags.y = ( y%2 == 0 ) ? 1 : 0;
    flags.x = ( x%2 == 0 ) ? 1 : 0;
    byte P =  flags.hash;
    std::cout << "Generates bitset eqality to: " << ( ( int ) P ) << std::endl;
    std::cout << "        first bit: " << ( y >= x) << std::endl;
    std::cout << "       second bit: " << ( y % 2 == 0) << std::endl;
    std::cout << "        third bit: " << ( x % 2 == 0) << std::endl;
}

byte bitIndetificator::get() const
{
    return flags.hash;
}