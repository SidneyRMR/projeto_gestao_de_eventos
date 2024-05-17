#include "variaveis_compartilhadas.h"
#include "usuario.h"

//TODO - nao esta funcionado, quero criar uma variavel global para o usuario, para que ele possa passar o id_evento e id_usuario para os TODOs do venda.c
Usuario usuarioCompartilhado;
// Função para definir os dados do usuário compartilhado
void setUsuarioCompartilhado(const Usuario *novoUsuario) {
    usuarioCompartilhado = *novoUsuario; // Copia os dados da estrutura passada para a variável global
}
// Função para obter os dados do usuário compartilhado
Usuario getUsuarioCompartilhado() {
    return usuarioCompartilhado; // Retorna a estrutura do usuário compartilhado
}

