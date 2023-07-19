#include "getPackageMap.h"
#include <json11.hpp>
#include <iostream>

// parses json string to map of objects
std::unique_ptr<RootMap> getPackageMap(const std::string& jsonStr, const std::string& branch){
    std::string err;
    const json11::Json jsonResponseObject = json11::Json::parse(jsonStr, err);
    std::cerr<<"Packages found in branch "<<branch<<" = "<<jsonResponseObject["length"].int_value()<<std::endl;
    const std::vector<json11::Json>& packagesArr=jsonResponseObject["packages"].array_items();


    // map contains arch -> map, each submap contains name - > package multimap (just in case repo has some package with same names)
    std::unique_ptr<RootMap> prootMap(new RootMap());

    // create map
    for (auto it=packagesArr.begin();it!=packagesArr.end();++it){
        // create object package
        Package p((*it)["name"].string_value(),
                  (*it)["version"].string_value(),
                  (*it)["release"].string_value(),
                  (*it)["arch"].string_value(),
                  (*it)["epoch"].int_value(),
                  (*it)["disttag"].string_value(),
                  (*it)["buildtime"].int_value(),
                 (*it)["source"].string_value());



        // create architecture in map if not exists
        prootMap->emplace(p.arch,std::unordered_map<std::string, Package>() );
        // push object to submap
        (*prootMap)[p.arch].emplace(p.name,p);
    }
    int mappedCount{0};
    for (auto it= prootMap->cbegin(); it != prootMap->cend(); ++it){
        mappedCount+=it->second.size();
    }

    std::cerr<<"Mapped " << mappedCount << " objects from " << packagesArr.size() << std::endl;
    std::cerr<<"..."<<std::endl;
    return prootMap;
}
