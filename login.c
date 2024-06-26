#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "login.h"
#include "menu.h"
#include "variaveis_compartilhadas.h"
#include "components.h"

#define MAX_USUARIOS 100 // Defina o número máximo de usuários

typedef struct UsuarioLogin {
    int id;
    char nome[51];
    char login[21];
    char senha[11];
    char tipo[15];
    int status;
    int id_evento;
} UsuarioLogin;

struct UsuarioLogin usuarios[MAX_USUARIOS]; // Declaração do array de usuários
int numUsuarios = 0; // Variável para rastrear o número atual de usuários

// Função para carregar os usuários do arquivo usuarios.txt
void carregarUsuarios() {
    FILE *file;
    char filename[] = "data/usuarios.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        while (fscanf(file, "%d '%50[^']' '%20[^']' '%10[^']' %16s %d %d",
                      &usuarios[numUsuarios].id,
                      usuarios[numUsuarios].nome,
                      usuarios[numUsuarios].login,
                      usuarios[numUsuarios].senha,
                      usuarios[numUsuarios].tipo,
                      &usuarios[numUsuarios].status,
                      &usuarios[numUsuarios].id_evento) == 7) {
            numUsuarios++;
            if (numUsuarios >= MAX_USUARIOS) {
                break; // Evita ultrapassar o tamanho máximo do array
            }
        }
        fclose(file);
    } else {
        centralizarFrase("Erro ao abrir o arquivo de usuários", "error");
        exit(1);
    }
}
int loginAux() {
    system("cls");
    imprimirTituloCabecarioDuplo("TELA DE LOGIN - GESTAO DE EVENTOS",NULL);
    char *usuarioo = centralizarEObterValorSenha("Digite seu usuario: ", 21);
    char *senha = centralizarEObterValorSenha("Digite sua senha: ",11);

    for (int i = 0; i < numUsuarios; i++) {
        if(strcmp(usuarioo, usuarios[i].login) == 0 && strcmp(senha, usuarios[i].senha) == 0 && usuarios[i].status == 1) {
            char fraseLogin[114];
            sprintf(fraseLogin, "Login efetuado com sucesso como %s ", usuarios[i].nome);
            centralizarFrase(fraseLogin, "success");
            setUsuarioCompartilhado(&usuarios[i]);
            escolherMenu();
            return 0;
        }
    }
    centralizarFrase("Login invalido, tente novamente.","warning");
    Sleep(500);
    //system("cls");
    return 0;
}

// Função de login
void login() {
    carregarUsuarios(); // Carregar os usuários do arquivo
    system("cls");
    int tentativas = 3;
    while (tentativas > 0) {
        if (loginAux()) {
            // Se o login for bem-sucedido, sair da função
            return;
        } else {
            tentativas--;
            char fraseTentativas[114];
            sprintf(fraseTentativas, "Voce tem %d tentativas restantes.", tentativas);
            centralizarFrase(fraseTentativas, "warning");
            Sleep(1000);
        }
    }
    centralizarFrase("Numero maximo de tentativas excedido. Saindo...","error");
    exit(1);
}
