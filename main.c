#include "menu.h"
#include "login.h"
#include <windows.h>
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

int main() {
    ajustarTamanhoJanela(1000, 900); // Ajusta o tamanho da janela do console
    centralizarJanela(); // Centraliza a janela do console

    login(); // Chama a função de login
    return 0;
}
