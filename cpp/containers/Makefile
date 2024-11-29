SHELL = /bin/bash

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror --std=c++17 -g
GFLAGS = -lgtest -pthread -lstdc++ -lsupc++ -lgcc
#DIRECTORIES = . tests/ s21_array/ s21_list/ s21_map/ s21_multiset/ s21_queue/ s21_set/ s21_stack/ s21_vector/
DIRECTORIES = . tests/ s21_list/ s21_queue/ s21_set/ s21_stack/ s21_vector/ s21_associative_containers/
ALL_SRC = $(foreach DIR, $(DIRECTORIES), $(wildcard $(DIR)*.tpp))
ALL_HEADERS = $(foreach DIR, $(DIRECTORIES), $(wildcard $(DIR)*.hpp))
TEST_FILES = $(wildcard tests/*.cpp)
TEST_TARGET = test

WHEREIS_GCOVR:=$(shell whereis gcovr | sed 's/.*://')


all: clear clean test

clean:
	rm -rf *.o *.a $(TEST_TARGET) *.gcno *.gcda *.info
	rm -rf report

test: clear clean
	$(CXX) $(CXXFLAGS) $(TEST_FILES) -o $(TEST_TARGET) $(GFLAGS)
	./$(TEST_TARGET)
	@rm $(TEST_TARGET)

gcov_report: clear clean
	$(CXX) $(CXXFLAGS) $(TEST_FILES) -o $(TEST_TARGET) $(GFLAGS) --coverage
	./$(TEST_TARGET)
	mkdir report
	source gcovr_env/bin/activate; gcovr --txt-metric branch -r . -e 'tests/*' --exclude-throw-branches --html-details report/index.html --html-theme github.dark-blue; deactivate
#	@if [-d gcovr_env]; then; rm -rf gcovr_env
#	lcov --no-external -o test.info -c -d . -rc lcov_branch_coverage=1 --exclude "$(PWD)/tests/*"
#	genhtml -o report test.info -rc lcov_branch_coverage=1
	@rm -rf *.gcno *.gcda *.gcov $(TEST_TARGET) test.info

clang-format:
	clang-format -i $(ALL_SRC) $(ALL_HEADERS)

clang-check:
	clang-format -n $(ALL_SRC) $(ALL_HEADERS)

valgrind: clean
	$(CXX) $(CXXFLAGS) $(TEST_FILES) -o $(TEST_TARGET) $(GFLAGS)
	valgrind --tool=memcheck --leak-check=yes ./$(TEST_TARGET)
	@rm $(TEST_TARGET)

clear:
	clear

.PHONY: all clean test gcov_report clang-format clang-check valgrind clear