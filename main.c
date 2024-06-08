#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "menu.h"
#include "login.h"
#include "components.h"

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path, mode) _mkdir(path)
#else
#include <unistd.h>
#define MKDIR(path, mode) mkdir(path, mode)
#endif

void ajustarTamanhoJanela(int largura, int altura) {
    HWND hwnd = GetConsoleWindow(); // Obtém o identificador da janela do console
    RECT rect;
    GetWindowRect(hwnd, &rect); // Obtém as dimensões atuais da janela
    MoveWindow(hwnd, rect.left, rect.top, largura, altura, TRUE); // Move e redimensiona a janela
}

void centralizarJanela() {
    HWND hwnd = GetConsoleWindow(); // Obtém o identificador da janela do console
    RECT rect;
    GetWindowRect(hwnd, &rect); // Obtém as dimensões atuais da janela
    int screenWidth = GetSystemMetrics(SM_CXSCREEN); // Obtém a largura da tela
    int screenHeight = GetSystemMetrics(SM_CYSCREEN); // Obtém a altura da tela
    int windowWidth = rect.right - rect.left; // Obtém a largura atual da janela
    int windowHeight = rect.bottom - rect.top; // Obtém a altura atual da janela
    int posX = (screenWidth - windowWidth) / 2; // Calcula a posição X para centralizar a janela
    int posY = (screenHeight - windowHeight) / 2; // Calcula a posição Y para centralizar a janela
    MoveWindow(hwnd, posX, posY, windowWidth, windowHeight, TRUE); // Move a janela para as coordenadas centralizadas
}

// Função para obter o nome do arquivo sem a extensão
char* get_filename(const char* path) {
    const char* last_slash = strrchr(path, '/');
    const char* filename = (last_slash != NULL) ? last_slash + 1 : path;
    const char* dot = strrchr(filename, '.');
    size_t length = (dot != NULL) ? (size_t)(dot - filename) : strlen(filename);
    char* name = (char*)malloc(length + 1);
    if (name == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria\n");
        exit(1);
    }
    strncpy(name, filename, length);
    name[length] = '\0';
    return name;
}

// Função para criar diretório se não existir
void criarDiretorio(const char* nomeDiretorio) {
    struct stat st = {0};
    if (stat(nomeDiretorio, &st) == -1) {
        if (MKDIR(nomeDiretorio, 0700) == 0) {
            printf("Diretorio %s criado com sucesso.\n", nomeDiretorio);
        } else {
            printf("Erro ao criar o diretorio %s.\n", nomeDiretorio);
        }
    }
    system("cls");
}

// Função para mostrar barra de progresso
void mostrarBarraProgresso(const char* mensagem) {
    const int total = 50;  // tamanho total da barra de progresso
    printf("%s\n", mensagem);
    for (int i = 0; i <= total; ++i) {
        printf("\r[");
        for (int j = 0; j < i; ++j) {
            printf("#");
        }
        for (int j = i; j < total; ++j) {
            printf(" ");
        }
        printf("] %d%%", (i * 100) / total);
        Sleep(0);  // tempo de espera para simular o progresso
    }
    printf("\n");
}

// Função para verificar e criar arquivo se não existir
void verificaECriaArquivo(const char* nomeArquivo) {
    char* nomeLimpo = get_filename(nomeArquivo);
    criarDiretorio("data");
    FILE* file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        // Arquivo não existe, então cria o arquivo
        file = fopen(nomeArquivo, "w");
        if (file != NULL) {
            printf("Instalando o arquivo %s no computador.\n", nomeArquivo);
            if (strcmp(nomeArquivo, "data/usuarios.txt") == 0) {
                fprintf(file, "1 'Administrador' 'admin' 'admin' administrador 1 0\n");
                printf("Adicionando acesso de administrador ao programa\n");
            }
            if (strcmp(nomeArquivo, "data/eventos.txt") == 0) {
                fprintf(file, "0 'Geral' 'Geral' 15/05/2024 0\n");
                printf("Adicionando evento padrao ao programa.\n");
            }
            fclose(file);
        } else {
            printf("Erro ao criar o arquivo %s.\n", nomeLimpo);
        }
    } else {
        // Arquivo existe, então faz o backup
        printf("Fazendo backup dos %s.\n", nomeLimpo);
        fclose(file);

        char nomeBackup[200];
        snprintf(nomeBackup, sizeof(nomeBackup), "backup/%s", strrchr(nomeArquivo, '/') + 1);

        // Abre o arquivo original para leitura
        file = fopen(nomeArquivo, "r");
        if (file != NULL) {
            // Abre o arquivo de backup para escrita
            FILE* backupFile = fopen(nomeBackup, "w");
            if (backupFile != NULL) {
                // Copia o conteúdo do arquivo original para o arquivo de backup
                int ch;
                while ((ch = fgetc(file)) != EOF) {
                    fputc(ch, backupFile);
                }
                printf("Backup dos %s criado com sucesso.\n", nomeLimpo);
                fclose(backupFile);
            } else {
                printf("Erro ao criar o backup dos %s.\n", nomeLimpo);
            }
            fclose(file);
        } else {
            printf("Erro ao abrir os %s para leitura.\n", nomeLimpo);
        }
    }
    free(nomeLimpo);
    mostrarBarraProgresso("Processo de verificacao de arquivos em andamento...");
    system("cls");
}


void verificarArquivos() {
    // Lista de nomes de arquivos a serem verificados e criados
    const char *arquivos[] = {
            "data/usuarios.txt",
            "data/vendas.txt",
            "data/vendas_detalhes.txt",
            "data/produtos.txt",
            "data/eventos.txt"
    };

    // Número de arquivos na lista
    int numArquivos = sizeof(arquivos) / sizeof(arquivos[0]);

    // Cria o diretório de backup se não existir
    criarDiretorio("backup");

    // Verifica e cria cada arquivo se necessário
    for (int i = 0; i < numArquivos; i++) {
        verificaECriaArquivo(arquivos[i]);
    }
}
int main() {
    //impressaoTeste();
    setvbuf(stdout,NULL,_IONBF,0);
    // Verifica se os arquivos .txt necessários para armazenamento dos dados existem, caso nao existirem, serão criados
    ajustarTamanhoJanela(500, 120); // Ajusta o tamanho da janela do console
    centralizarJanela(); // Centraliza a janela do console
    verificarArquivos();
    ajustarTamanhoJanela(1000, 900); // Ajusta o tamanho da janela do console
    centralizarJanela(); // Centraliza a janela do console

    login(); // Chama a função de login e inicia o programa de fato
    return 0;
}
