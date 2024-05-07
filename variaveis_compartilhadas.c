#include "variaveis_compartilhadas.h"

#include "variaveis_compartilhadas.h"
#include <string.h>
#include <stdlib.h>

char* nomeUsuarioCompartilhado = NULL;

void setNomeUsuarioCompartilhado(const char* novoNome) {
    if (nomeUsuarioCompartilhado != NULL) {
        free(nomeUsuarioCompartilhado); // Liberar memória se já houver uma string
    }
    nomeUsuarioCompartilhado = strdup(novoNome); // Alocar memória e copiar a nova string
}

const char* getNomeUsuarioCompartilhado() {
    return nomeUsuarioCompartilhado;
}
