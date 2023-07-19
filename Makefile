CC=g++
CFLAGS=-c -Iinclude -Wall -fPIC -g 
#CFLAGS=-c  -fPIC -g -Wall -fexceptions -O2 -Wnon-virtual-dtor -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -pedantic-errors -pedantic -Wfatal-errors -Wextra -Wall -Iinclude 
LNKFLAGS= -shared -Wl,-soname,
LINKFILES =testlib.o CurlWrapper.o getPackageMap.o Package.o SortMap.o
LINKFILES_FULL = $(LINKFILES:%.o=$(BUILD_DIR)/%.o)

BUILD_DIR=./build
	
all: builddir libObj lib cleanobjs 
#   

builddir:
	if [ ! -d $(BUILD_DIR) ]; then mkdir  $(BUILD_DIR) ;	fi
libObj: testlib.o CurlWrapper.o getPackageMap.o Package.o SortMap.o 

testlib.o: 
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/testlib.o  ./testlib.cpp
CurlWrapper.o: 
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/CurlWrapper.o  ./src/CurlWrapper.cpp
getPackageMap.o:
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/getPackageMap.o  ./src/getPackageMap.cpp
Package.o: 
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/Package.o  ./src/Package.cpp
SortMap.o:
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/SortMap.o ./src/SortMap.cpp
lib:   builddir libObj 
	$(CC) -shared  -Wl,-soname,libtestlibforALT.so.1 -o $(BUILD_DIR)/libtestlibforALT.so.1.0 $(LINKFILES_FULL) -lcurl -ljson11
	rm $(LINKFILES_FULL)
	
client.o: 
	$(CC) -Wall -O2 -c -o $(BUILD_DIR)/client.o ./client.cpp
client: client.o /usr/local/lib/libtestlibforALT.so.1
	$(CC) -o $(BUILD_DIR)/ALT_test1 $(BUILD_DIR)/client.o -L/usr/local/lib -ltestlibforALT 
	rm $(BUILD_DIR)/client.o
	
installLib: $(BUILD_DIR)/libtestlibforALT.so.1.0
	cp $(BUILD_DIR)/libtestlibforALT.so.1.0 /usr/local/lib; ldconfig   
uninstallLib:
	 rm /usr/local/lib/libtestlibforALT*
cleanup: uninstallLib builddir
	rm -r $(BUILD_DIR)	
remake: uninstallLib cleanup lib installLib client	 

cleanobjs: builddir
	rm -r $(BUILD_DIR)/*.o

install: lib installLib client
	cp $(BUILD_DIR)/ALT_test1 /usr/local/bin
remove: uninstallLib	
	rm /usr/local/bin/ALT_test1
	 
	
	
		
	
	
