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
su -
apt-get install gcc-c++ libjson11 curl libjson11-devel libcurl-devel  git
git clone https://github.com/3036662/ALT_TestApp1.git
cd ALT_TestApp1
make PREFIX=/usr LIBDIR=lib64
make install PREFIX=/usr LIBDIR=/lib64
ldconfig
cd client
make  PREFIX=/usr  LINKDIR=/usr/lib64
make install  PREFIX=/usr
```
### Remove built from source  
```
cd client
make remove PREFIX=/usr
cd ..
make remove PREFIX=/usr LIBDIR=/lib64
ldconfig
```
# Installation in Ubuntu  
```
sudo apt-get install g++ git libjson11-1-dev curl libcurl4-openssl-dev
git clone https://github.com/3036662/ALT_TestApp1.git
cd ALT_TestApp1
make
sudo make install
sudo ldconfig
cd client
make
sudo make install
```
## Uninstall  
```
cd ALT_TestApp1
sudo make remove
cd client
sudo make remove
```
# Notes
It's possible you can find memory leak 64 bytes in 2 blocks, the reason is bug in CURL library - curl_easy_escape function(), bugreport already exists.










   
