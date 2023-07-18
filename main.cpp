#include <string>
#include <iostream>


#include "Package.h"
#include "CurlWrapper.h"
#include "getPackageMap.h"
#include "SortMap.h"

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

    // sort Maps
    SortMap sm(branch1Map.get(),branch2Map.get());

    sm.findMissingInSecond();
    sm.findMissingInFirst();

    char tmp;
   std::cin>>tmp;
  return 0;
}
