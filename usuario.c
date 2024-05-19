#include <stdio.h>
#include <string.h>
#include "usuario.h"
#include "evento.h"
#include "components.h"
#include "menu.h"

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

    imprimirLinhaDivisoria();

    // Preencher a estrutura do usuário com os dados inseridos
    usuario.id = carregarUltimoUsuario(); // Incrementar +1 a partir do ID do último usuário
    usuario.status = 1; // Status 1 é referente a usuário ativo
    strcpy(usuario.tipo, "vendedor"); // Todos os usuários novos que forem cadastrados serão vendedores

    listarEventosCadastro();
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

        printf("| %-3s | %-30s | %-15s | %-10s | %-13s | %-8s | %-15s |\n", "Cod", "Nome", "Login", "Senha", "Tipo", "Status", "Evento");
        imprimirLinhaDivisoria();

        Usuario usuario;
        char aux_senha[20]; // Ajuste o tamanho conforme necessário

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%30[^']' %s %s %s %d %d", &usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, &usuario.status, &usuario.id_evento) != EOF) {
            char status[10];
            if(usuario.status == 1){
                strcpy(status, "Ativo");
            } else {
                strcpy(status, "Desativo");
            }
            strcpy(aux_senha, "******");
            char* nomeEvento = obterNomeEvento("eventos.txt", usuario.id_evento);

            printf("| %-3d | %-30s | %-15s | %-10s | %-13s | %-8s | %-15s |\n", usuario.id, usuario.nome, usuario.login, aux_senha, usuario.tipo, status, nomeEvento);
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


