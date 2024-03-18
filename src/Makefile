CC=g++
LIB_NAME=s21_smartcalc_v2.0.h
CC_FLAGS=-Wall -Werror -Wextra -std=c++17
GCOV_FLAGS=-coverage 
PACKAGE = s21_calc_V2.0
LGTEST_FLAGS = -lgtest -lgtest_main -pthread
SOURCES := $(shell find model/ -name "*.cc" ! -name "*_test*")
ifeq ($(OS), Linux)
  OPEN=xdg-open
else
  OPEN=open
endif

all: clean test install

test:
	g++ -c $(SOURCES)  -Wall -Werror -Wextra -std=c++17
	@$(CC) *.o model/tests.cpp -o test $(CC_FLAGS) $(LGTEST_FLAGS) -g
	@./test

install:
	@echo "Installing SmartCalc v2.0..."
	@mkdir -p release
	@cd view && qmake && make && make clean && rm -rf Makefile && mv SmartCalc_v2.app ../release/SmartCalc_v2.app
	@cp -R release/SmartCalc_v2.app ~/Desktop/SmartCalc_v2.app
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃    The project is located in the        ┃"
	@echo "┃    release folder and                   ┃"
	@echo "┃    on the desktop.                      ┃"
	@echo "┗=========================================

uninstall:
	@echo "Removing SmartCalc_v2.."
	@rm -rf ~/Desktop/SmartCalc_v2.app release view/.qmake.stash
	@echo "┏=========================================┓"
	@echo "┃     Uninstall completed successfully    ┃"
	@echo "┗=========================================┛"

start:
	open ~/Desktop/SmartCalc_v2.app

dvi:
	open documentation.md

clean:
	@rm -rf *.o *.gcda *.gcno *.info
	@rm -rf docs
	@rm -rf build
	@rm -rf html
	@rm -rf latex
	@rm -f info
	@rm -f *.a
	@rm -f *.gz
	@rm -f *.out
	@rm -rf report
	@rm -f test
	@rm -rf *.dSYM

format:
	clang-format -style=google -i */*.cc
	clang-format -style=google -i */*.h
	clang-format -style=google -i */*.cpp

dist:
	mkdir $(PACKAGE)
	cp -r ./controller $(PACKAGE)
	cp -r ./model $(PACKAGE)
	cp -r ./view $(PACKAGE)
	cp Makefile $(PACKAGE)
	tar -czf $(PACKAGE).tar.gz $(PACKAGE)
	rm -rf $(PACKAGE)

