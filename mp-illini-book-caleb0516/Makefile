INCLUDES=-I includes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -O0 -Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX=clang++

clean:
	rm -f bin/*

exec: src/driver.cc src/illini_book/.cc src/utilities.cc
	$(CXX) $(CXXFLAGS) $^ -o bin/exec

tests: tests/tests.cc src/illini_book.cc src/utilities.cc
	$(CXX) $(CXXFLAGS) $^ -o bin/tests

src/%.cc: includes/%.hpp
	touch $@

.DEFAULT_GOAL := tests
.PHONY: tests clean exec