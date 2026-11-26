/**
 * @file unit_LoteEstoqueImpl.h 
 * @brief Testes unitarios da classe loteEstoqueImpl
 * 
 */
#ifndef UNIT_LOTEESTOQUEIMPL
#define UNIT_LOTEESTOQUEIMPL

void unit_LoteEstoqueImpl_construtor(void);         ///< Testa os construtores
void unit_LoteEstoqueImpl_copyConstrutor(void);     ///< Testa o construtor de copia
void unit_LoteEstoqueImpl_operatorAtribuicao(void);  ///< Testa o operator=
void unit_LoteEstoqueImpl_destrutor(void);          ///< Testa o destrutor
void unit_LoteEstoqueImpl_id(void);                  ///< Testa id()
void unit_LoteEstoqueImpl_idUnidade(void);           ///< Testa idUnidade()
void unit_LoteEstoqueImpl_codigoProduto(void);       ///< Testa codigoProduto()
void unit_LoteEstoqueImpl_quantidadeInicial(void);   ///< Testa quantidadeInicial()
void unit_LoteEstoqueImpl_saldo(void);               ///< Testa saldo()
void unit_LoteEstoqueImpl_dataEntrada(void);         ///< Testa dataEntrada()
void unit_LoteEstoqueImpl_validade(void);            ///< Testa validade()
void unit_LoteEstoqueImpl_vencido(void);             ///< Testa vencido()
void unit_LoteEstoqueImpl_baixar(void);              ///< Testa baixar()
void run_unit_tests_LoteEstoqueImpl(void);           ///< Roda todos os testes de LoteEstoqueImpl


#endif