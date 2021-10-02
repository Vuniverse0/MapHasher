//
// Created by vuniverse on 9/1/21.
//

#include "HashTable.h"
#include "functions.h"
 HashTable::HashTable()
 {
     /* Hash Table:         Columns:8
     *
     *     Rows: 255     Start node of singly linked list
     *
     *     Every info node have pointer(position in file) to next info node that should be in table
     *     Start node have only position without info
     *
     *     Every first info node have structure like this:
     *          Pointer to position of next node. Can also be pointer to end iterator or non valid 8 bytes
     *
     *     Every info node have structure like this:
     *          Pointer to next node of data info 8 bytes
     *          Individual no collision hash      4 bytes
     *          Data position in data file        8 bytes
     *
     */
    file = std::fopen( "/home/vuniverse/CLionProjects/CordsSorter/Output/hashes", "wb+" );
    memory = std::fopen("/home/vuniverse/CLionProjects/CordsSorter/Output/values", "wb" );
    std::fwrite(&zero, sizeof( position ), 1, memory);
    memSize i=0;
    do {
        std::fwrite(&zero, sizeof( position ), 1, file);
        i++;
    } while (i != HASHSIZE * 8);
}

HashTable::~HashTable()
{
    std::fclose( file );
    std::fclose( memory );
}

void HashTable::write( const cords& y ,const cords& x,  memSize size ,  std::FILE*& data )
{
    //Generate HASHES
    cords cord = ( y >= x ) ? ( y - x ) : ( x - y );  //Individual hash for node
    byte row = cord % HASHSIZE;                       //Hash for table
    byte column = bitIndetificator( y, x ).get();     //generate bit flags to variable flags os type union flags
    position pos = writeData(size, data);//Got data position end write data

    std::fseek( file, 0, SEEK_END );//Go to end of info file
    auto nodepos = static_cast<unsigned long>( ftell( file ) );

    //Data info
    std::fwrite( &zero, sizeof( position ), 1, file); //Pointer to next node of data info
    std::fwrite( &cord, sizeof( cords ), 1, file );          //Individual no collision hash
    std::fwrite( &pos, sizeof( position ), 1, file );     //Data position in data file

    setHashTablePosition(column,row,file);//Set position in hashtable

    position current;
    position temp;
    do {        //Check pointer
        current = static_cast< unsigned long >( std::ftell( file ) );
        std::fread( &temp, sizeof( position ), 1, file );
        std::fseek( file, temp, SEEK_SET );
    }while ( temp != zero );
    std::fseek( file, current, SEEK_SET );
    std::fwrite( &nodepos, sizeof( position ), 1, file);
    std::fseek(file,current,SEEK_SET);
    std::fread( &temp, sizeof( position ), 1, file);
}
position HashTable::writeData(const memSize& size, std::FILE*& data)
{
    auto temporalityPosition=static_cast< unsigned long >( std::ftell( memory ) );
    char* buff ;
    std::fread(buff, size, 1, data);
    std::fwrite( &size, sizeof( memSize ), 1, memory );
    std::fwrite( buff, size, 1, memory );
    return temporalityPosition;
}
