	CC = gcc
DELETE = rm -rf

VALGRIND_OUTPUT = valgrind.txt

BUILD_FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic -fanalyzer
GTK_FLAGS = `pkg-config gtk+-3.0 --cflags`
GTK_LIBS = `pkg-config gtk+-3.0 --libs`
VALGRIND_FLAGS = --log-file="$(VALGRIND_OUTPUT)" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med
LIBS_FLAGS = -lcheck

SRC_C_FILES = s21_structs/*.c s21_calculate/*.c
GUI_C_FILES = s21_gtk_gui/*.c
TEST_C_FILES = tests/*.c

TEST_TARGET  = s21_test
MAIN_TARGET = s21_main

REPORT_DIR = report

INCLUDES = . 

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS_FLAGS += -lsubunit -lm
endif

#ifeq ($(UNAME_S),Darwin)
#	something for MACOS
#endif

all: clean test gcov_report $(LIB)

apply_clang: 
	cp ../materials/linters/.clang-format .
	clang-format -i *.[ch] || true
	clang-format -i */*.[ch] || true
	rm -f .clang-format

test: apply_clang $(SRC_C_FILES)
	$(CC) $(BUILD_FLAGS) $(addprefix -I , $(INCLUDES))	 $(SRC_C_FILES) $(TEST_C_FILES) -o $(TEST_TARGET) $(LIBS_FLAGS)
	./$(TEST_TARGET)

build_test: apply_clang $(SRC_C_FILES)
	$(CC) $(BUILD_FLAGS) $(addprefix -I , $(INCLUDES)) $(SRC_C_FILES) $(TEST_C_FILES) -o $(TEST_TARGET) $(LIBS_FLAGS)

build: apply_clang $(SRC_C_FILES)
	$(CC) $(BUILD_FLAGS) $(GTK_FLAGS) $(addprefix -I , $(INCLUDES)) $(GUI_C_FILES) $(SRC_C_FILES) main.c -o $(MAIN_TARGET) $(LIBS_FLAGS) $(GTK_LIBS)
	./$(MAIN_TARGET)

gcov_report: apply_clang
	$(CC) --coverage $(BUILD_FLAGS) $(addprefix -I , $(INCLUDES)) $(SRC_C_FILES) $(TEST_C_FILES) -o $(TEST_TARGET) $(LIBS_FLAGS)
	./$(TEST_TARGET)
	lcov -t "$(TEST_TARGET)" -o $(TEST_TARGET).info -c -d .
	genhtml -o report $(TEST_TARGET).info
	rm *.gcda *.gcno *.info
	open report/index.html

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

clean:
	$(DELETE) $(TEST_TARGET)
	$(DELETE) $(MAIN_TARGET)
	$(DELETE) $(REPORT_DIR)
	$(DELETE) *.info
	$(DELETE) $(LIB)
	$(DELETE) *.o
	$(DELETE) *.gc*
	$(DELETE) $(VALGRIND_OUTPUT)
	$(DELETE) tempfile.png

valgrind: apply_clang build_test
	valgrind $(VALGRIND_FLAGS) ./$(TEST_TARGET)
	grep --color=always -n "ERROR SUMMARY" $(VALGRIND_OUTPUT) | grep -v "0 errors from 0 contexts" || true
	grep --color=always -n "definitely lost:" $(VALGRIND_OUTPUT) | grep -v "0 bytes in 0 blocks" || true
