#ifndef SORTMAP_H
#define SORTMAP_H

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>


#include "Package.h"
#include "getPackageMap.h"

// explanation of result map
/*
map {
    criteria,
    map{
        architecture,
        array of packages
    }
}
*/

typedef  std::unordered_map< // for architectures
                        std::string, // architecture
                        std::vector<Package>>  Architecture;

typedef std::unordered_map <
    std::string, // criteria like MissingInSec
    Architecture> ResultTree;

// class holds methods for rootMap objects sorting
class SortMap
{
    public:
        SortMap()=delete;
        SortMap(const SortMap&)=delete;
        SortMap& operator= (const SortMap&)=delete;
        SortMap(const RootMap* const b1, const RootMap* const b2 );
        ~SortMap();


        void findMissingInSecond();
        void findMissingInFirst();


    protected:

    private:
    void findMissing(const RootMap* const pb1,const RootMap* const pb2,  const std::string& criteria);
    const RootMap* const pbranch1;
    const RootMap* const pbranch2;
    std::unique_ptr<ResultTree> resTree; // result structure
};

#endif // SORTMAP_H


