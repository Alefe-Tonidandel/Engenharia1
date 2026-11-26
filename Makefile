MODULO = $(filter-out src/main.cpp, $(wildcard src/*.cpp))
FLAGS = -std=c++17 -Wall -Wextra -Isrc

build:
	mkdir -p bin
	g++ $(FLAGS) src/main.cpp $(MODULO) -o bin/app
run: build
	./bin/app

build_unit:
	mkdir -p bin
	g++ $(FLAGS) test/unit/*.cpp $(MODULO) -o bin/unit_testes

run_unit: build_unit
	./bin/unit_testes

build_func:
	mkdir -p bin
	g++ $(FLAGS) test/funcional/*.cpp $(MODULO) -o bin/func_testes

run_func: build_func
	./bin/func_testes

# usado pelo CI do GitHub
test: run_unit run_func

docs:
	doxygen Doxyfile
	-explorer.exe "$$(wslpath -w docs/html/index.html)"

clean:
	rm -f bin/app bin/unit_testes bin/func_testes

.PHONY: build run build_unit run_unit build_func run_func test docs clean