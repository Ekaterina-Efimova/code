SHELL = /bin/sh

CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c11
CFLAGS:=$(FLAGS)
GCOV:=$(FLAGS) --coverage
SRC=$(wildcard *.c)
HEADERS=$(wildcard *.h)
OBJS=$(patsubst %.c,%.o,$(SRC))
TEST_SRC=$(wildcard tests/*.c)
BUILD=build/
GR=s21_graph
GA=s21_graph_algorithms
CONT=s21_containers
NAME=simple_navigator

.PHONY: all $(NAME) $(GR) $(GA) $(CONT) clean test run gcov_report vg cpp gcov_flag

all: $(NAME)

$(NAME): $(GR) $(CONT) $(GA) main.c main.h
	$(CC) $(CFLAGS) main.c -o $(BUILD)$@  -Lbuild -l:s21_graph.a -l:s21_graph_algorithms.a -l:s21_containers.a -lm

$(GR): $(BUILD)$(GR).a

$(BUILD)$(GR).a: $(BUILD)$(GR).o
	ar rc $@ $(BUILD)$(GR).o
	ranlib $@

$(BUILD)$(GR).o: $(GR).c $(GR).h
	$(CC) $(CFLAGS) -c $(GR).c -o $@

$(GA): $(BUILD)$(GA).a

$(BUILD)$(GA).a: $(BUILD)$(GA).o
	ar rc $@ $(BUILD)$(GA).o
	ranlib $@

$(BUILD)$(GA).o: $(GA).c $(GA).h
	$(CC) $(CFLAGS) -c $(GA).c -o $@

$(CONT): $(BUILD)$(CONT).a

$(BUILD)$(CONT).a: $(BUILD)$(CONT).o
	ar rc $@ $(BUILD)$(CONT).o
	ranlib $@

$(BUILD)$(CONT).o: $(CONT).c $(CONT).h
	$(CC) $(CFLAGS) -c $(CONT).c -o $@

clean:
	-rm -rf *.o *.gcno *.gcda *.info tests/*.o tests/*.gcno tests/*.gcda tests/*.gcda tests/*.info test build/*

test: $(GR) $(CONT) $(GA) $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(BUILD)$@  -Lbuild -l:s21_graph.a -l:s21_graph_algorithms.a -l:s21_containers.a -lcheck -lm -lsubunit
	-clear
	$(BUILD)test

run: all
	$(BUILD)$(NAME)

$(BUILD)$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c $(CONT).c -o $@

gcov_report: clean gcov_flag test
	-lcov --rc lcov_branch_coverage=1 -t "s21_simple_navigator_report" -o s21_simple_navigator_report2.info -c -d .
	-lcov -r s21_simple_navigator_report2.info "*src/tests*" -o s21_simple_navigator_report.info
	-genhtml --rc lcov_branch_coverage=1 -o report s21_simple_navigator_report.info
	-make clean

vg: test
	-clear
	-valgrind --tool=memcheck --leak-check=yes $(BUILD)test

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem --check-config $(SRC) $(HEADERS)
	@cp ../materials/linters/.clang-format .
	clang-format -n $(SRC) $(HEADERS)

gcov_flag:
	$(eval CFLAGS:=$(GCOV))