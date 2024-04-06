CFLAGS = -Wall
CPPFLAGS = -Iinclude

VPATH = $(wildcard include src include/* src/*)

TEST_SRC = $(wildcard tests/*_tests.c)
TESTS = $(patsubst %.c,%,$(TEST_SRC))

LIB_SRC = $(wildcard src/dsa/*.c)
LIB_OBJ = $(patsubst src/dsa/%.c,%.o,$(LIB_SRC))

all: main mvbin

dev: CPPFLAGS += -DDEBUG
dev: CFLAGS += -g
dev: all

tests: clean libdsa.a run_tests

main: main.o linked_list.o
main.o: main.c
linked_list.o: linked_list.c linked_list.h

libdsa.a: $(LIB_OBJ)
	ar rcs $@ $^
	ranlib $@

.PHONY: debug
debug:
	@gdb --tui ./bin/main

.PHONY: mvbin
mvbin:
	@mkdir -p ./bin
	@mv main ./bin/main

.PHONY: clean
clean:
	@rm -fr ./bin *.o *.a $(TESTS)

.PHONY: tests
run_tests: LDLIBS += libdsa.a
run_tests: $(TESTS) libdsa.a
	sh ./tests/runtests.sh

