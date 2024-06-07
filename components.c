#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include "variaveis_compartilhadas.h"
#include "menu.h"
#include "components.h"
#include "evento.h"
#include <conio.h>

#define LARGURA 114
#define LARGURALISTA 32


void setColorScheme(ColorScheme scheme) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((scheme.bgColor << 4) | scheme.textColor));
}

ColorScheme getColorSchemeByName(const char* name) {
    if (strcmp(name, "default") == 0) {
        return (ColorScheme){FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0}; // Texto branco, fundo preto
    } else if (strcmp(name, "error") == 0) {
        return (ColorScheme){FOREGROUND_RED, 0};   // Texto vermelho, fundo preto
    } else if (strcmp(name, "success") == 0) {
        return (ColorScheme){FOREGROUND_GREEN, 0}; // Texto verde, fundo preto
    } else if (strcmp(name, "warning") == 0) {
        return (ColorScheme){FOREGROUND_RED | FOREGROUND_GREEN, 0}; // Texto amarelo, fundo preto
    } else if (strcmp(name, "info") == 0) {
        return (ColorScheme){FOREGROUND_GREEN | FOREGROUND_BLUE, 0};  // Texto ciano, fundo preto
    }
    // Adicione outras combinações de cores aqui conforme necessário

    // Retorna a combinação padrão se não encontrar o nome
    return (ColorScheme){FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0};
}
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
    centralizarFrase(linha, "default");
}

void imprimirLinhaDivisoriaAjustavel(int tamanho) {
    char linha[tamanho + 1];  // +1 para o caractere nulo
    int i;

    // Preenchendo manualmente cada elemento do array com '-'
    for (i = 0; i < tamanho; i++) {
        linha[i] = '-';
    }

    linha[tamanho] = '\0';  // Certifique-se de que a linha seja terminada com null
    centralizarFrase(linha, "default");
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
    centralizarFrase(linha, "default");
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
    int espacos_restantes = LARGURALISTA - comprimento_frase - espacos ;

    if (espacos < 0) {
        espacos = 0;
    }
    if (espacos_restantes < 0) {
        espacos_restantes = 0;
    }

    char linha[LARGURALISTA + 3];
    strcpy(linha, "|");
    for (int i = 0; i < espacos-1; ++i) {
        strcat(linha, " ");
    }
    strcat(linha, frase);
    for (int i = 0; i < espacos_restantes-1; ++i) {
        strcat(linha, " ");
    }
    strcat(linha, "|");

    centralizarFrase(linha, "default");
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
    char tituloComDecoracao[256];
    setColorScheme(getColorSchemeByName("success"));
    imprimirLinha();
    imprimirCentralizado("");

    snprintf(tituloComDecoracao, sizeof(tituloComDecoracao), "****    %s    ****", titulo);
    imprimirCentralizado(tituloComDecoracao);

    if (subtitulo != NULL) {
        imprimirCentralizado(subtitulo);
    }

    imprimirCentralizado("");
    imprimirLinha();
    setColorScheme(getColorSchemeByName("default"));

    return 0;
}

int imprimirUsuarioEData() {
    char dataAtual[11];
    obterDataAtual(dataAtual);
    imprimirLinhaDivisoria();

    printf("|");
    // Centraliza "USUARIO: nomeUsuario" na outra metade da linha
    char usuarioStr[31];
    snprintf(usuarioStr, sizeof(usuarioStr), "USUARIO: %-31s ", getUsuarioCompartilhado().nome);
    centralizarString(usuarioStr, (LARGURA / 3) );

    int idEvento = getUsuarioCompartilhado().id_evento;
    Evento evento = buscarEventoPorID(idEvento);

    // Centraliza "USUARIO: nomeUsuario" na outra metade da linha
    char eventoStr[31];
    snprintf(eventoStr, sizeof(eventoStr), "EVENTO: %-31s ", evento.evento);
    centralizarString(eventoStr, (LARGURA / 2)-3 );

    // Centraliza "DATA: ddata" em metade da linha
    char dataStr[20];
    snprintf(dataStr, sizeof(dataStr), "DATA: %-11s", dataAtual);
    centralizarString(dataStr, (LARGURA / 5) );
    printf("|\n");


    imprimirLinhaDivisoria();

    return 0;
}

void opcaoInvalida() {

    centralizarFrase("Opcao invalida.", "error");
    Sleep(500);
}

