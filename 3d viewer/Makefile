CC = g++

TEST_SRC = $(wildcard viewer/obj/obj.cpp viewer/obj/model_info.cpp viewer/obj/setting_info.cpp viewer/test/test.cpp)
TEST_FILES = $(wildcard viewer/obj/parse.cpp viewer/obj/obj.cpp viewer/obj/model_info.cpp viewer/obj/setting_info.cpp viewer/paint/figure.cpp viewer/paint/point.cpp)
TEST_EXEC = test.out

GFLAG = -fprofile-arcs -ftest-coverage
TFLAG = -lgtest -lgtest_main -pthread -lstdc++ -lsupc++ -lgcc
CFLAGS = -Wall -Wextra -Werror -std=c++17 -g

MAIN_SRC= $(wildcard 3D_Viewer_2.0.cpp )
MAIN_OBJ= $(patsubst %.cpp,%.o,$(MAIN_SRC))

VIEW_SRC= $(wildcard ./desktop/*.cpp )
VIEW_OBJ= $(patsubst %.cpp,%.o,$(VIEW_SRC))
VIEW_LIB = s21_view.a

CNTRL_SRC= $(wildcard ./controller/*.cpp )
CNTRL_OBJ= $(patsubst %.cpp,%.o,$(CNTRL_SRC))
CNTRL_LIB = s21_controller.a

MODEL_SRC = $(wildcard ./viewer/*/*.cpp )
MODEL_OBJ = $(SCREEN_SRC:.cpp=.o)
MODEL_LIB = s21_model.a

BUILD_DIR = build
EXEC = 3D_Viewer_2.0

all: install run

$(VIEW_LIB): $(VIEW_OBJ)
	@ar rcs $(VIEW_LIB) $(VIEW_OBJ) 
	@ranlib $(VIEW_LIB)
	@rm -f $(VIEW_OBJ) 
.PHONY: $(VIEW_LIB)

$(CNTRL_LIB): $(CNTRL_OBJ)
	@ar rcs $(CNTRL_LIB) $(CNTRL_OBJ) 
	@ranlib $(CNTRL_LIB)
	@rm -f $(CNTRL_OBJ) 
.PHONY: $(CNTRL_LIB)

$(MODEL_LIB): $(MODEL_OBJ) 
	@ar rcs $(MODEL_LIB) $(MODEL_OBJ) 
	@ranlib $(MODEL_LIB)
	@rm -f $(MODEL_OBJ) 
.PHONY: $(MODEL_LIB)

install:
	@clear
	@cd desktop && qmake desktop.pro -o Makefile.viewer
	@$(MAKE) -C desktop -f Makefile.viewer
	@mkdir -p $(BUILD_DIR)
	@mv desktop/desktop $(BUILD_DIR)/$(EXEC)
	@rm -f $(CNTRL_OBJ) $(MODEL_OBJ) $(VIEW_OBJ) $(MAIN_OBJ) desktop/*.o
.PHONY: install

run: install
	@./$(BUILD_DIR)/$(EXEC)
.PHONY: run

uninstall:
	@rm -rf $(BUILD_DIR) ../setting.txt *.a
.PHONY: uninstall

reinstall: clean uninstall install

dvi: 
	# sudo apt-get install texlive-xetex
	# sudo apt-get install texlive-lang-cyrillic
	# sudo apt-get install doxygen
	@clear
	@cp docs/Doxyfile .
	@cp docs/README.md .
	@doxygen Doxyfile
	@cd latex && make
	@open latex/refman.pdf
	@rm -rf Doxyfile README.md latex/*.tex latex/*.tmp latex/*.aux latex/*.log latex/*.out latex/*.dot latex/*.sty latex/*.idx latex/*.toc latex/*.jpg latex/*.png latex/*.ilg latex/*.ind latex/Makefile
.PHONY: dvi

dist: install
	@clear
	@tar -cvzf 3d_viewer_2.0.tgz $(BUILD_DIR)
.PHONY: dist

gcov_report: clean 
	@clear 
	@$(CC) $(CFLAGS) -g -c viewer/obj/parse.cpp -o parce.o --coverage
	@$(CC) $(CFLAGS) -g -c viewer/paint/figure.cpp -o figure.o --coverage
	@$(CC) $(CFLAGS) -g -c viewer/paint/point.cpp -o point.o --coverage
	@$(CC) $(CFLAGS) $(GFLAG) -o gcov_r $(TEST_SRC) point.o  parce.o figure.o $(TFLAG)
	@mkdir coverage_report
	@./gcov_r
	@python3 -m gcovr -r . --html --html-details -o coverage_report/index.html --exclude viewer/obj/obj.cpp --exclude viewer/obj/model_info.cpp --exclude viewer/obj/setting_info.cpp --exclude viewer/test/test.cpp --exclude viewer/obj/tiny_obj_loader.h --exclude viewer/obj/obj.hpp
	@rm -f *.gcno *.gcda *.o gcov_r coverage.info
	@rm -f */*/*.gcno */*/*.gcda */*.gcno */*.gcda
.PHONY: gcov_report

leak_check: test
	@clear
	@valgrind --tool=memcheck --leak-check=yes ./$(TEST_EXEC)
.PHONY: leak_check

style_check: 
	@clear
	@cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ $(TEST_SRS) $(VIEW_SRC) $(MODEL_SRC) $(MAIN_SRC) $(CNTRL_SRC)
.PHONY: cpp_check

google_check:
	@clear
	@cp ../materials/linters/.clang-format .
	@clang-format -n *.cpp */*.cpp */*.h */*/*.cpp */*/*.h */*/*.hpp
.PHONY: clang_check

g_edit:
	@clear
	@cp ../materials/linters/.clang-format .
	@clang-format -i *.cpp */*.cpp */*.h */*/*.cpp */*/*.h */*/*.hpp
.PHONY: clang_check

clean: uninstall
	@rm -f $(TEST_EXEC)
	@rm -rf latex html */*.o
	@rm -rf coverage_report gcov_r Doxyfile README.md setting.txt
	@rm -f desktop/Makefile.viewer desktop/.qmake.stash 
	@rm -f desktop/ui_mainwindow.h desktop/*.user desktop/moc*
.PHONY: clean

tests: clean 
	@clear
	@g++ $(CFLAGS) viewer/test/test.cpp $(TEST_FILES) -o $(TEST_EXEC) $(TFLAG)
	@./$(TEST_EXEC)

%.o: %.cpp
	@$(CC) $(CFLAGS) $(GIF_FLAG) -cpp $< -o $@

add_coverage:
	$(eval CFLAGS:=$(CFLAGS) $(GFLAGS))
