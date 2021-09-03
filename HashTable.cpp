//
// Created by vuniverse on 9/1/21.
//

#include "HashTable.h"
#include "FileMacro&Aliases.h"
memSize getFileSize(FILE * data);
 HashTable::HashTable()
 {
     /* Hash Table:         Columns:8
     *
     *     Rows: 255     Start node of singly linked list
     *
     *     Every info node have pointer(position in file) to next info node that should be in table
     *     Start node have only position without info
     *
     *     Every info node have structure like this:
     *          Pointer to position of next node. Can also be pointer to end iterator or non valid
     *
     */
    file = std::fopen( "/home/vuniverse/CLionProjects/CordsSorter/Output/hashes", "wb+" );
    memory = std::fopen("/home/vuniverse/CLionProjects/CordsSorter/Output/values", "wb" );
    checkPosition(memory );
    std::fwrite(&zero, sizeof( position ), 1, memory);
    checkPosition(memory );
    memSize i=0;
    do {
        std::fwrite(&zero, sizeof(position), 1, file);
        i++;
    } while (i != HASHSIZE * 8);
    std::cout << "Successful, files was opened. Data Hashes: "<<( ( int ) i );
    std::cout << " (" << HASHSIZE << " * " << (i / HASHSIZE) << " )" << std::endl;
}

HashTable::~HashTable()
{
    std::fclose( file );
    std::fclose( memory );
    std::cout << "Successful, files was closed" << std::endl;
}

void HashTable::write( const cords& y ,const cords& x, FILE* data )
{
    //Generate HASHES
    cords cord = ( y >= x ) ? ( y - x ) : ( x - y );  //Individual hash for node
    byte row = cord % HASHSIZE;                       //Hash for table
    byte column = bitIndetificator( y, x ).get();            //generate bit flags to variable flags os type union flags

    memSize size=getFileSize(data );      //Get data file size

    position pos=writeData( size, data );//Got data position end write data

    std::cout << "Cords generated: " << ( ( int ) cord ) << std::endl;
    std::cout << "Hash generated: " << ( ( int ) row ) << std::endl;
    std::cout << "Set flags: " << ( ( int ) column ) << std::endl;
    std::cout << "Data size generated: " << ( ( int ) size ) << std::endl;
    std::cout << "Data position : " << pos << std::endl;

    std::fseek( file, 0, SEEK_END );//Go to end of info file
    position nodepos = static_cast<unsigned long>( ftell( file ) );
    std::cout << "Current Position of node " << nodepos << std::endl;

    //Data info
    int dbg1 = std::fwrite( &zero, sizeof( position ), 1, file); //Pointer to next node of data info
    int dbg2 = std::fwrite( &cord, sizeof( cords ), 1, file );          //Individual no collision hash
    int dbg3 = std::fwrite( &pos, sizeof( position ), 1, file );     //Data position in data file

    //Write data info to hash file
    std::cout << "Writen:\n "<<( dbg1 * sizeof( position ) ) << " bytes of next pointer\n";    //Next
    std::cout << ( dbg2 * sizeof( cords ) ) << " bytes of cords\n";                            //Cords
    std::cout << ( dbg3 * sizeof( position ) ) << " bytes of pointer to data" << std::endl;    //Data position

    std::cout << "Bits: " << ( ( int ) column ) << " Hash: " << ( ( int ) row ) << std::endl;
    position hashtablePosition = ( column * sizeof( position ) ) + ( row * BITSVARIATIONS * sizeof( position ) );
    std::fseek( file, hashtablePosition, SEEK_SET ); //Set position in hashtable

    checkPosition( file );

    position current;
    position temp;
    do {        //Check pointer
        current = static_cast< unsigned long >( std::ftell( file ) );
        std::fread( &temp, sizeof( position ), 1, file );

        checkPosition( file );
        std::cout << "Now: " << ( ( int ) current ) << std::endl;
        std::cout << "Temp: " << ( ( int ) temp ) << std::endl;
        std::fseek( file, temp, SEEK_SET );
    }while ( temp != zero );
    std::cout << "Try to write node position: " << ( ( int ) nodepos ) << std::endl;

    std::fseek( file, current, SEEK_SET );
    int debag = std::fwrite( &nodepos, sizeof( position ), 1, file);
    std::fseek(file,current,SEEK_SET);
    std::cout << ( debag * sizeof( position ) ) << " bytes of position was writen" << std::endl;
    checkPosition( file );
    std::fread( &temp, sizeof( position ), 1, file);
    std::cout << "Now pointed to " << ( ( int ) temp ) << " Break;" << std::endl;

    std::cout << "Data writen\n\n\n" << std::endl;

}
position HashTable::writeData(const memSize& size, FILE* data)
{
    checkPosition(memory);
    position temporalityPosition=static_cast< unsigned long >( std::ftell( memory ) );
    char* buff;
    std::fread(buff, 1, size, data);
    std::fwrite( &size, sizeof( memSize ), 1, memory );
    std::fwrite( buff, 1, size, memory );
    return temporalityPosition;
}

const inline void HashTable::checkPosition(FILE* file)
{
    position pos=static_cast< unsigned long >( ftell( file ) );
    std::cout<<"Current position : "<<pos<<std::endl;
}

HashTable::bitIndetificator::bitIndetificator( const cords& y, const cords& x )
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

byte HashTable::bitIndetificator::get() const
{
    return flags.hash;
}