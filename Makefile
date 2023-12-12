CFLAGS= -std=c11 -Wall -Wextra -Werror

LCOV_FLAGS=-fprofile-arcs -ftest-coverage -lgcov

INSTALL_PREFIX ?= /usr/local

all: libsp_cstring.a

install: $(INSTALL_PREFIX)/lib $(INSTALL_PREFIX)/include/sp libsp_cstring.a
	cp lib/libsp_cstring.a $(INSTALL_PREFIX)/lib/
	cp include/sp/cstring.h $(INSTALL_PREFIX)/include/sp/

uninstall:
	rm $(INSTALL_PREFIX)/lib/libsp_cstring.a
	rm $(INSTALL_PREFIX)/include/sp/cstring.h

tests: libsp_cstring.a
	$(CC) $(CFLAGS) -Iinclude tests/test_cstring.c -Llib -lcheck -lm -lsubunit -lc_containers -o build/test_string

build/obj/cstring.o: build/obj
	$(CC) $(CFLAGS) -Iinclude/sp -c src/sp/cstring.c -o build/obj/cstring.o

build: build_dir libsp_cstring.a

build_dir:
	mkdir -p build

build/obj: build_dir
	mkdir -p build/obj

$(INSTALL_PREFIX)/lib:
	mkdir -p $(INSTALL_PREFIX)/lib

$(INSTALL_PREFIX)/include/sp:
	mkdir -p $(INSTALL_PREFIX)/include/sp

lib:
	mkdir -p lib

libsp_cstring.a: lib build/obj/cstring.o
	ar -rcs lib/libsp_cstring.a build/obj/cstring.o
	ranlib lib/libsp_cstring.a

build_covered: add_coverage rebuild

build_debug: add_debug rebuild

clean:
	rm -rf lib build
	rm -rf *.gcda *.gcno

rebuild: clean $(LIB_NAME).a

add_coverage:
	$(eval CFLAGS += --coverage)
add_debug:
	$(eval CFLAGS += -DDEBUG_MODE -g)
