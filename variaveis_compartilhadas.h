#ifndef PROJETO_GESTAO_DE_EVENTOS_VARIAVEIS_COMPARTILHADAS_H
#define PROJETO_GESTAO_DE_EVENTOS_VARIAVEIS_COMPARTILHADAS_H

extern char* nomeUsuarioCompartilhado;

void setNomeUsuarioCompartilhado(const char* novoNome);
const char* getNomeUsuarioCompartilhado();

#endif //PROJETO_GESTAO_DE_EVENTOS_VARIAVEIS_COMPARTILHADAS_H
