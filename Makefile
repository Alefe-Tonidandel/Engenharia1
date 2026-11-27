FLAGS = -std=c++17 -Wall -Wextra -Isrc
PICFLAGS = $(FLAGS) -fPIC
LDFLAGS = -Lbin -lfabrica -lservico -ldados -Wl,-rpath,bin

DADOS_SRC = src/banco_impl.cpp src/data.cpp src/dinheiro.cpp src/item_estoque.cpp \
            src/lote_impl.cpp src/produto_impl.cpp src/sessao_impl.cpp \
            src/usuario_impl.cpp src/venda_impl.cpp
SERVICO_SRC = src/servico_cadastros_impl.cpp src/servico_estoque.cpp
FABRICA_SRC = src/fabrica.cpp

DADOS_OBJ = $(patsubst src/%.cpp,bin/%.pic.o,$(DADOS_SRC))
SERVICO_OBJ = $(patsubst src/%.cpp,bin/%.pic.o,$(SERVICO_SRC))
FABRICA_OBJ = $(patsubst src/%.cpp,bin/%.pic.o,$(FABRICA_SRC))

LIB_DADOS = bin/libdados.so
LIB_SERVICO = bin/libservico.so
LIB_FABRICA = bin/libfabrica.so
LIBS = $(LIB_DADOS) $(LIB_SERVICO) $(LIB_FABRICA)

all: $(LIBS) bin/app bin/unit_testes bin/func_testes

bin/%.pic.o: src/%.cpp
	mkdir -p bin
	g++ $(PICFLAGS) -c $< -o $@

$(LIB_DADOS): $(DADOS_OBJ)
	mkdir -p bin
	g++ -shared -o $@ $^

$(LIB_SERVICO): $(SERVICO_OBJ) $(LIB_DADOS)
	mkdir -p bin
	g++ -shared -o $@ $(SERVICO_OBJ) -Lbin -ldados -Wl,-rpath,bin

$(LIB_FABRICA): $(FABRICA_OBJ) $(LIB_SERVICO) $(LIB_DADOS)
	mkdir -p bin
	g++ -shared -o $@ $(FABRICA_OBJ) -Lbin -lservico -ldados -Wl,-rpath,bin

build: $(LIBS)
	mkdir -p bin
	g++ $(FLAGS) src/main.cpp $(LDFLAGS) -o bin/app

run: build
	./bin/app

build_unit: $(LIBS)
	mkdir -p bin
	g++ $(FLAGS) test/unit/*.cpp $(LDFLAGS) -o bin/unit_testes

run_unit: build_unit
	./bin/unit_testes

build_func: $(LIBS)
	mkdir -p bin
	g++ $(FLAGS) test/funcional/*.cpp $(LDFLAGS) -o bin/func_testes

run_func: build_func
	./bin/func_testes

test: run_unit run_func

docs:
	doxygen Doxyfile

clean:
	rm -f bin/app bin/unit_testes bin/func_testes bin/*.so bin/*.pic.o

.PHONY: all build run build_unit run_unit build_func run_func test docs clean
