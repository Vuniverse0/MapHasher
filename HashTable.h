//
// Created by vuniverse on 8/21/21.
//

#ifndef CORDSSORTER_HASHTABLE_H
#define CORDSSORTER_HASHTABLE_H

#include <cstdio>//for working with files
#include <cstdint>//for fixed size integers
#include <cassert>//for assert
#include <iostream>//for cout

#define HASHSIZE 255
#define BITSVARIATIONS 8
typedef std::uint8_t byte;
typedef std::uint16_t memSize;
typedef std::uint32_t cords;
typedef std::uint64_t position;


struct HashTable {
    HashTable();
    ~HashTable();
    void write( const cords& y ,const cords& x, FILE* data );
private:
    position zero = 0;
    FILE* file;
    FILE* memory;
    position writeData(const memSize& size, FILE* data);
    static inline memSize getFileSize(FILE* data);
    static const inline void checkPosition(FILE* file);
    struct bitIndetificator {
        bitIndetificator( const cords& y, const cords& x );
        byte get();
    private :
        union {
            byte hash;
            struct {
                byte yHx : 1;
                byte y : 1;
                byte x : 1;
            };
        } flags;
    };
};


#endif //CORDSSORTER_HASHTABLE_H
