Name: libALT_test1
Version: 1.0
Release: alt1

Summary: library for repo branch compare
Source: libALT_test1.tar.gz

Group: System/Libraries
Url: https://github.com/3036662/ALT_TestApp1
License:  GPL

%description
This library compares ALT repo branches

%package lib 
Summary: shared library for ALT_test1
Group: System/Libraries
%description lib
Shared library for program

%package client
Summary: client executable for ALT_test1
Group: System/Libraries
Requires: libALT_test1-lib 
%description client
Executable client

#development library
%package devel
Summary: development library for ALT_test1
Group: System/Libraries
%description devel
Dev files

%prep
%setup
%build
make # PREFIX=$RPM_BUILD_ROOT/%{_usr} LIBDIR=%{_lib} 
mkdir -p $RPM_BUILD_ROOT%{_usr}/%{_lib}
mkdir -p $RPM_BUILD_ROOT%{_usr}/include

cp ./build/libtestlibforALT.so.1.0 $RPM_BUILD_ROOT/%{_usr}/%{_lib}
rm -f $RPM_BUILD_ROOT/%{_usr}/%{_lib}/libtestlibforALT.so   
ln -s $RPM_BUILD_ROOT/%{_usr}/%{_lib}/libtestlibforALT.so.1.0 $RPM_BUILD_ROOT/%{_usr}/%{_lib}/libtestlibforALT.so   
cp testlibforalt.h $RPM_BUILD_ROOT/%{_usr}/include
make --directory=client PREFIX=$RPM_BUILD_ROOT/%{_usr} LINKDIR=$RPM_BUILD_ROOT/%{_usr}/%{_lib}
rm -f $RPM_BUILD_ROOT/%{_usr}/%{_lib}/libtestlibforALT.so*
rm $RPM_BUILD_ROOT/%{_usr}/include/testlibforalt.h 

%install 
mkdir -p $RPM_BUILD_ROOT%{_usr}/%{_lib}
mkdir -p $RPM_BUILD_ROOT%{_usr}/include
make install PREFIX=$RPM_BUILD_ROOT/%{_usr} LIBDIR=%{_lib}
mkdir -p $RPM_BUILD_ROOT/%{_bindir}
make install --directory=client PREFIX=$RPM_BUILD_ROOT BINDIR=%{_bindir}


%files lib
%{_usr}/%{_lib}/libtestlibforALT.so.1.0 
%{_usr}/%{_lib}/libtestlibforALT.so.1

%files client 
%{_bindir}/ALT_test1

%files devel
%{_includedir}/testlibforalt.h
%{_usr}/%{_lib}/libtestlibforALT.so


