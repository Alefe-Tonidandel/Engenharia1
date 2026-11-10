// Bom-Preco - demonstracao do produto (Sprint 3)
#include <iostream>
#include "banco.h"
#include "servico_cadastros.h"
#include "servico_estoque.h"

int main() {
    Banco banco;

    // Gestor da Rede: catalogo e preco padrao
    Relogio::fixar(Data(2026, 10, 26));
    Sessao gestor(Usuario(10, "Rafael Lima", Perfil::GestorRede, 0));
    ServicoCadastros cadastros(gestor, banco);
    DadosProduto tomate = {"BP-1265", "Tomate italiano (kg)", "Hortifruti",
                           Dinheiro::reais(8.40), 20};
    cadastros.cadastrarProduto(tomate);
    cadastros.definirPrecoPadrao("BP-1265", Dinheiro::reais(11.20));

    // Repositor de Estoque (unidade 1): entradas
    Sessao repo(Usuario(21, "Joana Reis", Perfil::RepositorEstoque, 1));
    ServicoEstoque estoque(repo, banco);
    estoque.registrarEntrada("BP-1265", 30, Data(2026, 10, 30));   // lote 1
    estoque.registrarEntrada("BP-1265", 50, Data(2026, 11, 5));    // lote 2

    // Operador de Caixa (unidade 1): venda em 31/10, quando o lote 1 ja venceu
    Relogio::fixar(Data(2026, 10, 31));
    Sessao op(Usuario(31, "Pedro Alves", Perfil::OperadorCaixa, 1));
    ServicoEstoque caixa(op, banco);

    Resultado<Venda> v = caixa.registrarVenda("BP-1265", 2);
    if (v.ok())
        std::cout << "Venda " << v.valor.id() << ": " << v.valor.quantidade()
                  << " x " << v.valor.codigoProduto() << " = "
                  << v.valor.valorTotal() << "\n";

    Resultado<Venda> e = caixa.registrarVenda("BP-1265", 60);
    if (!e.ok())
        std::cout << "Venda recusada: " << e.mensagem << "\n";

    const LoteEstoque* l1 = banco.buscarLote(1);
    const LoteEstoque* l2 = banco.buscarLote(2);
    std::cout << "Lote 1 (vence " << l1->validade() << "): saldo " << l1->saldo()
              << " (vencido, nao foi usado)\n"
              << "Lote 2 (vence " << l2->validade() << "): saldo " << l2->saldo()
              << "\n";
    return 0;
}
