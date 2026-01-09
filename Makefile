# Makefile for liboct - Octonion Arithmetic Library
# (c) Chris "Scáth" Ó Luanaigh, 2026

# Package information
NAME = liboct
VERSION = 0.2.0
RELEASE = 1

# Installation directories
PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
INCLUDEDIR = $(PREFIX)/include
PKGCONFIGDIR = $(LIBDIR)/pkgconfig

# Build tools
CC = gcc
AR = ar
INSTALL = install
MKDIR = mkdir -p
RM = rm -f

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -fPIC
LDFLAGS = -shared -lm

# Source files
SOURCES = octonion.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = octonion.h

# Library outputs
STATIC_LIB = liboct.a
SHARED_LIB = liboct.so.$(VERSION)
SHARED_SONAME = liboct.so.0
SHARED_LINK = liboct.so

# Test programs
TEST_BASIC = test

# ============================================
# Build Targets
# ============================================

.PHONY: all clean install uninstall test static shared

all: static shared

# Static library
static: $(STATIC_LIB)

$(STATIC_LIB): $(OBJECTS)
	$(AR) rcs $@ $^

# Shared library
shared: $(SHARED_LIB)

$(SHARED_LIB): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) -Wl,-soname,$(SHARED_SONAME) -o $@ $^
	ln -sf $(SHARED_LIB) $(SHARED_SONAME)
	ln -sf $(SHARED_SONAME) $(SHARED_LINK)

# Object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

# Test programs
test: $(TEST_BASIC)

$(TEST_BASIC): test.c $(STATIC_LIB)
	$(CC) $(CFLAGS) -o $@ $< $(STATIC_LIB) -lm


# ============================================
# Installation
# ============================================

install: all
	# Create directories
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(MKDIR) $(DESTDIR)$(PKGCONFIGDIR)
	
	# Install libraries
	$(INSTALL) -m 644 $(STATIC_LIB) $(DESTDIR)$(LIBDIR)/
	$(INSTALL) -m 755 $(SHARED_LIB) $(DESTDIR)$(LIBDIR)/
	
	# Create symlinks
	ln -sf $(SHARED_LIB) $(DESTDIR)$(LIBDIR)/$(SHARED_SONAME)
	ln -sf $(SHARED_SONAME) $(DESTDIR)$(LIBDIR)/$(SHARED_LINK)
	
	# Install headers
	$(INSTALL) -m 644 $(HEADERS) $(DESTDIR)$(INCLUDEDIR)/
	
	# Install pkg-config file
	sed -e 's|@PREFIX@|$(PREFIX)|g' \
	    -e 's|@VERSION@|$(VERSION)|g' \
	    octonion.pc.in > octonion.pc
	$(INSTALL) -m 644 octonion.pc $(DESTDIR)$(PKGCONFIGDIR)/
	
	# Update library cache (if not using DESTDIR)
	@if [ -z "$(DESTDIR)" ]; then \
		ldconfig 2>/dev/null || true; \
	fi

uninstall:
	$(RM) $(DESTDIR)$(LIBDIR)/$(STATIC_LIB)
	$(RM) $(DESTDIR)$(LIBDIR)/$(SHARED_LIB)
	$(RM) $(DESTDIR)$(LIBDIR)/$(SHARED_SONAME)
	$(RM) $(DESTDIR)$(LIBDIR)/$(SHARED_LINK)
	$(RM) $(DESTDIR)$(INCLUDEDIR)/octonion.h
	$(RM) $(DESTDIR)$(PKGCONFIGDIR)/octonion.pc
	@if [ -z "$(DESTDIR)" ]; then \
		ldconfig 2>/dev/null || true; \
	fi

# ============================================
# Package Building
# ============================================

# RPM package
.PHONY: rpm rpm-prep

rpm-prep:
	$(MKDIR) -p rpmbuild/{BUILD,RPMS,SOURCES,SPECS,SRPMS}

