CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc
LIB      = $(filter-out src/main.cpp,$(wildcard src/*.cpp))

all: bin/bompreco bin/unit_tests bin/funcional_tests

bin/bompreco: src/main.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/unit_tests: test/unit/main.cpp test/unit/unit_tests.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/funcional_tests: test/funcional/main.cpp test/funcional/funcional_tests.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: all
	./bin/unit_tests
	./bin/funcional_tests

clean:
	rm -f bin/bompreco bin/unit_tests bin/funcional_tests
