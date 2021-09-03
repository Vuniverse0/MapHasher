//
// Created by vuniverse on 9/2/21.
//

#include "OpenTable.h"
#include "functions.h"

OpenTable::OpenTable()
{
    file = std::fopen( "/home/vuniverse/CLionProjects/CordsSorter/Output/hashes", "rb" );
    memory = std::fopen("/home/vuniverse/CLionProjects/CordsSorter/Output/values", "rb" );
}

OpenTable::~OpenTable()
{
    fclose(file);
    fclose(memory);
}
int OpenTable::getData( const cords& y , const cords& x , char* buffer )
{
    //Generate HASHES
    cords cord = ( y >= x ) ? ( y - x ) : ( x - y );  //Individual hash for node
    byte row = cord % HASHSIZE;                       //Hash for table
    byte column = bitIndetificator( y, x ).get();     //generate bit flags to variable flags os type union flags
    setHashTablePosition(column,row,file);            //Set position in hashtable

    position current;
    position temp;
    cords hash;
    do {        //Check pointer
        std::fread( &temp, sizeof( position ), 1, file );
        std::fread( &hash, sizeof( cords ), 1, file );
        if(hash==cord){
            //Reuse of temp. Other meaning. Sorry ;(
            std::fread( &temp, sizeof( position ), 1, file );
            std::fseek(memory,temp,SEEK_SET);
            memSize size;
            std::fread( &size, sizeof( memSize ), 1, memory);
            std::fread( buffer, size, 1, memory);
            return size;
        }else {
            std::fseek(file, temp, SEEK_SET);
        }
    }while ( temp != zero );
    return 0;
}
