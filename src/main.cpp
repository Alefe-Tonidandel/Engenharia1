#include <iostream>
#include "fabrica.h"
#include "usuario_impl.h"
#include "data.h"
#include "dinheiro.h"

int main() {
    Fabrica fabrica;
    Banco* banco = fabrica.criarBanco();

    Relogio::fixar(Data(2026, 10, 26));
    UsuarioImpl uGestor(10, "Rafael Lima", Perfil::GestorRede, 0);
    Sessao* gestor = fabrica.criarSessao(uGestor);
    ServicoCadastros* cadastros = fabrica.criarServicoCadastros(*gestor, *banco);

    DadosProduto tomate = {"BP-1265", "Tomate italiano (kg)", "Hortifruti",
                           Dinheiro::reais(8.40), 20};
    cadastros->cadastrarProduto(tomate);
    cadastros->definirPrecoPadrao("BP-1265", Dinheiro::reais(11.20));

    UsuarioImpl uRepo(21, "Joana Reis", Perfil::RepositorEstoque, 1);
    Sessao* repo = fabrica.criarSessao(uRepo);
    ServicoEstoque* estoque = fabrica.criarServicoEstoque(*repo, *banco);
    estoque->registrarEntrada("BP-1265", 30, Data(2026, 10, 30));
    estoque->registrarEntrada("BP-1265", 50, Data(2026, 11, 5));

    Relogio::fixar(Data(2026, 10, 31));
    UsuarioImpl uOp(31, "Pedro Alves", Perfil::OperadorCaixa, 1);
    Sessao* op = fabrica.criarSessao(uOp);
    ServicoEstoque* caixa = fabrica.criarServicoEstoque(*op, *banco);

    Resultado<const Venda*> v = caixa->registrarVenda("BP-1265", 2);
    if (v.ok())
        std::cout << "Venda " << v.valor->id() << ": " << v.valor->quantidade()
                  << " x " << v.valor->codigoProduto() << " = "
                  << v.valor->valorTotal() << "\n";

    Resultado<const Venda*> e = caixa->registrarVenda("BP-1265", 60);
    if (!e.ok())
        std::cout << "Venda recusada: " << e.mensagem << "\n";

    const LoteEstoque* l1 = banco->buscarLote(1);
    const LoteEstoque* l2 = banco->buscarLote(2);
    if (l1 && l2)
        std::cout << "Lote 1 (vence " << l1->validade() << "): saldo " << l1->saldo()
                  << "\nLote 2 (vence " << l2->validade() << "): saldo " << l2->saldo()
                  << "\n";

    delete caixa;
    delete op;
    delete estoque;
    delete repo;
    delete cadastros;
    delete gestor;
    delete banco;
    return 0;
}
