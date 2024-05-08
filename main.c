#include "menu.h"
#include "login.h"
#include <windows.h>

int main() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size = {100, 300}; // Define o tamanho do console (largura, altura)
    SetConsoleScreenBufferSize(console, size);
    login();
    //menuVenda();
    return 0;
}
