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

}
int OpenTable::getData( char *buffer )
{
    return 0;
}
