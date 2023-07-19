#include <iostream>
#include "testlibforalt.h"
#include <cstring>


//int getJsonResult(const char* ,const char* , char* (*pf) (unsigned);

enum HelpNeeded{
    NO_ARGS,
    SAME_ARGS,
};

char* callback(unsigned);
void printHelp(HelpNeeded);

int main(int argc, char* argv[]){
    char* pRes=nullptr;
    // if no args
    if ( argc<3 ||  strlen(argv[1])== 0  || strlen(argv[2]) == 0 ) {
            printHelp(HelpNeeded::NO_ARGS);
            return 1;
    }
    // if same args
    if (strcmp(argv[1],argv[2])==0){
            printHelp(HelpNeeded::SAME_ARGS);
            return 1;
    }
    pRes=getJsonResult(argv[1],argv[2],callback);
    std::cout<<pRes;
    delete[] pRes;
    return 0;
}



char* callback(unsigned size){
    return new char[size];
}

void printHelp(HelpNeeded c){
    switch (c){
        case HelpNeeded::NO_ARGS:
             std::cerr<<"No args passed"<<std::endl;
            break;
        case HelpNeeded::SAME_ARGS:
             std::cerr<<"No sence to compare a branch with itself"<<std::endl;
        default:
            ;
    }
    std::cerr<<"Usage example:  ALT_Test1 branch1 branch2 >output.json"<<std::endl;
};
