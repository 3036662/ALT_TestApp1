//#include <stdio.h>
//#include <curl/curl.h>
#include <string>
#include <iostream>
//#include <json11.hpp>
//#include <unordered_map>



#include "Package.h"
#include "CurlWrapper.h"
#include "getPackageMap.h"

const char* branch1="p10";
const char* branch2="p9";

int main(void)
{


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


    char tmp;
   std::cin>>tmp;
  return 0;
}
