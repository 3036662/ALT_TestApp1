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

        Package(const std::string& name_,const std::string& version_,const std::string& release_,const std::string& arch_,int epoch_):
                                                            name{name_},version{version_},release{release_},arch{arch_},epoch{epoch_}{}
};

#endif // PACKAGE_H
