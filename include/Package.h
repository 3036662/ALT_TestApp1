#ifndef PACKAGE_H
#define PACKAGE_H


class Package
{
    public:
        std::string name;
        std::string version;
        std::string release;
        std::string arch;
        int epoch;
        //not needed yet
        // std::string disttag;
        // int buildtime;
        // std::string source;

        Package(const std::string& name,const std::string& version,const std::string& release,const std::string& arch,int epoch):
                                                            name{name},version{version},release{release},arch{arch},epoch{epoch}{}
};

#endif // PACKAGE_H
