#ifndef GETPACKAGEMAP_H
#define GETPACKAGEMAP_H
#include <unordered_map>

#include <string>
#include <curl/curl.h>

#include "Package.h"


typedef std::unordered_map <std::string, std::unordered_multimap <std::string, Package>>  RootMap;

RootMap*  getPackageMap(CURL* curl,std::string branch){

}


#endif // PERFORMCURLREQUEST_H
