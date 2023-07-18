//#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <json11.hpp>
#include <unordered_map>

#include "Package.h"

static size_t WriteCallback(void *contents, size_t sz, size_t nmemb, void *userp){
    //((std::string*)userp)->append((char*)contents, sz * nmemb);
    try{
        static_cast<std::string*>(userp)->append(static_cast<char*>(contents), sz * nmemb);
    }
    catch (std::bad_alloc& ba){
         std::cerr<<"Error allocating memory for HTTP response." "bad_alloc caught: " << ba.what() << '\n';
         return 0;
    }
    return sz * nmemb;
}

int main(void)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;
  try{
    readBuffer.reserve(CURL_MAX_WRITE_SIZE*10);
  }
  catch (std::bad_alloc& ba){
     std::cerr<<"Error allocating memory for HTTP response." "bad_alloc caught: " << ba.what() << '\n';
     throw;
  }

  curl = curl_easy_init();
  if (curl==NULL){
    std::cerr<< "Fatal error found with CURL initialisation"<<std::endl;
    return 1;
  }

//curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    curl_easy_setopt(curl, CURLOPT_URL, "https://rdb.altlinux.org/api/export/branch_binary_packages/p10");
//curl_easy_setopt(curl, CURLOPT_URL, "https://rdb.altlinux.org/api/dsfg");
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    /* Perform the request, res will get the return code */
    std::cerr << "Making request to server..."<< std::endl;
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK) std::cerr<<"cUrl request to server failed: \n"<<curl_easy_strerror(res)<<std::endl;
    readBuffer.shrink_to_fit();
   // std::cout << readBuffer << std::endl;
    std::cerr<<"Downoladed data size: "<<readBuffer.size()<<std::endl;

//std::cout<< readBuffer.substr(0,100)<<std::endl;
    /* always cleanup */
    curl_easy_cleanup(curl);

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
    //for (auto it=packagesArr.vec)


  return 0;
}
