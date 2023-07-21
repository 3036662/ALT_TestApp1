#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>

namespace VersionUtils{


// split string to vector of strings with dot
std::vector<std::string> splitStr(std::string str, char );


int findNonNumber(const std::string& str);

// split string to vector of string with not digit
std::vector<std::string> splitByLetters ( std::string str );

// compare atomic parts
int partCompareAtomic (const std::string& a, const std::string& b);

// two pars of verstion splitted by simbols exampl  [123,a,1] and [123,b,2] compare
int partCompare (std::vector<std::string> a, std::vector<std::string> b);


void deleteSpaces( std::string& str);

// two versions splitted to arrays by dots compare for exaple [123a1, 23] and [123b2, 3]
int versCompare( std::vector<std::string> a, std::vector<std::string> b );



// true if str1 > str2
int versBigger(std::string str1,std::string str2);

}

#endif // STRINGUTILS_H