void centralizarFrase(char *frase, const char *cor) {
    int espacos;
    int comprimento_frase;
    comprimento_frase = strlen(frase);
    espacos = (LARGURA - comprimento_frase) / 2;

    // Obter o esquema de cores
    ColorScheme scheme = getColorSchemeByName(cor);
    // Definir o esquema de cores
    setColorScheme(scheme);

    // Imprimir a frase centralizada
    printf("%*s%-*s%*s\n", espacos, "", comprimento_frase, frase, LARGURA - comprimento_frase - espacos, "");

    // Restaurar a cor padrão
    setColorScheme(getColorSchemeByName("default"));
    if (strcmp(cor, "default") == 0 || strcmp(cor, "warning") == 0) {
        Sleep(0);
    } else {
        Sleep(500);
    }

}
void centralizarFraseDoisValores(char *frase, char *frase2) {
    int comprimento_frase = strlen(frase) + strlen(frase2);
    int espacos = (LARGURALISTA+9);
    int espacos_extra = LARGURALISTA - espacos - 4 - comprimento_frase;

    for (int i = 0; i < espacos; i++) {
        printf(" ");
    }
    printf("| ");
    printf("%s%s", frase, frase2);
    for (int i = 0; i < espacos + espacos_extra; i++) {
        printf(" ");
    }
    printf(" |\n");
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Função para obter um valor int com entrada validada
int centralizarEObterValorInt(const char *frase) {
    int espacosEsquerda = (LARGURA - strlen(frase)) / 2;
    int valor;
    int entradaValida;

    do {
        // Imprimindo os espaços à esquerda
        for (int i = 0; i < espacosEsquerda; i++) {
            printf(" ");
        }

        setColorScheme(getColorSchemeByName("info"));
        // Imprimindo a frase
        printf("%s ", frase);

        setColorScheme(getColorSchemeByName("default"));

        // Tentando ler o valor
        entradaValida = scanf("%d", &valor);

        // Limpar o buffer de entrada em caso de erro
        if (entradaValida != 1) {
            limparBufferEntrada();

            setColorScheme(getColorSchemeByName("error"));
            centralizarString("Entrada invalida. Tente novamente.", LARGURA+6);
            setColorScheme(getColorSchemeByName("default"));

            entradaValida = 0;  // Definir como 0 para continuar no loop
        }
    } while (entradaValida != 1);
    //limparBufferEntrada();
    return valor;
}

double centralizarEObterValorDouble(const char* frase) {
    double valor;
    int entradaValida;

    do {
        int espacosEsquerda = (LARGURA - strlen(frase)) / 2;
        // Imprimindo os espaços à esquerda
        for (int i = 0; i < espacosEsquerda; i++) {
            printf(" ");
        }

        setColorScheme(getColorSchemeByName("info"));
        // Imprimindo a frase
        printf("%s ", frase);

        setColorScheme(getColorSchemeByName("default"));

        // Tentando ler o valor
        entradaValida = scanf("%lf", &valor);

        // Limpar o buffer de entrada em caso de erro
        if (entradaValida != 1 || valor < 0) {
            limparBufferEntrada();

            setColorScheme(getColorSchemeByName("error"));
            centralizarString("Entrada invalida. Tente novamente.", LARGURA+6);
            setColorScheme(getColorSchemeByName("default"));

            entradaValida = 0;  // Definir como 0 para continuar no loop
        }
    } while (entradaValida != 1 || valor < 0);

    limparBufferEntrada();
    return valor;
}


char* centralizarEObterValorChar(const char *frase, int tamanho) {
    if (strlen(frase) > LARGURA) {
        centralizarFrase("Erro: O valor excede a largura máxima permitida.", "error");
        return NULL; // Saída em caso de erro
    }

    int espacosEsquerda = (LARGURA - strlen(frase)) / 2;

    setColorScheme(getColorSchemeByName("info"));
    printf("%*s%s ", espacosEsquerda, "", frase); // Centraliza a frase
    setColorScheme(getColorSchemeByName("default"));

    char *valor = (char *)malloc((tamanho + 1) * sizeof(char)); // Alocando memória dinamicamente

    if (valor == NULL) {
        centralizarFrase("Erro: Falha na alocação de memória.", "error");
        return NULL; // Saída em caso de erro de alocação de memória
    }

    int i = 0;
    char ch;

    while (1) {
        ch = _getch(); // Lê um caractere sem exibi-lo na tela

        if (ch == 13) { // Enter key (ASCII 13)
            valor[i] = '\0';
            break;
        } else if (ch == 8) { // Backspace key (ASCII 8)
            if (i > 0) {
                i--;
                printf("\b \b"); // Move o cursor para trás, apaga o caractere e move para trás novamente
            }
        } else if (i < tamanho) { // Se não exceder o tamanho máximo
            valor[i] = ch;
            i++;
            printf("%c", ch); // Exibe o caractere na tela
        } else {
            // Se o tamanho máximo for atingido, toque um som de alerta e ignore mais entradas
            printf("\a"); // Toca um som de alerta
        }
    }

    printf("\n"); // Adiciona um newline após a leitura

    return valor;
}

void getPassword(char *password, int maxLength) {
    int i = 0;
    char ch;

    while (1) {
        ch = _getch(); // Lê um caractere sem exibi-lo na tela
        if (ch == 13) { // Enter key (ASCII 13)
            password[i] = '\0';
            break;
        } else if (ch == 8) { // Backspace key (ASCII 8)
            if (i > 0) {
                i--;
                printf("\b \b"); // Move o cursor para trás, apaga o caractere e move para trás novamente
            }
        } else if (i < maxLength - 1) {
            password[i] = ch;
            i++;
            printf("*");
        }
    }
}

char* centralizarEObterValorSenha(const char *frase, int tamanho) {
    if (strlen(frase) > LARGURA) {
        centralizarFrase("Erro: O valor excede a largura máxima permitida.", "error");
        return NULL; // Saída em caso de erro
    }

    int espacosEsquerda = (LARGURA - strlen(frase)) / 2;
    char *valor = (char *)
            malloc((tamanho + 1) * sizeof(char)); // Alocando memória dinamicamente

    if (valor == NULL) {
        centralizarFrase("Erro: Falha na alocação de memória.", "error");
        return NULL; // Saída em caso de erro de alocação de memória
    }

    // Imprimindo os espaços à esquerda
    for (int i = 0; i < espacosEsquerda; i++) {
        printf(" ");
    }
    setColorScheme(getColorSchemeByName("info"));
    // Imprimindo a frase
    printf("%s ", frase);

    setColorScheme(getColorSchemeByName("default"));

    getPassword(valor, tamanho);
    printf("\n");

    // Verificando se a entrada excede o tamanho permitido
    if (strlen(valor) > tamanho) {
        centralizarFrase("Erro: A entrada excede o tamanho máximo permitido de %d caracteres.","error");
        free(valor); // Liberando a memória alocada
        return NULL; // Saída em caso de erro
    }
    // Retornando a entrada lida
    return valor;
}

