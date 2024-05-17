#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usuario.h"
#include "evento.h"
#include "components.h"

// Função para cadastro de usuário
void criarUsuario() {
    Usuario usuario;

    int opcaoTipo = 0;


    imprimirTituloCabecario("TELA DE CADASTRO DE USUARIO",NULL);

    printf("|\tDigite o NOME: ");
    scanf(" %50[^\n]", usuario.nome);
    printf("|\tDigite o LOGIN: ");
    scanf(" %20[^\n]", usuario.login);
    printf("|\tDigite A SENHA: ");
    scanf(" %10[^\n]", usuario.senha);
    printf("|\tEscolha o tipo de usuario:                    |\n");
    printf("|\t\t1. Vendedor                           |\n");
    printf("|\t\t2. Administrador                      |\n");
    printf("|     Escolha: ");
    scanf("%d", &opcaoTipo);
    imprimirLinhaDivisoria();

    // Solicitar ao usuário que escolha o tipo de usuário
    while (opcaoTipo != 1 && opcaoTipo != 2) {
        printf("|\tEscolha o tipo de usuario:                      |\n"
               "|\t\t 1. Vendedor                                     |\n"
               "|\t\t 2. Administrador                                |\n"
               "|\t\t Escolha: ");
        scanf("%d", &opcaoTipo);
    }

    // Determinar o tipo do usuário com base na escolha do usuário
    switch (opcaoTipo) {
        case 1:
            strcpy(usuario.tipo, "vendedor");
            break;
        case 2:
            strcpy(usuario.tipo, "administrador");
            break;
        default:
            opcaoInvalida();
    }

    // Preencher a estrutura do usuário com os dados inseridos
    usuario.id = carregarUltimoUsuario(); // Incrementar o ID do último usuário
    usuario.status = 1;

    // TODO - PRECISA SER MELHORADA ESTA LISTAGEM DE EVENTOS
    listarEventos();
    int eventoMax = carregarUltimoEvento();
    int opcaoEvento = 0;

    do {
        printf("|\tDigite o codigo do evento para o usuario: ");
        scanf("%d", &opcaoEvento);
    }
    while(opcaoEvento < 1 || opcaoEvento > eventoMax);

    usuario.id_evento = opcaoEvento;
    salvarUsuario(usuario);
}

int listarUsuarios() {
    FILE *file;
    char filename[] = "data/usuarios.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        //printf("Arquivo foi aberto com sucesso.\n\n");

        imprimirRodape();
        // Imprimir cabeçalho da tabela
        imprimirTituloCabecario("LISTA DE USUARIOS",NULL);

        printf("| %-3s | %-38s | %-15s | %-10s | %-14s | %-7s | %-7s |\n", "Cod", "Nome", "Login", "Senha", "Tipo", "Status", "Evento");
        imprimirLinhaDivisoria();

        Usuario usuario;
        char aux_senha[20]; // Ajuste o tamanho conforme necessário

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%[^']' %s %s %s %d %d", &usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, &usuario.status, &usuario.id_evento) != EOF) {
            strcpy(aux_senha, "******");
            printf("| %-3d | %-38s | %-15s | %-10s | %-14s | %-7d | %-7d |\n", usuario.id, usuario.nome, usuario.login, aux_senha, usuario.tipo, usuario.status, usuario.id_evento);
        }

        imprimirLinhaDivisoria();
        fclose(file);
    } else {
        perror("Não foi possível abrir o arquivo %s.\n\n");
    }
    return 0;
}

int carregarUltimoUsuario() {
    FILE *file;
    char filename[] = "data/usuarios.txt";
    file = fopen(filename, "r");

    int contador_linhas = 0;

    if (file != NULL) {
        int c;
        // Percorrer o arquivo caractere por caractere
        while ((c = fgetc(file)) != EOF) {
            if (c == '\n') {
                ++contador_linhas;
            }
        }
        fclose(file);
        //printf("Registro %d\n", contador_linhas);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }
    return contador_linhas+1;
}

void salvarUsuario(Usuario usuario) {
    FILE *file;
    char filename[] = "data/usuarios.txt";
    file = fopen(filename, "a"); // Abrir o arquivo em modo de escrita, acrescentando ao final

    if (file != NULL) {
        fprintf(file, "%d '%s' %s %s %s %d %d\n", usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, usuario.status, usuario.id_evento);
        fclose(file);
        printf("Usuario salvo com sucesso!\n");
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }
}

Usuario consultarUsuarioPorID(int id) {
    FILE *file;
    char filename[] = "data/usuarios.txt";
    file = fopen(filename, "r"); // Abrir o arquivo em modo de leitura

    if (file != NULL) {
        Usuario usuario;
        int encontrado = 0;

        // Lê cada usuário do arquivo até encontrar o usuário com o ID correspondente
        while (fscanf(file, "%d '%49[^']' %19s %19s %19s %d %d\n", &usuario.id, usuario.nome, usuario.login,
                      usuario.senha, usuario.tipo, &usuario.status, &usuario.id_evento) != EOF) {
            if (usuario.id == id) {
                encontrado = 1;
                fclose(file);
                return usuario;
            }
        }

        fclose(file);
        if (!encontrado) {
            printf("Usuário com ID %d não encontrado.\n", id);
        }
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    Usuario usuario_vazio; // Retorna um usuário vazio se não encontrar
    usuario_vazio.id = -1; // Ou outro valor que você considerar adequado
    return usuario_vazio;
}

#define MAX_USUARIOS 100 // Defina o número máximo de usuários


Usuario buscarUsuarioPorId(int id) {
struct Usuario usuarios[MAX_USUARIOS]; // Declaração do array de usuários

int numUsuarios = 0; // Variável para rastrear o número atual de usuários
    Usuario usuarioEncontrado;
    FILE *file;
    char filename[] = "data/usuarios.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        while (fscanf(file, "%d '%49[^']' %19s %19s %19s %d %d",
                      &usuarios[numUsuarios].id,
                      usuarios[numUsuarios].nome,
                      usuarios[numUsuarios].login,
                      usuarios[numUsuarios].senha,
                      usuarios[numUsuarios].tipo,
                      &usuarios[numUsuarios].status,
                      &usuarios[numUsuarios].id_evento) == 7) {
            if (usuarios[numUsuarios].id == id) {
                usuarioEncontrado = usuarios[numUsuarios];
                fclose(file);
                return usuarioEncontrado;
            }
            numUsuarios++;
        }
        fclose(file);
    } else {
        perror("Erro ao abrir o arquivo de usuários");
        exit(1);
    }
    // Se não encontrar nenhum usuário com o ID especificado, retorna um usuário com ID -1
    usuarioEncontrado.id = -1;
    return usuarioEncontrado;
}

// Função para carregar os usuários do arquivo usuarios.txt
