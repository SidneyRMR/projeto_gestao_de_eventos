#include "menu.h"
#include "login.h"
#include <windows.h>

// Ajuste o tamanho da janela
void ajustarTamanhoJanela(int largura, int altura) {
    HWND hwnd = GetConsoleWindow();
    RECT rect;
    GetWindowRect(hwnd, &rect);
    MoveWindow(hwnd, rect.left, rect.top, largura, altura, TRUE);
}

int main() {
    ajustarTamanhoJanela(1000, 800);
    login();
    return 0;
}
