MODULO = $(filter-out src/main.cpp, $(wildcard src/*.cpp))
OBJ_PIC = $(patsubst src/%.cpp,bin/%.pic.o,$(MODULO))
LIB_SO = bin/libbompreco.so
FLAGS = -std=c++17 -Wall -Wextra -Isrc
LDFLAGS = -Lbin -lbompreco -Wl,-rpath,bin

all: $(LIB_SO) bin/app bin/unit_testes bin/func_testes

$(LIB_SO): $(OBJ_PIC)
	mkdir -p bin
	g++ -shared -o $@ $^

bin/%.pic.o: src/%.cpp
	mkdir -p bin
	g++ $(FLAGS) -fPIC -c $< -o $@

build: $(LIB_SO)
	mkdir -p bin
	g++ $(FLAGS) src/main.cpp $(LDFLAGS) -o bin/app

run: build
	./bin/app

build_unit: $(LIB_SO)
	mkdir -p bin
	g++ $(FLAGS) test/unit/*.cpp $(LDFLAGS) -o bin/unit_testes

run_unit: build_unit
	./bin/unit_testes

build_func: $(LIB_SO)
	mkdir -p bin
	g++ $(FLAGS) test/funcional/*.cpp $(LDFLAGS) -o bin/func_testes

run_func: build_func
	./bin/func_testes

test: run_unit run_func

docs:
	doxygen Doxyfile

clean:
	rm -f bin/app bin/unit_testes bin/func_testes bin/libbompreco.so bin/*.pic.o

.PHONY: all build run build_unit run_unit build_func run_func test docs clean
