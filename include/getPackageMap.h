#ifndef GETPACKAGEMAP_H
#define GETPACKAGEMAP_H
#include <unordered_map>
#include <string>
#include <memory>


#include "Package.h"


typedef std::unordered_map <std::string, std::unordered_multimap <std::string, Package>>  RootMap;


// parses json string to map of objects
std::unique_ptr<RootMap>  getPackageMap(const std::string& , const std::string& );


#endif // PERFORMCURLREQUEST_H