rpm: rpm-prep
	# Create source tarball
	$(MKDIR) $(NAME)-$(VERSION)
	cp $(SOURCES) $(HEADERS) $(NAME)-$(VERSION)/
	cp test.c  $(NAME)-$(VERSION)/
	cp Makefile octonion.pc.in $(NAME)-$(VERSION)/
	tar czf rpmbuild/SOURCES/$(NAME)-$(VERSION).tar.gz $(NAME)-$(VERSION)
	$(RM) -r $(NAME)-$(VERSION)
	
	# Build RPM
	rpmbuild --define "_topdir $(PWD)/rpmbuild" \
	         -ba packaging/$(NAME).spec

# DEB package
.PHONY: deb deb-prep

deb-prep:
	$(MKDIR) -p debian/$(NAME)/DEBIAN
	$(MKDIR) -p debian/$(NAME)$(PREFIX)

deb: deb-prep
	# Install to debian staging directory
	$(MAKE) install DESTDIR=$(PWD)/debian/$(NAME) PREFIX=/usr
	
	# Create control file
	sed -e 's|@VERSION@|$(VERSION)|g' \
	    -e 's|@RELEASE@|$(RELEASE)|g' \
	    packaging/control.in > debian/$(NAME)/DEBIAN/control
	
	# Copy postinst/postrm scripts if they exist
	@if [ -f packaging/postinst ]; then \
		$(INSTALL) -m 755 packaging/postinst debian/$(NAME)/DEBIAN/; \
	fi
	@if [ -f packaging/postrm ]; then \
		$(INSTALL) -m 755 packaging/postrm debian/$(NAME)/DEBIAN/; \
	fi
	
	# Build DEB
	dpkg-deb --build debian/$(NAME)
	mv debian/$(NAME).deb $(NAME)_$(VERSION)-$(RELEASE)_arm64.deb

# Source distribution
.PHONY: dist

dist:
	$(MKDIR) $(NAME)-$(VERSION)
	cp $(SOURCES) $(HEADERS) $(NAME)-$(VERSION)/
	cp test.c  $(NAME)-$(VERSION)/
	cp Makefile octonion.pc.in README.md LICENSE $(NAME)-$(VERSION)/
	cp -r packaging $(NAME)-$(VERSION)/
	tar czf $(NAME)-$(VERSION).tar.gz $(NAME)-$(VERSION)
	$(RM) -r $(NAME)-$(VERSION)

# ============================================
# Utility Targets
# ============================================

clean:
	$(RM) *.o *.a *.so* $(TEST_BASIC) $(TEST_VERSION) octonion.pc
	$(RM) -r rpmbuild debian
	$(RM) *.deb *.rpm *.tar.gz

distclean: clean
	$(RM) -r $(NAME)-$(VERSION)

check: test
	./$(TEST_BASIC)
	./$(TEST_VERSION)

help:
	@echo "liboct Makefile"
	@echo ""
	@echo "Build targets:"
	@echo "  all          - Build static and shared libraries (default)"
	@echo "  static       - Build static library only"
	@echo "  shared       - Build shared library only"
	@echo "  test         - Build test programs"
	@echo ""
	@echo "Installation:"
	@echo "  install      - Install libraries and headers"
	@echo "  uninstall    - Remove installed files"
	@echo ""
	@echo "Packaging:"
	@echo "  rpm          - Build RPM package"
	@echo "  deb          - Build DEB package"
	@echo "  dist         - Create source tarball"
	@echo ""
	@echo "Utilities:"
	@echo "  clean        - Remove build artifacts"
	@echo "  distclean    - Remove all generated files"
	@echo "  check        - Run tests"
	@echo "  help         - Show this help"
	@echo ""
	@echo "Variables:"
	@echo "  PREFIX       - Installation prefix (default: /usr/local)"
	@echo "  DESTDIR      - Staging directory for packaging"
	@echo "  CC           - C compiler (default: gcc)"
