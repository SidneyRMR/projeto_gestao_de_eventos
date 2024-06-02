#ifndef PROJETO_GESTAO_DE_EVENTOS_VARIAVEIS_COMPARTILHADAS_H
#define PROJETO_GESTAO_DE_EVENTOS_VARIAVEIS_COMPARTILHADAS_H
#include "usuario.h"


/**
 * Função para definir os dados do usuário compartilhado.
 * Recebe um ponteiro para uma estrutura Usuario contendo os dados do novo usuário.
 * Copia os dados da estrutura passada para a variável global usuarioCompartilhado.
 */
void setUsuarioCompartilhado(const Usuario *novoUsuario);

/**
 * Função para obter os dados do usuário compartilhado.
 * Retorna a estrutura do usuário compartilhado armazenada na variável global usuarioCompartilhado.
 */
Usuario getUsuarioCompartilhado();


#endif //PROJETO_GESTAO_DE_EVENTOS_VARIAVEIS_COMPARTILHADAS_H
