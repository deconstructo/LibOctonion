Name:           libOctonion
Version:        0.2.0
Release:        1%{?dist}
Summary:        Octonion arithmetic library

License:        GPL-3.0
URL:            https://github.com/deconstructo/LibOctonion
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc
BuildRequires:  make

%description
liboct is a standalone C library for octonion arithmetic. Octonions are
8-dimensional hypercomplex numbers, the final normed division algebra.

This library provides:
- Complete octonion arithmetic (add, subtract, multiply)
- Properties (norm, conjugate, inverse)
- Non-associative multiplication with 8x8 table
- Full support for baroque number systems exploration

%package devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.

%prep
%setup -q

%build
make %{?_smp_mflags} CFLAGS="%{optflags}"

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT PREFIX=%{_prefix}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%license LICENSE
%doc README.md
%{_libdir}/liboct.so.*

%files devel
%{_includedir}/octonion.h
%{_libdir}/liboct.a
%{_libdir}/liboct.so
%{_libdir}/pkgconfig/octonion.pc

%changelog
* Thu Jan 09 2026 Chris "Scáth" Ó Luanaigh <metanoia@gmail.com> - 0.2.0-1
- Initial release
- Basic octonion arithmetic
- 8x8 multiplication table
- Norm-preserving multiplication
- Non-associative algebra support
