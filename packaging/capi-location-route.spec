Name:           capi-location-route
Version:        0.1.4
Release:        1
License:        Apache-2.0
Summary:        A Location Route library in Tizen Native API
Group:          API/C API
Source0:        %{name}-%{version}.tar.gz
Source1001: 	capi-location-route.manifest
BuildRequires:  cmake
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(capi-location-manager)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(location)

%description
%{summary}.


%package devel
Summary:        A Location Route library in Tizen Native API (Development)
Group:          Development/API
Requires:       %{name} = %{version}

%description devel
%{summary}.

Development Package


%prep
%setup -q
cp %{SOURCE1001} .

%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}


make %{?_smp_mflags}

%install
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest %{name}.manifest
%{_libdir}/libcapi-location-route.so.*

%files devel
%manifest %{name}.manifest
%{_includedir}/location/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-location-route.so
