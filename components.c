#include <stdio.h>
#include <string.h>
#include "variaveis_compartilhadas.h"
#include "menu.h"

#define LARGURA 114

void imprimirLinhaDivisoria() {
    for (int i = 0; i < LARGURA+2; i++) {
        printf("-");
    }
    printf("\n");
}

void imprimirLinha() {
    for (int i = 0; i < LARGURA+2; i++) {
        printf("=");
    }
    printf("\n");
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

// Função para centralizar uma string dentro de um espaço de largura específica
void centralizarString(char *str, int largura) {
    int comprimento = strlen(str);
    int espacos = (largura - comprimento) / 2;
    for (int i = 0; i < espacos; i++) {
        printf(" ");
    }
    printf("%s", str);
    for (int i = 0; i < espacos; i++) {
        printf(" ");
    }
    // Caso a largura não seja um número par, adiciona um espaço extra no final
    if ((largura - comprimento) % 2 != 0) {
        printf(" ");
    }
}

int imprimirRodape() {
    char dataAtual[11];
    obterDataAtual(dataAtual);

    imprimirLinhaDivisoria();

    printf("|");
    // Centraliza "DATA: ddata" em metade da linha
    char dataStr[20];
    snprintf(dataStr, sizeof(dataStr), "DATA: %-11s", dataAtual);
    centralizarString(dataStr, (LARGURA / 2) );
    printf("|");

    // Centraliza "USUARIO: nomeUsuario" na outra metade da linha
    char usuarioStr[21];
    snprintf(usuarioStr, sizeof(usuarioStr), "USUARIO: %-21s", getUsuarioCompartilhado().nome);
    centralizarString(usuarioStr, (LARGURA / 2)-1 );
    printf("|\n");

    imprimirLinhaDivisoria();

    return 0;
}

void opcaoInvalida() {
    printf("Opcao invalida.\n");
}