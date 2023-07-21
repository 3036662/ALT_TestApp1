#include "SortMap.h"
#include <iostream>
#include <string>
#include <json11.hpp>

SortMap::SortMap(const RootMap* const b1, const RootMap* const b2 ):
                                        pbranch1{b1},pbranch2{b2},resTree{new ResultTree()}{}
SortMap::~SortMap(){}


/*
Filling ResultTree with data

RootMap aka std::unordered_map <std::string, std::unordered_multimap <std::string, Package>>
is result of parsing JSON response, separate for each branch
*/
void SortMap::findMissing
            (const RootMap* const pb1,const RootMap* const pb2,  const std::string& criteria){
   // for each architecture in brach1 ,for each package in branch1
   // place this package to result if missing in branch2
   for (auto itArch = pb1->cbegin();itArch != pb1->cend(); ++itArch){ // for each arch in branch1
       const std::string& arch = itArch->first;      // architecture name in br1
       bool isMissingArch = false;
       if (pb2->count(arch) == 0){ isMissingArch = true;} // no even such architecture
        // for each package check existanse in branch2
       for (auto itPack = itArch->second.cbegin();itPack!=itArch->second.cend();++itPack){
            const std::string& packName = itPack->first; // package name in br1
            bool isPackMissing = false;
            if (!isMissingArch){
                 if(pb2->at(arch).count(packName) == 0 ) isPackMissing=true; // check package in brach2
            }
            //put missing to result
            if (isMissingArch || isPackMissing){
                (*resTree)[criteria][arch].push_back(itPack->second);
            }
       }
   }
}

// using findMissing
void SortMap::findMissingInSecond(){
    const std::string criteria{"MissingInSecond"};
    findMissing(pbranch1,pbranch2,criteria);
    unsigned count{0};
    for (auto it=(*resTree)[criteria].begin(); it != (*resTree)[criteria].end();++it){
        count+= it->second.size();
        it->second.shrink_to_fit();
    }
    std::cerr<<"Found in first branch "<< count <<" packages Missing in brach 2"<<std::endl;
}

// using  findMissing with swapped order of args
void SortMap::findMissingInFirst(){
    const std::string criteria{"MissingInFirst"};
    findMissing(pbranch2,pbranch1,criteria);
    unsigned count{0};
    for (auto it=(*resTree)[criteria].begin(); it != (*resTree)[criteria].end();++it){
        count+= it->second.size();
        it->second.shrink_to_fit();
    }
    std::cerr<<"Found in second brach "<< count <<" packages Missing in brach 1"<<std::endl;
}

// search for packages with newer version
void SortMap::findVersionOrReleaseNewer(){
    const std::string criteria="NewerInFirst";
    // for each arch
    for (auto itArch = pbranch1->cbegin(); itArch!=pbranch1->end(); ++itArch){
        const std::string& arch=itArch->first;
        if (pbranch2->count(arch) == 0){ continue;} // no even such architecture
        // for each package in branch 1;
        for (auto itPack = itArch->second.cbegin(); itPack !=itArch->second.cend(); ++itPack ){
             const std::string& packName = itPack->first; // package name in br1
             if(pbranch2->at(arch).count(packName) == 0 ) {continue;} // no such packet
             const Package& p1=itPack->second;
             const Package& p2=pbranch2->at(arch).at(packName);

             std::string p1vr=p1.version+" "+p1.release;
             std::string p2vr=p2.version+" "+p2.release;
             //if (p1.version>p2.version || p1.release>p2.release){
             //if (p1vr>p2vr){
              if (p1>p2){ // with usage of stringUtils
                    //std::cerr <<" version = " << p1.version +" release "+p1.release << " > " << p2.version+" release "+p2.release <<std::endl;
                    (*resTree)[criteria][arch].emplace_back(p1,p2);
               }

        }

    }
    unsigned count{0};
    for (auto it=(*resTree)[criteria].begin(); it != (*resTree)[criteria].end();++it){
        count+= it->second.size();
        it->second.shrink_to_fit();
    }
    std::cerr<<"Found in first branch "<< count <<" packages newer then in brach 2"<<std::endl;
}




const std::string SortMap::getJsonResponse(){
    json11::Json res=json11::Json(*resTree);
    return res.dump();
}
