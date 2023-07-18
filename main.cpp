//#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <json11.hpp>

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
    std::cout << "Making request to server..."<< std::endl;
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK) std::cerr<<"cUrl request to server failed: \n"<<curl_easy_strerror(res)<<std::endl;
    readBuffer.shrink_to_fit();
   // std::cout << readBuffer << std::endl;
    std::cout<<"Downoladed data size: "<<readBuffer.size()<<std::endl;

    std::cout<< readBuffer.substr(0,100)<<std::endl;
    /* always cleanup */
    curl_easy_cleanup(curl);

    // json response parse
    std::string err;
    const json11::Json jsonResponseObject = json11::Json::parse(readBuffer, err);
    std::cout<<"Packages found in branch 1"<<jsonResponseObject["length"].int_value()<<std::endl;

    auto packagesArr=jsonResponseObject["packages"].array_items();
    std::cout<<packagesArr[0].dump()<<std::endl;

  return 0;
}
