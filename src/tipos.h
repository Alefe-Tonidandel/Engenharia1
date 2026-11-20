/**
 * @file tipos.h
 * @brief Tipos comuns do sistema: perfis, cod de erro e Resultado
 */
#ifndef TIPOS_H
#define TIPOS_H

#include <string>

// Perfis de acesso
/**
 * @brief Perfis da rede
 * 
 */
enum class Perfil { OperadorCaixa, RepositorEstoque, GerenteUnidade,
                    GestorRede, Administrador };

// Um codigo de erro por regra de negocio
/**
 * @brief Possiveis erros para as operações
 * 
 */
enum class Erro { Nenhum, CampoVazio, Duplicado, QuantidadeInvalida,
                  CustoInvalido, PrecoAbaixoDoCusto, ValidadeVencida,
                  ProdutoSemPreco, NaoEncontrado, EstoqueInsuficiente,
                  UnidadeNaoInformada, AcessoNegado };


                  
// (struct simples de dados: a copia gerada pelo compilador ja e correta)
/**
 * @brief Resultado
 * @details Toda operação devolve um resultado: valor, erro e uma mensagem
 * 
 * @tparam Tipo
 */
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
