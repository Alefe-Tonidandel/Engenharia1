#ifndef TIPOS_H
#define TIPOS_H

#include <string>

// Perfis de acesso (Sprint 2, API final)
enum class Perfil { OperadorCaixa, RepositorEstoque, GerenteUnidade,
                    GestorRede, Administrador };

// Um codigo de erro por regra de negocio
enum class Erro { Nenhum, CampoVazio, Duplicado, QuantidadeInvalida,
                  CustoInvalido, PrecoAbaixoDoCusto, ValidadeVencida,
                  ProdutoSemPreco, NaoEncontrado, EstoqueInsuficiente,
                  UnidadeNaoInformada, AcessoNegado };

// Toda operacao da API devolve Resultado<T>: o valor, o erro e uma mensagem.
// (struct simples de dados: a copia gerada pelo compilador ja e correta)
template <typename T>
struct Resultado {
    T           valor;
    Erro        erro;
    std::string mensagem;

    Resultado() : valor(), erro(Erro::Nenhum), mensagem() {}
    bool ok() const { return erro == Erro::Nenhum; }

    static Resultado sucesso(const T& v) {
        Resultado r; r.valor = v; return r;
    }
    static Resultado falha(Erro e, const std::string& msg) {
        Resultado r; r.erro = e; r.mensagem = msg; return r;
    }
};

#endif
