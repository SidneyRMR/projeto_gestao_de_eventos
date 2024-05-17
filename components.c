#include "components.h"
#include <stdio.h>
#include <string.h>
#define LARGURA 104

void imprimirLinhaDivisoria() {
    printf("|--------------------------------------------------------------------------------------------------------|\n");
}

void imprimirLinha() {
    printf("|========================================================================================================|\n");
}

void imprimirCentralizado(const char *texto) {
    int comprimentoTexto = strlen(texto);
    if (comprimentoTexto > LARGURA) {
        comprimentoTexto = LARGURA;  // Trunca o texto se for maior que a largura disponível
    }
    int espacosEsquerda = (LARGURA - comprimentoTexto) / 2;
    int espacosDireita = LARGURA - comprimentoTexto - espacosEsquerda;

    printf("|%*s%.*s%*s|\n", espacosEsquerda, "", comprimentoTexto, texto, espacosDireita, "");
}

int imprimirTituloCabecario(const char *titulo, const char *subtitulo) {
    imprimirLinha();
    imprimirCentralizado(titulo);
    if (subtitulo != NULL) {
        imprimirCentralizado(subtitulo);
    }
    imprimirLinha();

    return 0;
}


