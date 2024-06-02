#include "variaveis_compartilhadas.h"
#include "usuario.h"

Usuario usuarioCompartilhado;
// Função para definir os dados do usuário compartilhado
void setUsuarioCompartilhado(const Usuario *novoUsuario) {
    usuarioCompartilhado = *novoUsuario; // Copia os dados da estrutura passada para a variável global
}
// Função para obter os dados do usuário compartilhado
Usuario getUsuarioCompartilhado() {
    return usuarioCompartilhado; // Retorna a estrutura do usuário compartilhado
}

