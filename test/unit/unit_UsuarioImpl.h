//apenas as declaracoes: uma funcao pra cada metodo da classe + funcao run_... que chama todas
#ifndef UNIT_USUARIOIMPL_H
#define UNIT_USUARIOIMPL_H

void unit_UsuarioImpl_construtor(void); ///<testa os construtores
void unit_UsuarioImpl_copyConstrutor(void); ///< testa o construtor de copia
void unit_UsuarioImpl_operatorAtribuicao(void); ///<testa o operator=
void unit_UsuarioImpl_destrutor(void); ///<testa o destrutor
void unit_UsuarioImpl_id(void); ///<testa id()
void unit_UsuarioImpl_nome(void);///<testa nome
void unit_UsuarioImpl_perfil(void);///testa perfil
void unit_UsuarioImpl_idUnidade(void); ///<testa idUnidade
void run_unit_tests_UsuarioImpl(void);///<roda todos os testes de usuarioImpl

#endif