#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include "variaveis_compartilhadas.h"
#include "menu.h"
#define LARGURA 114
#define LARGURALISTA 32
void centralizarFrase(char *frase);
void centralizarFraseSemBorda(char *frase);

void imprimirLinhaDivisoria() {
    for (int i = 0; i < LARGURA+2; i++) {
        printf("-");
    }
    printf("\n");
}

void imprimirLinhaDivisoriaLista() {
    char linha[LARGURALISTA+1];
    memset(linha, '-', LARGURALISTA);
    linha[LARGURALISTA] = '\0';  // Certifique-se de que a linha seja terminada com null
    centralizarFraseSemBorda(linha);
    //printf("\n");
}

void imprimirLinha() {
    for (int i = 0; i < LARGURA+2; i++) {
        printf("=");
    }
    printf("\n");
}
void imprimirLinhaLista() {
    char linha[LARGURALISTA+1];
    memset(linha, '=', LARGURALISTA);
    linha[LARGURALISTA] = '\0';  // Certifique-se de que a linha seja terminada com null
    centralizarFraseSemBorda(linha);
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

void imprimirCentralizadoLista(const char *frase) {
    int comprimento_frase = strlen(frase);
    int espacos = (LARGURALISTA - comprimento_frase) / 2;
    int espacos_restantes = LARGURALISTA - comprimento_frase - espacos;

    if (espacos < 0) {
        espacos = 0;
    }
    if (espacos_restantes < 0) {
        espacos_restantes = 0;
    }
    char buffer[LARGURALISTA + 3]; // LARGURALISTA + 2 para as bordas '|' e +1 para o caractere nulo
    sprintf(buffer, "|%*s%s%*s|", espacos-1, "", frase, espacos_restantes-1, "");
    centralizarFraseSemBorda(buffer);
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
int imprimirTituloCabecarioLista(const char *titulo, const char *subtitulo) {
    imprimirLinhaLista();
    imprimirCentralizadoLista(titulo);
    if (subtitulo != NULL) {
        imprimirCentralizadoLista(subtitulo);
    }
    imprimirLinhaLista();

    return 0;
}

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

int imprimirTituloCabecarioDuplo(const char *titulo, const char *subtitulo) {
    char dataAtual[11];
    char tituloComDecoracao[256];

    obterDataAtual(dataAtual);

    imprimirLinha();
    imprimirCentralizado("");

    snprintf(tituloComDecoracao, sizeof(tituloComDecoracao), "****    %s    ****", titulo);
    imprimirCentralizado(tituloComDecoracao);

    if (subtitulo != NULL) {
        imprimirCentralizado(subtitulo);
    }

    imprimirCentralizado("");
    imprimirLinha();

    return 0;
}

int imprimirUsuarioEData() {
    char dataAtual[11];
    obterDataAtual(dataAtual);
    imprimirLinhaDivisoria();

    printf("|");
    // Centraliza "USUARIO: nomeUsuario" na outra metade da linha
    char usuarioStr[21];
    snprintf(usuarioStr, sizeof(usuarioStr), "USUARIO: %-21s ", getUsuarioCompartilhado().nome);
    centralizarString(usuarioStr, (LARGURA / 2) );

    // Centraliza "DATA: ddata" em metade da linha
    char dataStr[20];
    snprintf(dataStr, sizeof(dataStr), "DATA: %-11s", dataAtual);
    centralizarString(dataStr, (LARGURA / 2) );
    printf("|\n");


    imprimirLinhaDivisoria();

    return 0;
}

void opcaoInvalida() {
    centralizarFraseSemBorda("Opcao invalida.");
}

void centralizarFrase(char *frase) {
    int espacos = 0;
    int comprimento_frase= 0;
    comprimento_frase = strlen(frase);
    espacos = (LARGURA - comprimento_frase) / 2;
    printf("|%*s%-*s%*s|\n", espacos, "", comprimento_frase, frase, LARGURA - comprimento_frase - espacos, "");
}

void centralizarFraseSemBorda(char *frase) {
    int espacos = 0;
    int comprimento_frase= 0;
    comprimento_frase = strlen(frase);
    espacos = (LARGURA - comprimento_frase) / 2;
    printf("%*s%-*s%*s\n", espacos, "", comprimento_frase, frase, LARGURA - comprimento_frase - espacos, "");
}

// Função para obter um valor int com entrada validada
int centralizarEObterValorInt(const char *frase) {
    int espacosEsquerda = (LARGURA - strlen(frase)) / 2;
    int valor;
    int entradaValida;

    //imprimirLinhaDivisoria();
    do {
        // Imprimindo os espaços à esquerda
        for (int i = 0; i < espacosEsquerda; i++) {
            printf(" ");
        }

        // Imprimindo a frase
        printf("%s ", frase);

        // Tentando ler o valor
        entradaValida = scanf("%d", &valor);

        // Limpar o buffer de entrada em caso de erro
        if (entradaValida != 1) {
            while (getchar() != '\n');
            centralizarString("Entrada invalida. Tente novamente.\n", LARGURA);
            //centralizarString("Entrada invalida. Tente novamente.", LARGURA + strlen(frase) / 4);
            entradaValida = 0;  // Definir como 0 para continuar no loop
        }
    } while (entradaValida != 1);

    return valor;
}

double centralizarEObterValorDouble(const char *frase) {
    double valor;
    int entradaValida;

    //imprimirLinhaDivisoria();
    do {
    int espacosEsquerda = (LARGURA - strlen(frase)) / 2;
        // Imprimindo os espaços à esquerda
        for (int i = 0; i < espacosEsquerda; i++) {
            printf(" ");
        }

        // Imprimindo a frase
        printf("%s ", frase);

        // Tentando ler o valor
        entradaValida = scanf("%lf", &valor);

        // Limpar o buffer de entrada em caso de erro
        if (entradaValida != 1 || valor < 0) {
            while (getchar() != '\n');
            centralizarString("Entrada invalida. Tente novamente.\n", LARGURA + strlen(frase) / 4);
            entradaValida = 0;  // Definir como 0 para continuar no loop
        }
    } while (entradaValida != 1 || valor < 0);

    return valor;
}

char* centralizarEObterValorChar(const char *frase, int tamanho) {
    if (strlen(frase) > LARGURA) {
        centralizarFrase("Erro: O valor excede a largura máxima permitida.");
        return NULL; // Saída em caso de erro
    }

    //imprimirLinhaDivisoria();
    int espacosEsquerda = (LARGURA - strlen(frase)) / 2;
    char *valor = (char *)
            malloc((tamanho + 1) * sizeof(char)); // Alocando memória dinamicamente

    if (valor == NULL) {
        centralizarFrase("Erro: Falha na alocação de memória.\n");
        return NULL; // Saída em caso de erro de alocação de memória
    }

    // Imprimindo os espaços à esquerda
    for (int i = 0; i < espacosEsquerda; i++) {
        printf(" ");
    }
    //imprimirTituloCabecario(frase,NULL);
    // Imprimindo a frase
    printf("%s ", frase);

    // Lendo a entrada com scanf, garantindo que não exceda o tamanho máximo
    scanf(" %97[^\n]", valor); // lê no máximo 97 caracteres para garantir espaço para o terminador nulo

    // Verificando se a entrada excede o tamanho permitido
    if (strlen(valor) > tamanho) {
        printf("Erro: A entrada excede o tamanho máximo permitido de %d caracteres.", tamanho);
        free(valor); // Liberando a memória alocada
        return NULL; // Saída em caso de erro
    }

    // Retornando a entrada lida
    return valor;
}

