#include "Package.h"
#include "stringUtils.h"

using namespace VersionUtils;

//simple constructor from strings
Package::Package(const std::string& name_,const std::string& version_,
                const std::string& release_,const std::string& arch_,int epoch_,
                const std::string& dtag,int bt,const std::string src):
                                    name{name_},
                                    version{version_},
                                    release{release_},
                                    arch{arch_},
                                    epoch{epoch_},
                                    disttag{dtag},
                                    buildtime{bt},
                                    source{src},
                                    versionInSecond{},
                                    releaseInSecond{}{};



// constructor for differense info
Package::Package(const Package& p1,const Package& p2):
                                    name{p1.name},
                                    version{p1.version},
                                    release{p1.release},
                                    arch{p1.arch},
                                    epoch{p1.epoch},
                                    disttag{p1.disttag},
                                    buildtime{p1.buildtime},
                                    source{p1.source},
                                    versionInSecond{p2.version},
                                    releaseInSecond{p2.release}{};




json11::Json Package::to_json() const {
           if (versionInSecond.empty() && releaseInSecond.empty() ){
                return  json11::Json::object{
                       {"name", name},
                       {"version", version},
                       {"release", release},
                       {"arch" , arch},
                       {"epoch",epoch},
                       {"disttag",disttag},
                       {"buildtime",buildtime},
                       {"source",source},
                       };
            }
            return  json11::Json::object{
                   {"name", name},
                   {"version", version},
                   {"release", release},
                   {"arch" , arch},
                   {"epoch",epoch},
                   {"disttag",disttag},
                   {"buildtime",buildtime},
                   {"source",source},
                   {"versionInSecond",versionInSecond},
                   {"releaseInSecond",releaseInSecond},
                   };
}

bool Package::operator > (const Package& p2) const{
        int res=versBigger(version,p2.version);
        if ( res == 0 )  res=versBigger(release,p2.release);
        return res==1;
}


