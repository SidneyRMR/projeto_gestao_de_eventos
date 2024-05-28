#include "menu.h"
#include "login.h"
#include <windows.h>
//#include <hpdf.h>
#include <stdio.h>
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
int main() {
    ajustarTamanhoJanela(1000, 900); // Ajusta o tamanho da janela do console
    centralizarJanela(); // Centraliza a janela do console
    //impressaoTeste();
    login(); // Chama a função de login
    return 0;
}
