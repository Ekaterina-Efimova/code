CC = gcc
TEST_SRC = $(wildcard tests/*.c)
TEST_OBJ = $(patsubst %.c,%.o,$(TEST_SRC))
TEST_FILES = $(wildcard gtk/s21_parce.c gtk/s21_matrix.c)
TEST_FILES_OBJ = $(patsubst %.c,%.o,$(TEST_FILES))
TEST_EXEC = tests/test

GIF_FLAG = -lgif
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
GTK_FLAG = `pkg-config --cflags --libs gtk+-3.0 cairo epoxy`
GFLAG = -fprofile-arcs -ftest-coverage
TFLAG = -lcheck -lsubunit -lm

MAIN_SRC = 3d_viewer.c
DSK_SRC = $(wildcard ./desktop/*.c )
DSK_OBJ = $(patsubst %.c,%.o,$(DSK_SRC))
GTK_SRC = $(wildcard ./gtk/*.c )
GTK_OBJ = $(patsubst %.c,%.o,$(GTK_SRC))
PARAM = 2>/dev/null
GTK_LIB = s21_gtk.a

BUILD_DIR = build
EXEC = 3D_Viewer

all: run

%.o: %.c
	@gcc $(GTK_FLAG) $(GIF_FLAG) -lglut -lGL -I./lib/glm -lm -c $< -o $@

$(GTK_LIB): $(GTK_OBJ) $(DSK_OBJ)
	@ar rcs $(GTK_LIB) $(GTK_OBJ) $(DSK_OBJ)
	@ranlib $(GTK_LIB)
	@rm -f $(GTK_OBJ) $(DSK_OBJ)
.PHONY: $(GTK_LIB)

install: clear clean $(GTK_LIB) 
	@mkdir $(BUILD_DIR)
	@$(CC) $(MAIN_SRC) -o $(BUILD_DIR)/$(EXEC) $(CFLAGS) -L. -l:$(GTK_LIB) $(GTK_FLAG) $(GIF_FLAG) -lglut -lGL -I./lib/glm -lm 
.PHONY: install

run: install
	@./$(BUILD_DIR)/$(EXEC) $(PARAM)
.PHONY: run

uninstall:
	@rm -rf $(BUILD_DIR)
.PHONY: uninstall

dvi: clear
	# sudo apt-get install texlive-xetex
	# sudo apt-get install texlive-lang-cyrillic
	# sudo apt-get install doxygen
	@cp docs/Doxyfile .
	@cp docs/README.md .
	@doxygen Doxyfile
	@cd latex && make
	@open latex/refman.pdf
	@rm -rf Doxyfile README.md latex/*.tex latex/*.tmp latex/*.aux latex/*.log latex/*.out latex/*.dot latex/*.sty latex/*.idx latex/*.toc latex/*.jpg latex/*.png latex/*.ilg latex/*.ind latex/Makefile
.PHONY: dvi

dist: install
	@tar -cvzf breack_game.tgz $(BUILD_DIR)
.PHONY: dist

test: $(TEST_OBJ)
	@clear
	@gcc $(TEST_OBJ) -o $(TEST_EXEC) $(TEST_FILES) -lcheck -lm -lrt -lpthread -lsubunit -g
	@./$(TEST_EXEC)
.PHONY: test

gcov_report: clear clean
	@$(CC) $(CFLAGS) -g -c  gtk/s21_parce.c -o s21_parce.o --coverage
	@$(CC) $(CFLAGS) -g -c   gtk/s21_matrix.c -o s21_matrix.o --coverage
	@$(CC) $(CFLAGS) $(GFLAG) -o gcov_r $(TEST_SRC) s21_parce.o s21_matrix.o $(TFLAG)
	@mkdir coverage_report
	@./gcov_r
	@python3 -m gcovr -r . --html --html-details -o coverage_report/index.html --exclude test
	@rm -f *.gcno *.gcda *.o gcov_r
	@rm -f */*/*.gcno */*/*.gcda
	@rm -f */*.gcno */*.gcda
.PHONY: gcov_report

leak_check: clear
	@valgrind --tool=memcheck --leak-check=yes ./$(TEST_EXEC)
.PHONY: leak_check

cpp_check: clear
	@cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ $(TEST_SRS) $(GTK_SRC) $(DSK_SRC) $(MAIN_SRC)
.PHONY: cpp_check

clang_check: clear
	@cp ../materials/linters/.clang-format .
	@clang-format -n $(TEST_SRC) $(GTK_SRC) $(DSK_SRC) $(MAIN_SRC)
.PHONY: clang_check

clear:
	clear
.PHONY: clear

clean:
	@rm -f $(TEST_OBJ) $(TEST_EXEC)
	@rm -rf $(BUILD_DIR) latex html
	@rm -f $(GTK_LIB)
	@rm -rf coverage_report gcov_r
.PHONY: clean

lib_install:
	sudo apt-get update
	sudo apt install libgtk-3-dev libcairo2-dev
# OpenGL 
	sudo apt install freeglut3-dev 
# Gif
	sudo apt-get install libgif-dev
# для установки gtk3:  sudo apt install libgtk-3-dev
# для установки cairo: sudo apt install libcairo2-dev
# для установки giflib: sudo apt-get install libgif-dev
# sudo apt-get install freeglut3-dev