#include "CurlWrapper.h"

//curl init
CurlWrapper::CurlWrapper() :readBuffer{},curl{nullptr}
{
     try{
        readBuffer.reserve(CURL_MAX_WRITE_SIZE*10); //string buffer for curl response
      }
      catch (std::bad_alloc& ba){
         std::cerr<<"Error allocating memory for HTTP response." "bad_alloc caught: " << ba.what() << '\n';
         throw;
      }
      curl = curl_easy_init();
      if (curl==NULL){
               std::cerr<< "Fatal error found with CURL initialisation"<<std::endl;
               throw "Error with cUrl initialization";
      }
      curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);


}

// cleanup CURL
CurlWrapper::~CurlWrapper()
{
     curl_easy_cleanup(curl);
}


// callback for CURL
size_t CurlWrapper::writeCallback(void *contents, size_t sz, size_t nmemb, void *userp){
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

// get Response string for branch
const std::string CurlWrapper::perfomReq(std::string branch){
    readBuffer.clear();
    std::string req_url="https://rdb.altlinux.org/api/export/branch_binary_packages/";
    // curl_easy_escape yelds to memory leak 32 bytes
    req_url+=curl_easy_escape(curl,branch.c_str(),branch.size());
    //req_url+=branch;
    curl_easy_setopt(curl, CURLOPT_URL, req_url.c_str());
    std::cerr << "Making request to "<<req_url<< std::endl;
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        std::cerr<<"cUrl request to server failed: \n"<<curl_easy_strerror(res)<<std::endl;
        std::cerr<<"!!!"<<std::endl<<"Looks like you passed wrong branch names"<<std::endl;
        std::cerr<<"Allowed branches examples: sisyphus, p9, p10"<<std::endl;
        readBuffer.clear();
    }
    readBuffer.shrink_to_fit();
    std::cerr<<"Downoladed data size: "<<readBuffer.size()<<std::endl<<"..."<<std::endl;
    return readBuffer;
}
