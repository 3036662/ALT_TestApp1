#include <string>
#include <iostream>
#include <cstring>

#include "Package.h"
#include "CurlWrapper.h"
#include "getPackageMap.h"
#include "SortMap.h"

//const char* branch1="p10";
//const char* branch2="p9";
extern "C"{
    char* getJsonResult(const char* ,const char* , char* (*pf) (unsigned) );
}


char*  getJsonResult(const char* branch1,const char* branch2,char* (*pf) (unsigned)){


    std::string* pjsonString1=new std::string{};
    std::string* pjsonString2=new std::string{};
    { //separate scope just to destroj CurlWrapper when not needed
        CurlWrapper curlw{};
        *pjsonString1=curlw.perfomReq(branch1);
        *pjsonString2=curlw.perfomReq(branch2);
    }
    // creating object maps for two branches
    std::unique_ptr<RootMap> branch1Map=getPackageMap(*pjsonString1,branch1);
    delete pjsonString1;
    std::unique_ptr<RootMap> branch2Map=getPackageMap(*pjsonString2,branch2);
    delete pjsonString2;



     char*  ptr_to_buffer=nullptr;
    // sort Maps{
    {
    std::string resJsonString;
    SortMap sm(branch1Map.get(),branch2Map.get());

    sm.findMissingInSecond();
    sm.findMissingInFirst();
    sm.findVersionOrReleaseNewer();
    branch1Map.reset();
    branch2Map.reset();
    resJsonString=sm.getJsonResponse();
    ptr_to_buffer=pf(resJsonString.size()+1); //get buffer from callback
    if (ptr_to_buffer) strcpy(ptr_to_buffer,resJsonString.c_str()); // copy string to buffer
    }
    return ptr_to_buffer; // pointer res buffer

}
