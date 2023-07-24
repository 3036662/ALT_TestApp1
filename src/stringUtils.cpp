#include  <cctype>
#include "stringUtils.h"




std::vector<std::string> VersionUtils::splitStr( std::string str, char delimiter = '.' ){
   // patch for situation like a=1a vs b=1.2
    // insert dots before letters
    std::string tmp;
    for (auto it =str.begin();it!=str.end();++it){


        if (it!=str.begin() && isdigit(*it)==0 && *it != '.' ){
            tmp.push_back('.'); //insert dot before symbol
        }
        tmp.push_back(*it);
        if (isdigit(*it)==0 && *it!='.' && *it!= '~' && *it !='^' ){
            tmp.push_back('.'); // insert dot after symbol
        }
    }
    str=tmp;
    // end of patch


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


//The caret symbol (‘^’) is used before a version component which must sort later than any non-caret component. It is used for post-release snapshots, see next section.
//The tilde symbol (‘~’) is used before a version component which must sort earlier than any non-tilde component. It is used for any pre-release versions which wouldn’t otherwise sort appropriately.
// 0.4.1^<something> sorts higher than 0.4.1, but lower than both 0.4.2 and 0.4.1.<anything>.
int VersionUtils::partCompareAtomic ( std::string a, std::string b){
    if (a==b) {return 0;}
    // handling tilda
    if (a[0]=='~' && b[0]!='~') { return -1;}
    if (b[0]=='~' && a[0]!='~') {return 1;}
    if (a[0]=='~' && b[0]=='~' && a.size()>1 && b.size()>1) {
        a.erase(0,1);
        b.erase(0,1);
    }
    // handling caret
    if (a[0]=='^' && b[0]=='^' && a.size()>1 && b.size()>1) {
        a.erase(0,1);
        b.erase(0,1);
    }
    if (a[0]=='^'){
        if (b.empty()) return 1;  //0.4.1^<something> sorts higher than 0.4.1
        else return -1;    // but lower 0.4.1.<anything>.
    }
    if (b[0]=='^') {
        if (a.empty()) return -1;
        else return 1;
    }

    if (a.empty() && !b.empty()) return -1;
    if (b.empty() && !a.empty()) return 1;

    // if symbols
    if (isdigit(a[0])==0 || isdigit(b[0])==0 ) { // a=string or b=string
        if (isdigit(a[0])==0 && isdigit(b[0])!=0) return -1; // a is symbol b is digit -> b>a
        if (isdigit(a[0])!=0 && isdigit(b[0])==0) return 1; // a is digit b is symbol -> a >b
        return   a>b ? 1:-1 ;
    }
    // digits
    if (std::stoi(a)==std::stoi(b)) return 0;
    return   std::stoi(a)>std::stoi(b) ? 1:-1;
}


void VersionUtils::deleteSpaces( std::string& str){
    std::string temp;
    for (size_t i=0;i<str.size();++i){
        if(str[i]!=' ' && str[i]!='_') temp.push_back(str[i]);
        if (str[i]=='_')  temp.push_back('.');
    }
    str=temp;
}

// two versions splitted to arrays for exaple [123a1, 23] and [123b2, 3]
int VersionUtils::versCompare( std::vector<std::string> a, std::vector<std::string> b ){
    size_t longest=std::max (a.size(),b.size());
    a.resize(longest);
    b.resize(longest);
    for (size_t i=0; i < longest; ++i){
        int res=partCompareAtomic(a[i],b[i]);
        if (res!=0){ return res;}
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


