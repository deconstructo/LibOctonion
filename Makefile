# Octonion Library Makefile
# Works on Linux and macOS

# Installation prefix - override with: make PREFIX=/opt/local install
PREFIX ?= /usr/local

# Platform detection
UNAME_S := $(shell uname -s)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC
LDFLAGS = -lm

# Library name and versioning
LIB_NAME = liboct
VERSION = 1.0

ifeq ($(UNAME_S),Darwin)
    # macOS
    LIB_EXT = dylib
    LIB_FILE = $(LIB_NAME).$(LIB_EXT)
    SONAME_FLAG = -install_name $(PREFIX)/lib/$(LIB_FILE)
    SHARED_FLAGS = -dynamiclib $(SONAME_FLAG)
else
    # Linux
    LIB_EXT = so
    LIB_FILE = $(LIB_NAME).$(LIB_EXT).$(VERSION)
    SONAME_FLAG = -Wl,-soname,$(LIB_NAME).$(LIB_EXT).1
    SHARED_FLAGS = -shared $(SONAME_FLAG)
endif

# Source and object files
SOURCES = octonion.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = octonion.h

# Targets
all: $(LIB_FILE)

$(LIB_FILE): $(OBJECTS)
	$(CC) $(SHARED_FLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Installation
install: $(LIB_FILE) $(HEADERS)
	@echo "Installing to $(PREFIX)..."
	install -d $(PREFIX)/lib
	install -d $(PREFIX)/include
	install -m 644 $(HEADERS) $(PREFIX)/include/
	install -m 755 $(LIB_FILE) $(PREFIX)/lib/
ifeq ($(UNAME_S),Linux)
	# Create symlinks for versioning on Linux
	ln -sf $(LIB_FILE) $(PREFIX)/lib/$(LIB_NAME).$(LIB_EXT).1
	ln -sf $(LIB_NAME).$(LIB_EXT).1 $(PREFIX)/lib/$(LIB_NAME).$(LIB_EXT)
	ldconfig -n $(PREFIX)/lib || true
endif
	@echo "Installed successfully!"

uninstall:
	@echo "Uninstalling from $(PREFIX)..."
	rm -f $(PREFIX)/include/oct.h
	rm -f $(PREFIX)/lib/$(LIB_NAME).*
	@echo "Uninstalled successfully!"

clean:
	rm -f $(OBJECTS) $(LIB_FILE) $(LIB_NAME).so.* $(LIB_NAME).dylib test

test: test.c octonion.o
	$(CC) $(CFLAGS) -o test octonion.o test.c -L. -loct $(LDFLAGS)
	./test

.PHONY: all install uninstall clean test
