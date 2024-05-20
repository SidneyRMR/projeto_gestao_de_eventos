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

int imprimirUsuarioEData() {
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

void centralizarFrase(char *frase) {
    int espacos = 0;
    int comprimento_frase= 0;
    comprimento_frase = strlen(frase);
    espacos = (LARGURA - comprimento_frase) / 2;
    printf("|%*s%-*s%*s|\n", espacos, "", comprimento_frase, frase, LARGURA - comprimento_frase - espacos, "");
}

int centralizarEObterValorInt(const char *frase) {
    int espacosEsquerda = (LARGURA - strlen(frase)) / 2;
    int valor;

    // Imprimindo os espaços à esquerda
    for (int i = 0; i < espacosEsquerda; i++) {
        printf(" ");
    }

    // Imprimindo a frase
    printf("%s ", frase);

    // Lendo o valor com scanf
    while (scanf("%d", &valor) != 1) {
        // Limpar o buffer de entrada
        while (getchar() != '\n');
        centralizarString("Entrada inválida. Tente um numero inteiro.", 35);
        centralizarEObterValorInt(frase);
    }

    // Retornando o valor lido
    return valor;
}

double centralizarEObterValorDouble(const char *frase) {
    int espacosEsquerda = (LARGURA - strlen(frase)) / 2;
    double valor;

    // Imprimindo os espaços à esquerda
    for (int i = 0; i < espacosEsquerda; i++) {
        printf(" ");
    }

    // Imprimindo a frase
    printf("%s ", frase);

    // Lendo o valor com scanf
    scanf("%lf", &valor);

    // Retornando o valor lido
    return valor;
}

char* centralizarEObterValorChar(const char *frase, int tamanho) {
    // Verifica se o tamanho da frase é maior que a largura permitida
    if (strlen(frase) > LARGURA) {
        printf("Erro: A valor excede a largura máxima permitida.\n");
        centralizarEObterValorChar(frase, tamanho);
    }

    int espacosEsquerda = (LARGURA - strlen(frase)) / 2;
    static char valor[100]; // Array para armazenar a entrada do usuário

    // Imprimindo os espaços à esquerda
    for (int i = 0; i < espacosEsquerda; i++) {
        printf(" ");
    }

    // Imprimindo a frase
    printf("%s ", frase);

    // Lendo a entrada com scanf, garantindo que não exceda o tamanho máximo
    scanf(" %97[^\n]", valor); // lê no máximo 99 caracteres para garantir espaço para o terminador nulo

    // Verificando se a entrada excede o tamanho permitido
    if (strlen(valor) > tamanho) {
        printf("\nErro: A entrada excede o tamanho máximo permitido de %d caracteres.\n", tamanho);
        centralizarEObterValorChar(frase, tamanho);
    }
    // Retornando a entrada lida
    return valor;
}

