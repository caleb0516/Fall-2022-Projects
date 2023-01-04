CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: src/main.cc src/seam_carver.cc src/image_ppm.cc includes/image_ppm.hpp includes/seam_carver.hpp
	${CXX} ${CXX_FLAGS} src/main.cc src/seam_carver.cc src/image_ppm.cc -o bin/exec

bin/tests: tests/tests.cc src/seam_carver.cc src/image_ppm.cc includes/image_ppm.hpp includes/seam_carver.hpp
	${CXX} ${CXX_FLAGS} tests/tests.cc src/seam_carver.cc src/image_ppm.cc -o bin/tests

.DEFAULT_GOAL := tests
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*