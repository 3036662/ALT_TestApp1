#include  <cctype>
#include "stringUtils.h"



// split string to vector of strings with dot
std::vector<std::string> VersionUtils::splitStr(std::string str, char delimiter = '.' ){
    std::vector<std::string> v1;
    size_t len{0};
    size_t pos{0};
    while  ( (pos=str.find(delimiter)) != std::string::npos) {
        if (pos) v1.push_back( str.substr(0, pos) );
        len= pos == std::string::npos ? pos : pos+1;
        str.erase(0, len);
    }
    if (!str.empty()) v1.push_back(str);
    return v1;
}

int VersionUtils::findNonNumber(const std::string& str){
    for (size_t i=0; i<str.size(); ++i){
        if (isdigit(str[i]) == 0) return i;
    }
    return -1;
}

// split string to vector of string with not digit
std::vector<std::string> VersionUtils::splitByLetters ( std::string str ){
    std::vector<std::string> v1;
    size_t len{0};
    int pos{-1};
    while  ( (pos=findNonNumber(str)) != -1) {
        if (pos) v1.push_back( str.substr(0, pos) );
        v1.push_back(str.substr(pos,1)); // push simbol
        len= pos == -1 ? std::string::npos : pos+1;
        str.erase(0, len);
    }
    //std::cout<<"split by symbol "<< str.substr(0, pos) <<std::endl;
    if (!str.empty()) v1.push_back(str);
    return v1;
}



int VersionUtils::partCompareAtomic (const std::string& a, const std::string& b){
    if (a==b) {return 0;}
    if (a.empty() && isdigit(b[0])==0) return -1; // a="" < b="x"
    if (a.empty() && isdigit(b[0])!=0) return stoi(b)==0 ? 0:-1; // a="" = b=000 and a="" < b=1
    if (b.empty() && isdigit(a[0])==0) return 1;  // a="x" > b=""
    if (b.empty() && isdigit(a[0])!=0){ return stoi(a)==0 ? 0:1 ;} // a="000" = b="" , a="1" > b=""
     // if symbols
    if (isdigit(a[0])==0 || isdigit(b[0])==0 ) return   a>b ? 1:-1 ; // a=string or b=string
    // digits
    if (std::stoi(a)==std::stoi(b)) return 0;
    return   std::stoi(a)>std::stoi(b) ? 1:-1;
}

// two pars of verstion splitted by simbols exampl  [123,a,1] and [123,b,2]
int VersionUtils::partCompare (std::vector<std::string> a, std::vector<std::string> b){
    size_t longest=std::max (a.size(),b.size());
    a.resize(longest);
    b.resize(longest);
    // for each part
    for (size_t i=0; i < longest; ++i){
        int res=partCompareAtomic(a[i],b[i]);
        if (res!=0){ return res;}
    }
    return 0;
}

void VersionUtils::deleteSpaces( std::string& str){
    std::string temp;
    for (size_t i=0;i<str.size();++i){
        if(str[i]!=' ' || str[i]!='_') temp.push_back(str[i]);
    }
    str=temp;
}

// two versions splitted to arrays for exaple [123a1, 23] and [123b2, 3]
int VersionUtils::versCompare( std::vector<std::string> a, std::vector<std::string> b ){
    size_t longest=std::max (a.size(),b.size());
    a.resize(longest);
    b.resize(longest);

    std::vector<std::string>  partofA;
    std::vector<std::string>  partofB;
    // for each part of version
    for (size_t i=0; i < longest; ++i){
        partofA=splitByLetters(a[i]); //[123,a,1]
        partofB=splitByLetters(b[i]); // [123,b,2]
        // now compare patst splitted by letter
        int res=partCompare(partofA,partofB);
        if (res!=0) return res;
    }
    return 0;
}

int VersionUtils::versBigger(std::string str1,std::string str2){
    deleteSpaces(str1);
    deleteSpaces(str2);
    std::vector<std::string> v1=splitStr(str1) ;
    std::vector<std::string> v2=splitStr(str2);
    return versCompare(v1,v2);

}


