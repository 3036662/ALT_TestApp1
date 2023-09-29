cmake_minimum_required(VERSION 3.20.0)
project(testlibforALT VERSION 1.0)


#include(GNUInstallDirs)

set(CMAKE_INSTALL_LIBDIR lib64)
set(CMAKE_INSTALL_PREFIX /usr)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSON11 REQUIRED IMPORTED_TARGET json11)
message("JSON11_FOUND: ${JSON11_FOUND}")
pkg_check_modules(CURL REQUIRED IMPORTED_TARGET libcurl)
message("CURL_FOUND: ${CURL_FOUND}")


add_compile_options(-fPIC -Wall -Wextra)
add_library(testlibforALT SHARED testlib.cpp)
include_directories(include)
add_subdirectory(src)
target_link_libraries(testlibforALT PRIVATE CurlWrapper StringUtils SortMap)
target_link_libraries(testlibforALT PRIVATE PkgConfig::JSON11 PkgConfig::CURL)
set_target_properties(testlibforALT PROPERTIES VERSION ${CMAKE_PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR} )

add_subdirectory(client)

install(TARGETS testlibforALT LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}) 
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/testlibforalt.h" TYPE INCLUDE)
install(TARGETS ALT_test1 RUNTIME) 
