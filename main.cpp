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
typedef std::pair<uint32_t,uint32_t> fnameNs;
static void deleteFile(std::string st="0",bool i= true){
    static std::string s;
    if(i){
        assert(remove(s.c_str())==0);
    } else{
        s=st;
    }
}
static inline void clearPath(std::string& s)
{
    deleteFile(s, false);
    auto it=s.begin();
    for(auto i = s.begin();i!=s.end();i++){
        if((*i)=='/'){
            it=i;
        }
    }
    s.erase(s.begin(),it+1);
}
static fnameNs GetFileName(std::string&& s)
{
    clearPath(s);
    uint8_t a=0;
    uint8_t b=0;
    for(auto i = 0;i!=s.size();i++){
        if(s[i]=='x'){
            a=i;
        }
    }
    for(auto i = a;i!=s.size();i++){
        if(s[i]=='y'){
            b=i;
        }
    }
    uint32_t sub1 = static_cast<uint32_t>(std::stoul(s.substr(1,a)));
    uint32_t sub2 = static_cast<uint32_t>(std::stoul(s.substr(a+1, b)));
    return  {sub1,sub2};
}

int main() {
    HashTable table;
    fnameNs path;
    for(auto& item:fs::directory_iterator("/home/vuniverse/CLionProjects/CordsSorter/Data")){
        path=GetFileName(item.path());
        std::cout<<"Y: "<<path.first<<" X: "<<path.second<<std::endl;
        std::string s=item.path();
        std::cout<<"Try to open file "<<s<<std::endl;
        FILE *file = fopen( s.c_str(), "rb");
        std::cout<<"Open successful, try to read"<<std::endl;
        table.write(path.first,path.second,file);
        std::cout<<"Successful, go next file"<<std::endl;
        fclose(file);
    }
    std::cout<<"Successful"<<std::endl;
    return 0;
}
/*
   fnameNs path;
    for(auto& item:fs::directory_iterator("/home/vuniverse/CLionProjects/CordsSorter/Data")){
        path=GetFileName(item.path());
        std::cout << path.first << " x: " << path.second << std::endl;
    }
    std::bitset<3> hashSet{"101"};
    uint8_t a= hashSet.to_ulong();
    //std::cout<<((int)a)<<std::endl;
    FILE* file;
    FILE* file1;
    file=fopen("/home/vuniverse/CLionProjects/CordsSorter/Output/Testes","ab+");
    file1=fopen("/home/vuniverse/CLionProjects/CordsSorter/Output/Teste","ab+");
    uint64_t test = 45;
    //std::cout<<((int)test)<<std::endl;
    fwrite(&test,sizeof(uint64_t),1,file);
    fwrite(&test,sizeof(uint64_t),1,file1);
    fseek(file, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(file);
    fseek(file,0,SEEK_SET);
    fseek(file1,0,SEEK_SET);
    for(auto i=0;i<(len/sizeof(uint64_t));i++){
        fpos_t nodepos;
        fgetpos(file,&nodepos);
        std::cout<<"Position "<<nodepos.__pos<<" Number:";
        uint64_t n;
        fread(&n,sizeof(uint64_t),1,file);
        std::cout<<((unsigned int)n)<<std::endl;
    }
    std::cout<<"\nDelay\n"<<std::endl;
    for(auto i=0;i<(len/sizeof(uint64_t));i++){
        fpos_t nodepos;
        fgetpos(file1,&nodepos);
        std::cout<<"Position "<<nodepos.__pos<<" Number:";
        uint64_t n;
        fread(&n,sizeof(uint64_t),1,file1);
        std::cout<<((unsigned int)n)<<std::endl;
    }
    fclose(file);
    fclose(file1);
 */