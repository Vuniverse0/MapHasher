#include <iostream>//for debug
#include <utility>//for pairs
#include <cstdio>//for working with files
#include <cstdint>//for fixed size integers
#include <filesystem>//for working with directory
#include <string>//for string
#include <cassert>//for assert
#include <bitset>//for bitset

#include "HashTable.h"

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
static fnameNs GetFileName( std::string&& s )
{
    clearPath(  s );
    uint8_t a = 0;
    uint8_t b = 0;
    for ( auto i = 0; i != s.size(); i++ ){
        if ( s[i] == 'x' ){
            a = i;
        }
    }
    for (auto i = a;i!=s.size();i++){
        if ( s[i] == 'y' ){
            b = i;
        }
    }
    uint32_t sub1 = static_cast<uint32_t>( std::stoul( s.substr( 1, a ) ) );
    uint32_t sub2 = static_cast<uint32_t>( std::stoul( s.substr( a + 1, b ) ) );
    return  { sub1 , sub2 };
}

int main()
{
    HashTable table;
    fnameNs path;
    for ( auto& item:fs::directory_iterator( "/home/vuniverse/CLionProjects/CordsSorter/Data" ) ){
        path = GetFileName( item.path() );
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