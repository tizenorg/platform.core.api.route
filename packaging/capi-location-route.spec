Name:       capi-location-route
Summary:    A Location Route library in Tizen Native API
Version:    0.1.0
Release:    2
Group:      TO_BE/FILLED_IN
License:    TO BE FILLED IN
Source0:    %{name}-%{version}.tar.gz
Source1001: packaging/capi-location-route.manifest 
BuildRequires: cmake
BuildRequires: pkgconfig(dlog)
BuildRequires: pkgconfig(location)
BuildRequires: pkgconfig(capi-base-common)
BuildRequires: pkgconfig(capi-location-manager)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description


%package devel
Summary:  A Location Route library in Tizen Native API (Development)
Group:    TO_BE/FILLED_IN
Requires: %{name} = %{version}-%{release}

%description devel


%prep
%setup -q


%build
cp %{SOURCE1001} .
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest capi-location-route.manifest
%{_libdir}/libcapi-location-route.so.*

%files devel
%manifest capi-location-route.manifest
%{_includedir}/location/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-location-route.so
