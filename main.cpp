#include <iostream>//for debug
#include <fstream>// std::ifstream
#include <utility>//for pairs
#include <cstdio>//for working with files
#include <cstdint>//for fixed size integers
#include <filesystem>//for working with directory
#include <string>//for string
#include <cassert>//for assert
#include <bitset>//for bitset

#include "HashTable.h"
#include "OpenTable.h"

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
static fnameNs GetFileName( std::string s )
{
    //clearPath(  s ); comented for debug
    uint8_t a = 0;
    uint8_t b = 0;
    uint8_t test=0;
    test=s.find(' ');
    a = s.find('x');
    for (auto i = a;i!=s.size();i++){
        if ( s[i] == 'y' ){
            b = i;
        }
    }
    uint32_t sub1 = static_cast<uint32_t>( std::stoul( s.substr( test+2, a ) ) );
    uint32_t sub2 = static_cast<uint32_t>( std::stoul( s.substr( a + 1, b ) ) );
    return  { sub1 , sub2 };
}
static uint16_t GetDebugSize( std::string s )
{
    uint8_t test=0;
    test=s.find(' ');
    uint16_t sub1 = static_cast<uint32_t>( std::stoul( s.substr( 0, test ) ) );
    std::cout << "Emulated Size " << s.substr( 0, test ) << std::endl;
    return  sub1;
}
int WriteDatabase()
{
    HashTable table;
    fnameNs path;
    for ( auto& item:fs::directory_iterator( "/home/vuniverse/CLionProjects/CordsSorter/Data" ) ){
        path = GetFileName(item.path());
        std::cout << "Y: " << path.first << " X: " << path.second << std::endl;
        std::string s=item.path();
        std::cout << "Try to open file " << s << std::endl;
        std::FILE *file = std::fopen( s.c_str(), "rb");
        std::cout << "Open successful, try to read" << std::endl;
        table.write( path.first, path.second, file );
        std::cout << "Successful, go next file" << std::endl;
        std::fclose( file );
    }
    return 0;
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
        std::cout << "Try to open file " << str << std::endl;
        path = GetFileName( str );
        uint16_t size = GetDebugSize( str );
        std::cout << "Y: " << path.first << " X: " << path.second << std::endl;
        std::cout << "Try to open file " << str << std::endl;
        std::FILE *file = std::fopen( str.c_str(), "wb");
        std::cout << "Open successful, try to read" << std::endl;
        table.write( path.first, path.second, file , size);
        std::cout << "Successful, go next file\n\n" << std::endl;
        std::fclose( file );
    }
    return 0;
}
static int readTest(){
    fnameNs path;
    std::ifstream file("/home/vuniverse/namesAndSizes");
    std::string str;
    getline(file,str);
    OpenTable table;
    for (int i=0;i<100;i++){
        getline(file,str);
        std::cout << "Try to read " << str << std::endl;
        path = GetFileName( str );
        std::cout << "Y: " << path.first << " X: " << path.second << std::endl;
        std::cout << "Try to open file FOR READ " << str << std::endl;
        //std::FILE *file = std::fopen( str.c_str(), "wb");
        char* buff;
        uint16_t result = table.getData( path.first, path.second, buff);
        std::cout << "Size : " << result << "\n\n" << std::endl;
        //std::fclose( file );
    }
    return 0;
}
int main()
{
    std::ifstream file("/home/vuniverse/namesAndSizes");
    std::string str;
    for(int i=0;i<10;i++){
        getline(file,str);
        std::cout<<str<<std::endl;
    }
    writeTest();
    readTest();
    return 0;
}