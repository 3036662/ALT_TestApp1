PREFIX=/usr/local
CC=g++
LIBDIR=/lib
BINDIR=/bin
INCLUDEDIR=/include
CFLAGS=-c -Iinclude -Wall -fPIC -g 
LINKDIR=/usr/local/lib
#CFLAGS=-c  -fPIC -g -Wall -fexceptions -O2 -Wnon-virtual-dtor -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -pedantic-errors -pedantic -Wfatal-errors -Wextra -Wall -Iinclude 
LNKFLAGS= -shared -Wl,-soname,
LINKFILES =testlib.o CurlWrapper.o getPackageMap.o Package.o SortMap.o
LINKFILES_FULL = $(LINKFILES:%.o=$(BUILD_DIR)/%.o)

BUILD_DIR=./build
	
all: builddir libObj lib 
install: installLib
 
#   

builddir:
	mkdir -p  $(BUILD_DIR)


#--------------------- MAKE LIB -----------------------------

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

libObj: testlib.o CurlWrapper.o getPackageMap.o Package.o SortMap.o 	
	
lib:    builddir libObj 
	$(CC) -shared  -Wl,-soname,libtestlibforALT.so.1 -o $(BUILD_DIR)/libtestlibforALT.so.1.0 $(LINKFILES_FULL) -lcurl -ljson11
	rm $(LINKFILES_FULL)


#------------------------INSTALL---------------------------	
	
installLib: 
	install $(BUILD_DIR)/libtestlibforALT.so.1.0 $(PREFIX)/$(LIBDIR);  
	ln -s  $(PREFIX)/$(LIBDIR)/libtestlibforALT.so.1.0 $(PREFIX)/$(LIBDIR)/libtestlibforALT.so
	cp testlibforalt.h $(PREFIX)$(INCLUDEDIR) 
uninstallLib:
	 rm $(PREFIX)/$(LIBDIR)/libtestlibforALT*
	 rm  $(PREFIX)/$(INCLUDEDIR)/testlibforalt.h

#-------------------------------------------		 
cleanup:  builddir
	rm -r $(BUILD_DIR)	
remake: uninstallLib cleanup lib installLib 	 

remove: uninstallLib	

	 
	
	
		
	
	
