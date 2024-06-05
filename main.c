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

//#include <hpdf.h>
//todo - preparar apresentação powerpoint e documentação (pode ser em .md - confirmar com Ana Celia) e guia de usuario(como usar em .md) para dia 8 de junho *******************************

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

/*
void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
    printf("Error: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no, (HPDF_UINT)detail_no);
}

int impressaoTeste() {
    HPDF_Doc pdf;
    HPDF_Page page;
    HPDF_Font font;

    pdf = HPDF_New(error_handler, NULL);
    if (!pdf) {
        printf("Failed to create pdf object\n");
        return 1;
    }

    page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    font = HPDF_GetFont(pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(page, font, 24);

    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, 50, 750, "Hello, World!");
    HPDF_Page_EndText(page);

    HPDF_SaveToFile(pdf, "output.pdf");

    HPDF_Free(pdf);
    return 0;
}

 CmakeList :
 # Adicione os diretórios de inclusão e biblioteca manualmente
include_directories("C:/libsC/libharu/include")
link_directories("C:/libsC/libharu/build/src")
*/

// Função para extrair o nome do arquivo sem extensão a partir do caminho completo
// Função para extrair o nome do arquivo sem extensão a partir do caminho completo
char* get_filename(const char *path) {
    // Encontra a última ocorrência de '/'
    const char *last_slash = strrchr(path, '/');
    const char *filename = (last_slash != NULL) ? last_slash + 1 : path;

    // Encontra a última ocorrência de '.'
    const char *dot = strrchr(filename, '.');

    // Calcula o tamanho do nome do arquivo sem extensão
    size_t length = (dot != NULL) ? (size_t)(dot - filename) : strlen(filename);

    // Aloca memória para o nome do arquivo sem extensão
    char *name = (char *)malloc(length + 1);
    if (name == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(1);
    }

    // Copia o nome do arquivo sem extensão
    strncpy(name, filename, length);
    name[length] = '\0';  // Adiciona o terminador nulo

    return name;
}


// Função para criar diretório se não existir
void criarDiretorio(const char *nomeDiretorio) {
    struct stat st = {0};
    if (stat(nomeDiretorio, &st) == -1) {
        if (MKDIR(nomeDiretorio, 0700) == 0) {
            printf("Diretório %s criado com sucesso.\n", nomeDiretorio);
        } else {
            printf("Erro ao criar o diretório %s.\n", nomeDiretorio);
        }
    }
    system("cls");
}

// Função para verificar e criar arquivo se não existir
void verificaECriaArquivo(const char *nomeArquivo) {
    char *nomeLimpo = get_filename(nomeArquivo);
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        // Arquivo não existe, então cria o arquivo
        file = fopen(nomeArquivo, "w");
        if (file != NULL) {
            ("Instalando o arquivo %s no computador.\n", nomeArquivo);
            // Verifica se o arquivo é "usuarios.txt" e adiciona a linha específica
            if (strcmp(nomeArquivo, "data/usuarios.txt") == 0) {
                fprintf(file, "1 'Administrador' 'admin' 'admin' administrador 1 0\n");
                printf("Adicionando acesso de administrador ao programa");
            }
            if (strcmp(nomeArquivo, "data/eventos.txt") == 0) {
                fprintf(file, "0 'Geral' 'Geral' 15/05/2024 0\n");
                printf("Adicionando evento padrao ao programa.");
            }
            fclose(file);
        } else {
            printf("Erro ao criar o arquivo %s .\n", nomeLimpo);
        }
    } else {
        // Arquivo existe, então faz o backup
        printf("Fazendo backup dos %s.\n", nomeLimpo);
        fclose(file);

        char nomeBackup[200];
        snprintf(nomeBackup, sizeof(nomeBackup), "backup/%s", strrchr(nomeArquivo, '/') + 1);

        // Abre o arquivo original para leitura
        file = fopen(nomeArquivo, "r");
        Sleep(200);
        if (file != NULL) {
            // Abre o arquivo de backup para escrita
            FILE *backupFile = fopen(nomeBackup, "w");
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
    Sleep(200);
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

    // Verifica se os arquivos .txt necessários para armazenamento dos dados existem, caso nao existirem, serão criados
    verificarArquivos();

    ajustarTamanhoJanela(1000, 900); // Ajusta o tamanho da janela do console
    centralizarJanela(); // Centraliza a janela do console

    login(); // Chama a função de login e inicia o programa de fato
    return 0;
}
