Name: ALT_TestApp
Version: 1.0
Release: alt1

Summary: library for repo branch compare
Source: %name-%version.tar

Group: System/Libraries
Url: https://github.com/3036662/ALT_TestApp1
License: GPL

BuildRequires: gcc-c++ cmake rpm-macros-cmake libjson11-devel libcurl-devel
Requires: libjson11 libcurl

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
Requires: ALT_TestApp-lib
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
%cmake
%cmake_build


%install
%cmake_install

%files lib
%_usr/%_lib/libtestlibforALT.so.1.0
%_usr/%_lib/libtestlibforALT.so.1

%files client
%_bindir/ALT_test1

%files devel
%_includedir/testlibforalt.h
%_usr/%_lib/libtestlibforALT.so

