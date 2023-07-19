#ifndef PACKAGE_H
#define PACKAGE_H
#include <json11.hpp>

// simple class for rpm package representation
class Package
{
    public:
        std::string name;
        std::string version;
        std::string release;
        std::string arch;
        int epoch;
        std::string disttag;
        int buildtime;
        std::string source;
        std::string versionInSecond; // for differense
        std::string releaseInSecond;

        // constructor from strings
        Package(const std::string& name_,const std::string& version_,
                const std::string& release_,const std::string& arch_,int epoch_,
                const std::string& dtag,int bt,const std::string src);
        // constructor for differense info
        Package(const Package& p1,const Package& p2);
        ~Package(){};
        json11::Json to_json() const; //cast to json
};


#endif // PACKAGE_H
