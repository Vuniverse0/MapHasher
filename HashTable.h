//
// Created by vuniverse on 8/21/21.
//

#ifndef CORDSSORTER_HASHTABLE_H
#define CORDSSORTER_HASHTABLE_H

#include <cstdio>//for working with files
#include <bitset>//for bitset
#include <cstdint>//for fixed size integers
#include <cassert>//for assert

#define HASHSIZE 255
#define AVGHASHSIZE (HASHSIZE/2)
typedef uint8_t hashType;
typedef uint16_t dataSize;
typedef uint32_t cords;
typedef fpos_t pointerSize;
typedef std::bitset<3>  flags;
static pointerSize zero[8];
class HashTable {
    FILE* file;
    FILE* DATAfile;
    static flags generateBitset(const cords& y,const cords& x)
    {
        std::bitset<3> hashSet{"000"};
        if(y>=x){
            hashSet.set(0,true);
        }
        if(y%2==0){
            hashSet.set(3,true);
        }
        if(x%2==0){
            hashSet.set(2,true);
        }
        return hashSet;
    }
    pointerSize DATA(dataSize size,FILE* data)
    {
        pointerSize temp;
        fgetpos(DATAfile,&temp);
        char* buff;
        fread(buff,1,size,file);
        fwrite(&size, sizeof(dataSize), 1, DATAfile);
        fwrite(buff, 1,size, DATAfile);
        return temp;
    }
    inline void goHashPointer(flags f,hashType h)
    {
        hashType n= f.to_ulong();//Bitset to the nubmer
        std::cout<<"Bitset Clasificator: "<<((int)n)<<std::endl;
        std::cout<<"Hash "<<((int)h)<<std::endl;
        n=(n*16)+(h*8*16);
        fseek(file,n, 0);//Go to pointer
    }
    static inline cords generateHash(const cords& y,const cords& x)
    {
        return (y>=x)?(y-x):(x-y);
    }
    static inline hashType generateHashIndex(const cords& hash)
    {
        return hash%HASHSIZE;
    }
    static inline dataSize gotSize(FILE* data)
    {
        fseek(data, 0, SEEK_END);
        std::cout<<"Data size:"<<(unsigned long)ftell(data)<<std::endl;
        return (unsigned long)ftell(data);
    }
    public:
    HashTable()
    {
        for(uint8_t i=0;i<8;i++)
            zero[i].__pos=-1;
        file=fopen("/home/vuniverse/CLionProjects/CordsSorter/Output/hashes","ab+");
        DATAfile=fopen("/home/vuniverse/CLionProjects/CordsSorter/Output/values","ab+");
        uint8_t i=0;
        do{
            fwrite(&zero,sizeof(pointerSize),8,file);
            i++;
        }while(i != HASHSIZE);
        std::cout<<"Successful, files was opened"<<std::endl;
    }
    ~HashTable()
    {
        fclose(file);
        fclose(DATAfile);
        std::cout<<"Successful, files was closed"<<std::endl;
    }
    void write(const cords& y,const cords& x,FILE* data)
    {
        //Generate HASHES
        std::cout<<"Start generate hashes "<<std::endl;
        flags f=generateBitset(y,x);
        std::cout<<"Flags generated"<<std::endl;
        cords c=generateHash(y,x);
        std::cout<<"Hash cords generated: "<<((int)c)<<std::endl;
        hashType h=generateHashIndex(c);
        std::cout<<"Index hash generated: "<<((int)h)<<std::endl;
        dataSize size=gotSize(data);//Got size of datafile
        std::cout<<"Data size generated: "<<((int)size)<<std::endl;
        pointerSize pos=DATA(size,data);//Got data position end write data
        std::cout<<"Data position : "<<pos.__pos<<std::endl;

        //Got Current position
        fseek(file,0,SEEK_END);
        pointerSize nodepos;
        fgetpos(file,&nodepos);
        std::cout<<"Current Position of node "<<nodepos.__pos<<std::endl;
        std::cout<<"Writing data..."<<std::endl;
        //Write data info to hash file
        std::cout<<"Writen:\n "<<(fwrite(&zero,sizeof(pointerSize),1,file)*sizeof(pointerSize))<<" bytes of next pointer\n";//Next
        std::cout<<(fwrite(&c,sizeof(cords),1,file)*sizeof(cords))<<" bytes of cords\n";//Cords
        std::cout<<(fwrite(&pos,sizeof(pointerSize),1,file)*sizeof(pointerSize))<<" bytes of pointer to data"<<std::endl;//Data position
        goHashPointer(f,h);//Go to hash
        pointerSize temp;
        pointerSize tp;
        while(true) {        //Check pointer
            fgetpos(file,&tp);//GET POSITION WHERE WE ARE
            std::cout<<"On hash position "<<tp.__pos<<std::endl;

            fread(&temp, sizeof(pointerSize), 1, file);//GET WHAT WRITEN ON THIS POSITION
            pointerSize tp111;
            fgetpos(file,&tp111);
            std::cout<<"On hash position NOW "<<tp111.__pos<<std::endl;
            if (temp.__pos == -1) {
                std::cout<<"Not valid, pointer is clear "<<temp.__pos<<std::endl;

                fsetpos(file,&tp);
                fgetpos(file,&tp);
                std::cout<<"On hash position "<<tp.__pos<<std::endl;

                std::cout<<"Try to write node position: "<<nodepos.__pos<<std::endl;
                std::cout<<(fwrite(&nodepos, sizeof(pointerSize), 1, file)*sizeof(pointerSize))<< " bytes of position was writen"<<std::endl;
                fgetpos(file,&tp);//GET POSITION WHERE WE ARE
                std::cout<<"On hash position "<<tp.__pos<<std::endl;
                fsetpos(file,&tp);

                fread(&temp, sizeof(pointerSize), 1, file);
                std::cout<<"Now pointed to "<<temp.__pos<<std::endl;
                break;
            } else {
                std::cout<<"Temp valid "<<temp.__pos<<std::endl;
                std::cout<<"Go next position "<<std::endl;
                fsetpos(file,&temp);
                //fread(&temp, sizeof(pointerSize), 1, file);
            }
        }
        uint8_t i=0;
        do{
            fwrite(&temp,sizeof(pointerSize),8,file);
            std::cout<<"I: "<<((int)i)<<" Point to "<<temp.__pos<<std::endl;
            i++;
        }while(i != HASHSIZE);
        fseek(file,sizeof(cords),SEEK_END);
        std::cout<<"Data writen\n\n\n\n"<<std::endl;

    }
};


#endif //CORDSSORTER_HASHTABLE_H
