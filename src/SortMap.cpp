#include "SortMap.h"
#include <iostream>
#include <string>

SortMap::SortMap(const RootMap* const b1, const RootMap* const b2 ):
                                        pbranch1{b1},pbranch2{b2},resTree{new ResultTree()}
{
    // create criterias
//    resTree->emplace("MissingInSecond",)

    //create all architecrures
//    for (auto it=b1->cbegin();it!=b1->cend();++b){
//        (*resTree)[it->first]
//    }
}

SortMap::~SortMap()
{
    //dtor
}

void SortMap::findMissing
        (const RootMap* const pb1,const RootMap* const pb2,  const std::string& criteria){

   // for each architecture in brach1
   // for each package in branch1
   // place this package to result if missing in branch2

   for (auto itArch=pb1->cbegin();itArch!=pb1->cend();++itArch){ // for each arch in branch1
       const std::string& arch=itArch->first;      // architecture name in br1
       bool isMissingArch = false;
       if (pb2->find(arch) == 0){ isMissingArch = true;} // no even such architecture

        // for each package check existanse in branch2
       for (auto itPack=itArch->second.cbegin();itPack!=itArch->second.cend();++itPack){
            const std::string& packName = itPack->first; // package name in br1
            bool isPackMissing=false;
            if (!isMissingArch){
                 if(pb2->at(arch).find(packName) == 0 ) isPackMissing=true; // check package in brach2
            }
            //put missing to result
            if (isMissingArch || isPackMissing){
                (*resTree)[criteria][arch].push_back(itPack->second);
            }
       }
   }


}


void SortMap::findMissingInSecond(){
    const std::string criteria{"MissingInSecond"};
    findMissing(pbranch1,pbranch2,criteria);

    unsigned count{0};
    for (auto it=(*resTree)[criteria].cbegin(); it != (*resTree)[criteria].cend();++it){
        count+= it->second.size();
    }
     std::cerr<<"Found in first branch "<< count <<" packages Missing in brach 2"<<std::endl;
}

void SortMap::findMissingInFirst(){
    const std::string criteria{"MissingInFirst"};
    findMissing(pbranch2,pbranch1,criteria);

    unsigned count{0};
    for (auto it=(*resTree)[criteria].cbegin(); it != (*resTree)[criteria].cend();++it){
        count+= it->second.size();
    }
    std::cerr<<"Found in second brach "<< count <<" packages Missing in brach 1"<<std::endl;

}
