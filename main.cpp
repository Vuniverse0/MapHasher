#include <iostream>//for debug
#include <fstream>// std::ifstream
#include <utility>//for pairs
#include <cstdio>//for working with files
#include <cstdint>//for fixed size integers
#include <filesystem>//for working with directory
#include <string>//for string
#include <cassert>//for assert
#include <bitset>//for bitset
#include <cstring>

#include "HashTable.h"
#include "OpenTable.h"
#include "functions.h"

namespace fs = std::filesystem;
typedef std::pair< uint32_t , uint32_t > fnameNs;

static inline void clearPath( std::string& s )
{
    auto it = s.begin();
    for ( auto i = s.begin(); i != s.end(); i++ ){
        if ( (*i) == '/' ){
            it = i;
        }
    }
    s.erase( s.begin(), it+1);
}
static fnameNs ParseName(std::string s )
{
    return {
        static_cast<uint32_t>( std::stoul( s.substr( s.find('y') + 1, s.find('x') ) ) ) ,
        static_cast<uint32_t>( std::stoul( s.substr( s.find('x') + 1, s.find('y', s.find('x' ) ) ) ) )
    };
}
static uint16_t GetDebugSize( std::string s )
{
    return  static_cast<uint32_t>( std::stoul( s.substr( 0, s.find(' ') ) ) );
}
int WriteDatabase(const std::string& dir = "/home/vuniverse/CLionProjects/CordsSorter/Data")
{
    HashTable table;
    fnameNs path;

    for ( auto& item:fs::directory_iterator( dir ) ){
        std::string s = item.path() ;
        uint16_t size = std::filesystem::file_size( s );
        path = ParseName( s );
        std::FILE *file = std::fopen( s.c_str(), "rb");

        std::cout << "Y: " << path.first << " X: " << path.second << std::endl;
        std::cout << "Try to write file " << s << std::endl;

        table.write( path.first, path.second, size, file);
        std::fclose( file );
    }
    return 0;
}
static char* ReadDataBase( std::string name ){
    static OpenTable table;
    fnameNs path = ParseName( name );
    return table.getData( path.first, path.second);
}
int writeTest()
{
    HashTable table;
    fnameNs path;
    std::ifstream file("/home/vuniverse/namesAndSizes");
    std::string str;
    getline(file,str);

    for (int i=0;i<100;i++){
        getline(file,str);
        path = ParseName(str);
        uint16_t size = GetDebugSize( str );

        std::cout << "Y: " << path.first << " X: " << path.second << std::endl;
        std::cout << "Try to open file " << str << std::endl;

        table.write( path.first, path.second, size, nullptr);

        std::cout << "\n\n" << std::endl;
    }
    return 0;
}
static int readTest(){
    OpenTable table;
    fnameNs path;
    std::string str;

    std::ifstream file("/home/vuniverse/namesAndSizes");
    getline(file,str);

    for (int i=0;i<100;i++){

        getline(file,str);
        path = ParseName(str);

        std::cout << "Try to read " << str << std::endl;
        std::cout << "Y: " << path.first << " X: " << path.second << std::endl;

        char* result = table.getData( path.first, path.second);
        uint16_t size = GetDebugSize( str );

        std::cout << "Size from table: " << ( std::strlen( result ) ) << std::endl;
        std::cout << "Native size: " << ( ( int ) size ) << "\n\n" << std::endl;
        if( std::strlen( result ) != size ){
            std::cerr << "DOESNT EQUAL!!!" << std::endl;
            exit( 1 );
        }

    }
    return 0;
}
int main(int argc, char *argv[])
{
    FILE* file1 = fopen("/home/vuniverse/CLionProjects/CordsSorter/Data/y929999x1029y120z10","wb");
    char buff[] = "0102";
    fwrite(&buff,4,1,file1);
    fclose(file1);
    file1 = fopen("/home/vuniverse/CLionProjects/CordsSorter/Data/y929999x1029y120z10","rb");
    fread(&buff,4,1,file1);
    fclose(file1);
    std::cout<< buff << std::endl;
    WriteDatabase();
    char* data = ReadDataBase("y929999x1029y120z10" );
    std::cout<< data << std::endl;
    return 0;
}