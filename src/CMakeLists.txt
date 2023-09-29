add_compile_options(-fPIC)

add_library(CurlWrapper OBJECT CurlWrapper.cpp)
add_library(StringUtils OBJECT stringUtils.cpp)
add_library(SortMap OBJECT getPackageMap.cpp Package.cpp SortMap.cpp)
