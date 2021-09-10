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
#include "functions.h"

namespace fs = std::filesystem;
typedef std::pair< uint32_t , uint32_t > fnameNs;

static fnameNs ParsePath(std::string s , bool IsntPath=false)
{
    if(!IsntPath) {
        auto it = s.begin();
        for (auto i = s.begin(); i != s.end(); i++) {
            if ((*i) == '/') {
                it = i;
            }
        }
        s.erase(s.begin(), it + 1);
    }
    return {
        static_cast<uint32_t>( std::stoul( s.substr( 1, s.find('x') ) ) ) ,
        static_cast<uint32_t>( std::stoul( s.substr( s.find('x') + 1 ) ) )
    };
}
static int GetData( std::string& s )
{
    static OpenTable table;
    fnameNs path = ParsePath( s, true );
    char* buff;
    uint16_t temp = table.getData(path.first, path.second,buff);
    s=buff;
    return temp;
}
int WriteDatabase( const std::string& dir = "/home/vuniverse/CLionProjects/CordsSorter/Data" )
{
    HashTable table;
    fnameNs path;

    for ( auto& item:fs::directory_iterator( dir ) ){
        std::string s=item.path();
        uint16_t size = std::filesystem::file_size(s);
        std::FILE *file = std::fopen( s.c_str(), "rb");

        path = ParsePath(s);
        table.write( path.first, path.second, size, file);
        std::fclose( file );
    }
    return 0;
}
int main(int argc, char *argv[])
{
    //std::cout<< *argv << std::endl;

    WriteDatabase();
    std::string str;
    while ( std::cin >> str ){
        GetData( str );
        std::cout << "Out: " << str << std::endl;
    }

    return 0;
}