CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11
TFLAGS = -lcheck -lsubunit -lm
GFLAGS = -fprofile-arcs -ftest-coverage

MAIN_SRC = brick_game/brick_game.c
MAIN_OBJ = $(MAIN_SRC:.c=.o)
BRICK_SRC = brick_game/helper.c brick_game/bg_objects.c
BRICK_OBJ = $(BRICK_SRC:.c=.o)
EXEC = build/brick_game
TETRIS_LIB = tetris.a
TETRIS_SRC = $(wildcard ./brick_game/tetris/*.c) 
TETRIS_OBJ = $(TETRIS_SRC:.c=.o)
CLI_LIB = interface.a
CLI_SRC = gui/cli/interface.c
CLI_OBJ = $(CLI_SRC:.c=.o)
DIST_NAME = brick_game.tar.gz
TEST_SRC = tests/test.c
TEST_GCDA = $(TETRIS_SRC:.c=.gcda)
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(TETRIS_LIB)

clear: 
	clear
	
install: $(MAIN_OBJ) $(BRICK_OBJ) $(CLI_OBJ) $(TETRIS_LIB)
	@$(CC) $(CFLAGS) $(MAIN_OBJ) $(BRICK_OBJ) $(CLI_OBJ) -o $(EXEC) -L. -l:$(TETRIS_LIB) -lm -lncursesw 
	@rm -f $(MAIN_OBJ) $(BRICK_OBJ) $(CLI_OBJ)

uninstall:
	@rm -rf $(EXEC)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(TETRIS_LIB): $(TETRIS_OBJ)
	@ar rcs $(TETRIS_LIB) $(TETRIS_OBJ)
	@ranlib $(TETRIS_LIB)
	@rm -f $(TETRIS_OBJ)

dvi:
	@xelatex -output-directory=build build/documentation.tex

dist: install
	@tar -czvf $(DIST_NAME)  Makefile brick_game gui tests

test: $(TEST_OBJ) $(BRICK_OBJ) $(TETRIS_LIB)
	@$(CC) $(CFLAGS) $(TEST_OBJ) $(BRICK_OBJ) -o test -L. -l:$(TETRIS_LIB) $(TFLAGS)
	@rm -f $(TEST_OBJ)
	@./test

gcov_report: clean add_coverage $(TETRIS_OBJ) $(TETRIS_LIB) 
	@$(CC) $(CFLAGS) -o gcov_r $(TEST_SRC) $(BRICK_SRC) -L. -l:$(TETRIS_LIB) $(TFLAGS)
	@mkdir coverage_report
	@./gcov_r
	@python3 -m gcovr -r . --html --html-details -o coverage_report/index.html --exclude test
	@open coverage_report/index.html

run: install
	./$(EXEC)

style_check:
	@cp ../materials/linters/.clang-format .
	@clang-format -n brick_game/*.c brick_game/*.h brick_game/tetris/*.c brick_game/tetris/*.h gui/cli/*.c gui/cli/*.h tests/test.c
	@cppcheck --enable=all --suppress=missingIncludeSystem brick_game/*.c brick_game/*.h brick_game/tetris/*.c brick_game/tetris/*.h gui/cli/*.c gui/cli*.h tests/test.c

leak_check: 
	@valgrind --tool=memcheck --leak-check=yes ./test

clean:
	@rm -f $(TEST_OBJ) $(MAIN_OBJ) $(BRICK_OBJ)
	@rm -f $(TETRIS_LIB) test gcov* coverage.info *.gcda *.gcno tests/*.gcno brick_game/*.gcda brick_game/*.gcno brick_game/tetris/*.gcda brick_game/tetris/*.gcno
	@rm -rf coverage_report


add_coverage:
	$(eval CFLAGS:=$(CFLAGS) $(GFLAGS))

re: clean all

# установка enumitem: sudo apt-get install texlive-latex-extra
# установка gcovr: sudo apt install gcovr
# установка ncurses: sudo apt-get install libncurses5-dev libncursesw5-dev
# установка xelatex: sudo apt-get install texlive-latex-extra (если не работает прописать в маке абсолютный путь)
