CC = g++

CFLAGS = -Wall -Wextra -Werror -std=c++17
GFLAGS = -fprofile-arcs -ftest-coverage
TFLAGS = -lgtest -lgtest_main

TETRIS_LIB = tetris.a
TETRIS_SRC = $(wildcard ./brick_game/tetris/*.c)
TETRIS_OBJ = $(TETRIS_SRC:.c=.o)

SNAKE_LIB = snake.a 
SNAKE_SRC = $(wildcard ./brick_game/snake/*.cpp)
SNAKE_OBJ =  $(SNAKE_SRC:.cpp=.o)

MAIN_SRC = brick_game/brick_game_ncurses.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

CLI_LIB = interface.a
CLI_SRC = gui/cli/interface.c gui/cli/bg_objects.c
CLI_OBJ = $(CLI_SRC:.c=.o)

TEST_SRC = tests/*.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

all: clear clean clean_dir install run

$(SNAKE_LIB): $(SNAKE_OBJ)
	@ar rcs $(SNAKE_LIB) $(SNAKE_OBJ)
	@ranlib $(SNAKE_LIB)
	@rm -f $(SNAKE_OBJ)

$(TETRIS_LIB): $(TETRIS_OBJ) 
	@ar rcs $(TETRIS_LIB) $(TETRIS_OBJ) 
	@ranlib $(TETRIS_LIB)
	@rm -f $(TETRIS_OBJ) 

install: clear clean  clean_dir $(MAIN_OBJ) $(CLI_OBJ) $(SNAKE_LIB) $(TETRIS_LIB) install_cli install_desktop 

run:
	@chmod 777 menu.sh
	@./menu.sh

uninstall:
	@rm -rf build

install_cli: clear clean clean_dir $(MAIN_OBJ) $(CLI_OBJ) $(SNAKE_LIB) $(TETRIS_LIB)
	@mkdir -p build
	@$(CC) $(CFLAGS) -DTETRIS $(MAIN_OBJ) $(CLI_OBJ) -o build/tetris_cli -L. -l:$(TETRIS_LIB) -lm -lncursesw
	@$(CC) $(CFLAGS) $(MAIN_OBJ) $(CLI_OBJ) -o build/snake_cli -L. -l:$(SNAKE_LIB) -lm -lncursesw
	@rm -f $(MAIN_OBJ) $(CLI_OBJ) $(TETRIS_OBJ) $(SNAKE_OBJ)

build_tetris_cli: clear clean $(MAIN_OBJ) $(CLI_OBJ) $(TETRIS_LIB)
	@mkdir -p build
	@$(CC) $(CFLAGS) -DTETRIS $(MAIN_OBJ) $(CLI_OBJ) -o build/tetris_cli -L. -l:$(TETRIS_LIB) -lm -lncursesw

build_snake_cli: clear clean $(MAIN_OBJ) $(CLI_OBJ) $(SNAKE_LIB)
	@mkdir -p build
	@$(CC) $(CFLAGS) $(MAIN_OBJ) $(CLI_OBJ) -o build/snake_cli -L. -l:$(SNAKE_LIB) -lm -lncursesw

run_tetris_cli:
	./build/tetris_cli

run_snake_cli:
	./build/snake_cli

valgrind: install_cli
	@valgrind --tool=memcheck --leak-check=yes ./$(EXEC)
	@echo "\n\n_______NCURSES GIVES LEAK, BUT IT'S NOT OUR ERRORS_______\n\n"

install_desktop: clear clean clean_dir $(SNAKE_LIB) $(TETRIS_LIB)
	@mkdir -p build tmp/tetris tmp/snake
	@cd tmp/tetris && cmake -DTETRIS=ON ../../ && make tetris_desktop
	@cd tmp/snake && cmake ../../ && make snake_desktop
	@mv tmp/tetris/tetris_desktop build/
	@mv tmp/snake/snake_desktop build/
	@rm -rf tmp

build_tetris_desktop: clear clean $(TETRIS_LIB)
	@mkdir -p build tmp/tetris
	@cd tmp/tetris && cmake -DTETRIS=ON ../../ && make tetris_desktop
	@mv tmp/tetris/tetris_desktop build/
	@rm -rf tmp

build_snake_desktop: clear clean $(SNAKE_LIB) 
	@mkdir -p build tmp/snake
	@cd tmp/snake && cmake ../../ && make snake_desktop 
	@mv tmp/snake/snake_desktop build/
	@rm -rf tmp

run_tetris_desktop: 
	./build/tetris_desktop

run_snake_desktop:
	./build/snake_desktop


cpp_check: clear
	@cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ tests/*.cpp tests/*.hpp brick_game/*.cpp brick_game/tetris/*.c gui/cli/*.c gui/desktop/*.cpp gui/desktop/*.h gui/cli/*.h brick_game/snake/*.cpp brick_game/snake/*.h brick_game/snake/*.hpp brick_game/tetris/*.h  common/*.cpp

clang_check: clear
	@cp ../materials/linters/.clang-format .
	@clang-format -n tests/*.cpp tests/*.hpp brick_game/*.cpp brick_game/tetris/*.c gui/cli/*.c gui/desktop/*.cpp gui/desktop/*.h gui/cli/*.h brick_game/snake/*.cpp brick_game/snake/*.h brick_game/snake/*.hpp brick_game/tetris/*.h  common/*.cpp

test: clear clean  $(SNAKE_LIB) $(TETRIS_LIB) 
	@$(CC) $(CFLAGS) -o test $(TEST_SRC)  -L. -l:$(SNAKE_LIB) -l:$(TETRIS_LIB) $(TFLAGS)
	@./test

leak_check: clear
	@valgrind --tool=memcheck --leak-check=yes ./test

gcov_report: clear clean_dir add_coverage $(SNAKE_OBJ) $(SNAKE_LIB) $(TETRIS_OBJ) $(TETRIS_LIB)  
	@$(CC) $(CFLAGS) -o gcov_r $(TEST_SRC)  -L. -l:$(SNAKE_LIB) -l:$(TETRIS_LIB) $(TFLAGS)
	@mkdir coverage_report
	@./gcov_r
	@python3 -m gcovr -r . --html --html-details -o coverage_report/index.html --exclude test
	@rm -f *.gcno *.gcda
	@rm -f */*/*.gcno */*/*.gcda
	@rm -f */*.gcno */*.gcda
	@rm -f 

dist: install
	@tar -cvzf breack_game.tgz build

clean:
	@rm -f $(SNAKE_OBJ) $(SNAKE_LIB) $(MAIN_OBJ) $(CLI_OBJ) $(TETRIS_OBJ) $(TETRIS_LIB) gcov_r test
	@rm -f *.gcno *.gcda *.gcov
	@rm -f */*/*.gcno */*/*.gcda
	@rm -f */*.gcno */*.gcda
	@rm -f dvi/*.log dvi/*.aux dvi/*.dvi dvi/*.pdf
	@rm -f breack_game.tgz
	@rm -rf build coverage_report

clean_dir:
	@rm -rf build

re: clean all

clear:
	@clear

add_coverage:
	$(eval CFLAGS:=$(CFLAGS) $(GFLAGS))

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

install_qt:
	@sudo apt-get install qt5-default

install_ncurses:
	@sudo apt-get install libncurses5-dev

install_gtest:
	@sudo apt-get install libgtest-dev

install_latex:
	@sudo apt-get install texlive-full

install_xelatex:
	@sudo apt-get install texlive-xetex

install_gcovr:
	@sudo apt-get install gcovr

install_cmake:
	@sudo apt-get install cmake