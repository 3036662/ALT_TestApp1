#ifndef CURLWRAPPER_H
#define CURLWRAPPER_H
#include <curl/curl.h>
#include <string>
#include <iostream>


class CurlWrapper
{
    public:

        CurlWrapper(); // curl init
        CurlWrapper(const CurlWrapper&) = delete;
        CurlWrapper& operator= (const CurlWrapper&) = delete;
        ~CurlWrapper();

        const std::string& perfomReq(std::string branch);

    // callback for curl
    static size_t writeCallback(void *contents, size_t sz, size_t nmemb, void *userp);

    private:
        std::string readBuffer;
        CURL* curl;

};

#endif // CURLWRAPPER_H
