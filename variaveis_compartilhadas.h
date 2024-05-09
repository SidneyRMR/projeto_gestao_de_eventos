#ifndef PROJETO_GESTAO_DE_EVENTOS_VARIAVEIS_COMPARTILHADAS_H
#define PROJETO_GESTAO_DE_EVENTOS_VARIAVEIS_COMPARTILHADAS_H
#include "usuario.h"

extern char* nomeUsuarioCompartilhado;
extern Usuario UsuarioCompartilhado;

void setNomeUsuarioCompartilhado(const char* novoNome);
const char* getNomeUsuarioCompartilhado();

void setUsuarioCompartilhado(const Usuario *novoUsuario);
Usuario getUsuarioCompartilhado();


#endif //PROJETO_GESTAO_DE_EVENTOS_VARIAVEIS_COMPARTILHADAS_H
