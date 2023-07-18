//#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <json11.hpp>
#include <unordered_map>



#include "Package.h"
#include "CurlWrapper.h"


int main(void)
{


    CurlWrapper curlw{};
    const std::string& readBuffer=curlw.perfomReq("p10");


    // json response parse
    std::string err;
    const json11::Json jsonResponseObject = json11::Json::parse(readBuffer, err);
    std::cerr<<"Packages found in branch "<<jsonResponseObject["length"].int_value()<<std::endl;

    std::vector<json11::Json> packagesArr=jsonResponseObject["packages"].array_items();


    // map contains arch -> map, each submap contains name - > package multimap (just in case repo has some package with same names)
    std::unordered_map <std::string, std::unordered_multimap <std::string, Package>> rootMap;
    // create map
    for (auto it=packagesArr.begin();it!=packagesArr.end();++it){
        // create object package
        Package p((*it)["name"].string_value(),
                  (*it)["version"].string_value(),
                  (*it)["release"].string_value(),
                  (*it)["arch"].string_value(),
                  (*it)["epoch"].int_value());


        // create architecture in map if not exists
        rootMap.emplace(p.arch,std::unordered_multimap<std::string, Package>() );
        // push object to submap
        rootMap[p.arch].emplace(p.name,p);
    }
    int mappedCount{0};
    for (auto it= rootMap.cbegin(); it != rootMap.cend(); ++it){
        mappedCount+=it->second.size();
    }

    std::cerr<<"Mapped " << mappedCount << " objects from " << packagesArr.size() << std::endl;



  return 0;
}
