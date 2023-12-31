LIBRARY := sp_cstring

NAMESPACE := sp

CFLAGS = -std=c11
LD_FLAGS = -L$(LIB_DIR) -l$(LIBRARY) -lcheck

BUILD_TYPE ?= Release

ifeq ($(BUILD_TYPE), Release)
	CFLAGS += -Wall -Wextra -Werror
	BUILD_DIR = build
else ifeq ($(BUILD_TYPE), Sanitize)
	CFLAGS += -g -fsanitize=address
	BUILD_DIR = build_fsan
else ifeq ($(BUILD_TYPE), Debug)
	CFLAGS += -g
	BUILD_DIR = build_dbg
else
$(error Unknown build type $(BUILD_TYPE))
endif

INSTALL_PREFIX ?= /usr/local
OBJ_DIR := $(BUILD_DIR)/obj
LIB_DIR := $(BUILD_DIR)/lib
COVERAGE_DIR ?= coverage
GCDA_DIR := $(BUILD_DIR)/gcov
SOURCES_DIR := src
INCLUDE_DIR := include
TESTS_DIR := tests


MEMCHECK ?= valgrind
MEMCHECK_FLAGS ?= --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=$(BUILD_DIR)/memcheck_report.txt -s

FSANITIZE := -fsanitize=address
COVERAGE :=-fprofile-arcs -ftest-coverage -lgcov

SOURCES := cstring.c
TEST_SOURCES := test_cstring_create.c test_cstring_modification.c test_cstring_operations.c test_cstring_insertion.c test_cstring_erasure.c

SOURCES_PATH := $(addprefix $(SOURCES_DIR)/$(NAMESPACE)/, $(SOURCES))
TEST_SOURCES_PATH := $(addprefix $(TESTS_DIR)/, $(TEST_SOURCES))
OBJ_PATH := $(addprefix $(OBJ_DIR)/, $(SOURCES:%.c=%.o))

TEST_EXE = tests_$(LIBRARY)

ifeq ($(OS), Windows_NT)
else
    OS = $(shell uname -s)
	ifeq ($(OS), Linux)
		LD_FLAGS += -lm -lsubunit
	endif
endif

all: $(LIB_DIR)/lib$(LIBRARY).a

install: $(LIB_DIR)/lib$(LIBRARY).a
	@mkdir -p $(INSTALL_PREFIX)/lib
	@mkdir -p $(INSTALL_PREFIX)/include/$(NAMESPACE)
	cp $(LIB_DIR)/libsp_cstring.a $(INSTALL_PREFIX)/lib/
	cp $(INCLUDE_DIR)/$(NAMESPACE)/cstring.h $(INSTALL_PREFIX)/include/$(NAMESPACE)/

uninstall:
	rm $(INSTALL_PREFIX)/lib/libsp_cstring.a
	rm $(INSTALL_PREFIX)/include/sp/cstring.h

$(LIB_DIR)/lib$(LIBRARY).a: $(OBJ_DIR)/$(SOURCES:.c=.o)
	@mkdir -p  $(LIB_DIR)
	ar -rcs $(LIB_DIR)/lib$(LIBRARY).a $(OBJ_PATH)
	ranlib $(LIB_DIR)/lib$(LIBRARY).a

tests: $(BUILD_DIR)/$(TEST_EXE) 

$(BUILD_DIR)/$(TEST_EXE): $(LIB_DIR)/lib$(LIBRARY).a $(TEST_SOURCES_PATH)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(TEST_SOURCES_PATH) $(TESTS_DIR)/main.c $(LD_FLAGS) -o $(BUILD_DIR)/$(TEST_EXE)

$(OBJ_DIR)/%.o: $(SOURCES_DIR)/$(NAMESPACE)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR)/$(NAMESPACE) -c $< -o $@

memcheck: $(BUILD_DIR)/$(TEST_EXE)
	$(MEMCHECK) $(MEMCHECK_FLAGS)  ./$(BUILD_DIR)/$(TEST_EXE)

fsan: fsan_flags $(LIB_DIR)/lib$(LIBRARY).a tests

fsan_flags:
	$(eval CFLAGS += -fsanitize=address)

clean:
	rm -rf build* coverage

.PHONY: all, clean, tests
