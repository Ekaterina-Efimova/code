SHELL = /bin/sh

CFLAGS = -Wall -Wextra -Werror -std=c11 -lm
TFLAGS = -lcheck -lsubunit -lm
GFLAGS = -fprofile-arcs -ftest-coverage

LIB_NAME = s21_decimal.a
LIB_SRC = s21_decimal.c s21_round.c s21_conversion.c s21_compaRATion.c utils/s21_utils.c
LIB_OBJ = $(LIB_SRC:.c=.o)
TEST_SRC = $(wildcard test/*.c test/_helpers/*.c test/arithmetic/*.c test/comparison/*.c test/conversion/*.c test/other/*.c)
TEST_GCDA = $(LIB_SRC:.c=.gcda)
TEST_OBJ = $(TEST_SRC:.c=.o)

all: clear $(LIB_NAME)

clear:
	clear

$(LIB_NAME): $(LIB_OBJ)
	@ar rcs $(LIB_NAME) $(LIB_OBJ)
	@ranlib $(LIB_NAME)
	@rm -f $(LIB_OBJ)
	@cat pics/cat.txt

test: $(TEST_OBJ) $(LIB_NAME)
	@gcc $(CFLAGS) $(TEST_OBJ) -o tests -L. -l:$(LIB_NAME) $(TFLAGS)
	@rm -f $(TEST_OBJ)
	@valgrind --tool=memcheck --leak-check=yes ./tests
	@cat pics/cats.txt

.PHONY: gcov_report
gcov_report: clean_gcov
	@gcc $(CFLAGS) -c $(GFLAGS) $(LIB_SRC)
	@ar rcs $(LIB_NAME) s21_decimal.o s21_round.o s21_conversion.o s21_compaRATion.o s21_utils.o
	@ranlib $(LIB_NAME)
	@rm -f $(LIB_OBJ)
	@gcc $(CFLAGS) -o gcov_r $(GFLAGS) $(TEST_SRC) -L. -l:$(LIB_NAME) $(TFLAGS)
	@mkdir -p coverage_report
	@./gcov_r
	@gcovr -r . --html --html-details -o coverage_report/index.html --exclude '.*test.*'
	@rm -rf $(LIB_OBJ) $(TEST_OBJ) s21_utils.o *.gcno *.gcda *.gcov gcov_r
	@cat pics/rats.txt


%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(LIB_OBJ) $(LIB_NAME) $(TEST_OBJ) s21_utils.o *.gcno *.gcda *.gcov gcov_r
	@rm -rf coverage_report

clean_gcov:
	@rm -rf coverage_report