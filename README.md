# ALT_TestApp1
Simple CLI application for package branches analysis in repository.
Application dowloads lists of packages for two branches and compares it
The result consists json string with three objets:

1. MissingInFirst
2. MissingInSecond
3. NewerInFirst

Each parts contains architectures: aarch64, armg, i586, etc.
Each architecture contains array of "package info" (objects
releaseInSecond,versionInSecond fields contained only in the third branch) ,for example:
```
{"NewerInFirst":{"aarch64":[  {"buildtime":"1683218638","disttag":"sisyphus+319372.300.3.1","epoch":1,"name":"zsh-debuginfo","release":"alt1","releaseInSecond":"alt2","source":"zsh","version":"5.9","versionInSecond":"5.8.1,"}]}}
```
Size of JSON string is rather large, so it recomendded to open it with some web-browser.

# Usage 

Command usage:  
```
ALT_test1 brach1 branch > output
```
Example:  
```
ALT_test1 p10 p9 > result.json
```

# Installation in ALT Linux

App consists of shared library and executable.

### Dependencies
App depends on json11 and curl libraries
To install (you need super user rights): 

```
su-
apt-get install libjson11  libcurl libjson11-devel libcurl-devel 
```

Done!

## Install from source
```
cmake -S . -B build_result
cmake --build build_result
cmake --install build_result

```
## Uninstall  
```
#super user
su-
rm -rf /usr/lib64/libtestlibforALT.so.1
rm -rf /usr/lib64/libtestlibforALT.so.1.0
rm -rf /usr/include/testlibforalt.h
rm -rf /usr/lib64/libtestlibforALT.so
rm -rf /usr/bin/ALT_test1

```
# Notes
It's possible you can find memory leak 64 bytes in 2 blocks, the reason is bug in CURL library - curl_easy_escape function(), bugreport already exists.










   
