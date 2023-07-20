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
	
all: client 
 


# ----------------------- CLIENT------------------------	
client.o:
	$(CC) -Wall -O2 -c -I$(PREFIX)/$(INCLUDEDIR) -o client.o client.cpp
client: client.o 
	$(CC) -o ALT_test1 client.o -L$(LINKDIR) -ltestlibforALT 
	rm client.o
install: 
	cp ALT_test1 $(PREFIX)$(BINDIR)

remove: 	
	rm $(PREFIX)$(BINDIR)/ALT_test1
	 
	
	
		
	
	
