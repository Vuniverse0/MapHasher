//
// Created by vuniverse on 8/21/21.
//

#ifndef CORDSSORTER_HASHTABLE_H
#define CORDSSORTER_HASHTABLE_H

#include <cstdio>//for working with files
#include <cstdint>//for fixed size integers
#include <cassert>//for assert

#define HASHSIZE 255
#define AVGHASHSIZE (HASHSIZE/2)
typedef std::uint8_t hashType;
typedef std::uint16_t dataSize;
typedef std::uint32_t cords;
typedef std::uint64_t pointerSize;
union flags{
    hashType hash;
    struct {
        hashType yHx: 1;
        hashType y: 1;
        hashType x: 1;
    };
};
struct bitIndetificator{
    bitIndetificator(const cords& y, const cords& x){
        f.hash=0;
        if(y>=x){
            f.yHx=1;
        }
        if(y%2==0){
            f.y=1;
        }
        if(x%2==0){
            f.x=1;
        }
        hashType P =  f.hash;
        std::cout<<"Generates bitset eqality to: " << ((int)P) << std::endl;
        std::cout<<"        first bit: " << (y>=x) << std::endl;
        std::cout<<"       second bit: " << (y%2==0) << std::endl;
        std::cout<<"        third bit: " << (x%2==0) << std::endl;
    }
    hashType get()
    {
        return f.hash;
    }
private:
    flags f;
};
struct HashTable {
    HashTable()
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
        file=fopen("/home/vuniverse/CLionProjects/CordsSorter/Output/hashes","wb+");//info file :
        DATAfile=fopen("/home/vuniverse/CLionProjects/CordsSorter/Output/values","wb+");
        fwrite(&zero,sizeof(pointerSize),1,DATAfile);
        fseek(DATAfile,sizeof(pointerSize),SEEK_CUR);
        uint16_t i=0;
        do{
            fwrite(&zero,sizeof(pointerSize),1,file);
            fseek(file,sizeof(pointerSize),SEEK_CUR);
            i++;
        }while(i != HASHSIZE*8);
        std::cout<<"Successful, files was opened. Data Hashes: "<<((int)i)<<" ("<<HASHSIZE<<" * "<<(i/HASHSIZE)<<" )"<<std::endl;
        /*pointerSize temp;
        uint16_t a=0;
        fwrite(&temp,sizeof(pointerSize),1,file);
        std::cout<<"A: "<<((int)a)<<" Point to "<<temp<<std::endl;
        do{
            a++;
            fwrite(&temp,sizeof(pointerSize),8,file);
            std::cout<<"A: "<<((int)a)<<" Point to "<<temp<<std::endl;
        }while(a != HASHSIZE*8);*/
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
        hashType n=generateHash(y,x);//generate bit flags to variable flags os type union flags

        cords c=generateHash(y,x);//Individual hash for node

        hashType h=generateHashIndex(c);//Hash for table

        dataSize size=getFileSize(data);//Get data file size

        pointerSize pos=writeData(size,data);//Got data position end write data

        std::cout<<"Hash cords generated: "<<((int)c)<<std::endl;
        std::cout<<"Index hash generated: "<<((int)h)<<std::endl;
        std::cout<<"Data size generated: "<<((int)size)<<std::endl;
        std::cout<<"Data position : "<<pos<<std::endl;

        fseek(file,0,SEEK_END);//Go to end of info file
        pointerSize nodepos=(unsigned long)ftell(file);
        std::cout<<"Current Position of node "<<nodepos<<std::endl;

        //Data info
        int dbg1=fwrite(&zero,sizeof(pointerSize),1,file);//Pointer(position of) to next node of data info
        int dbg2=fwrite(&c,sizeof(cords),1,file);//Individual no collision hash
        int dbg3=fwrite(&pos,sizeof(pointerSize),1,file);//Data position in data file

        //Write data info to hash file
        std::cout<<"Writen:\n "<<(dbg1*sizeof(pointerSize))<<" bytes of next pointer\n";//Next
        std::cout<<(dbg2*sizeof(cords))<<" bytes of cords\n";//Cords
        std::cout<<(dbg3*sizeof(pointerSize))<<" bytes of pointer to data"<<std::endl;//Data position

        setHashTablePosition(h,n);//Go to cell in table
        pointerSize temp;
        while(true) {        //Check pointer
            fread(&temp,sizeof(pointerSize),1,file);
            checkPosition(file);//DEBUG
            if (temp == 0) {
                std::cout<<"Not valid, pointer is clear. Value: "<<((int)temp)<<std::endl;
                std::cout<<"Try to write node position: "<<((int)nodepos)<<std::endl;
                int debag=fwrite(&nodepos, sizeof(pointerSize), 1, file);
                std::cout<<(debag*sizeof(pointerSize))<< " bytes of position was writen"<<std::endl;
                checkPosition(file);
                fread(&temp, sizeof(pointerSize), 1, file);
                std::cout<<"Now pointed to "<<((int)temp)<<" Break;"<<std::endl;
                break;
            } else {
                std::cout<<"Temp valid "<<((int)temp)<<std::endl;
                std::cout<<"Go next position "<<std::endl;
                fseek(file,temp,SEEK_SET);
            }
        }
        fseek(file,0,SEEK_END);
        std::cout<<"Data writen\n\n\n\n"<<std::endl;

    }
private:
    pointerSize zero=0;
    FILE* file;
    FILE* DATAfile;
    static hashType generateBitset(const cords& y,const cords& x)
    {
        bitIndetificator bitset(y,x);
        return bitset.get();
    }
    pointerSize writeData(dataSize size,FILE* data)
    {
        pointerSize temp=(unsigned long)ftell(data);
        char* buff;
        fread(buff,1,size,data);
        fwrite(&size, sizeof(dataSize), 1, DATAfile);
        fwrite(buff, 1,size, DATAfile);
        return temp;
    }
    inline void setHashTablePosition(hashType h,hashType n)//Set position in file to hash
    {
        std::cout<<"rows: "<<((int)n)<<" columns: "<<((int)h)<<std::endl;
        pointerSize temp=(n*sizeof(pointerSize))+(h*8*sizeof(pointerSize));//Get columns and get cell position
        fseek(file,temp,SEEK_SET);// to cell
        checkPosition(file);
    }
    static inline cords generateHash(const cords& y,const cords& x)
    {
        return (y>=x)?(y-x):(x-y);
    }
    static inline hashType generateHashIndex(const cords& hash)
    {
        return hash%HASHSIZE;
    }
    static inline dataSize getFileSize(FILE* data)
    {
        fseek(data, 0, SEEK_END);
        std::cout<<"Data size:"<<(unsigned long)ftell(data)<<std::endl;
        return (unsigned long)ftell(data);
    }
    static const inline void checkPosition(FILE* file)
    {
        uint64_t pos=(unsigned long)ftell(file);
        std::cout<<"Current position : "<<pos<<std::endl;
    }


};


#endif //CORDSSORTER_HASHTABLE_H
