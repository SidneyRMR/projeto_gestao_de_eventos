#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "usuario.h"
#include "evento.h"
#include "components.h"
#include "menu.h"

// Função para cadastro de usuário
void criarUsuario() {
    Usuario usuario;
    int opcaoTipo = 0;

    imprimirTituloCabecario("TELA DE CADASTRO DE USUARIO",NULL);

    char *p_nome = centralizarEObterValorChar("Digite o nome: ", 51);
    strncpy(usuario.nome, p_nome, sizeof(usuario.nome) - 1);

    char *p_login = centralizarEObterValorChar("Digite o login: ", 21);
    strncpy(usuario.login, p_login, sizeof(usuario.login) - 1);

    char *p_senha = centralizarEObterValorChar("Digite a senha: ", 11);
    strncpy(usuario.senha, p_senha, sizeof(usuario.senha) - 1);

    imprimirLinhaDivisoria();

    // Preencher a estrutura do usuário com os dados inseridos
    usuario.id = carregarUltimoUsuario(); // Incrementar +1 a partir do ID do último usuário
    usuario.status = 1; // Status 1 é referente a usuário ativo
    strcpy(usuario.tipo, "vendedor"); // Todos os usuários novos que forem cadastrados serão vendedores

    listarEventosCadastro();
    int eventoMax = carregarUltimoEvento();
    int opcaoEvento = 0;

    do {
        opcaoEvento = centralizarEObterValorInt("Digite o codigo do evento para o usuario: ");
        //printf("|\tDigite o codigo do evento para o usuario: ");
        //scanf("%d", &opcaoEvento);
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

        imprimirUsuarioEData();
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

    // Abre o arquivo em modo de acréscimo ("a"), que cria o arquivo se ele não existir
    file = fopen(filename, "a");

    if (file != NULL) {
        // Escreve os dados do usuário no arquivo
        fprintf(file, "%d '%s' %s %s %s %d %d\n", usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, usuario.status, usuario.id_evento);
        fclose(file);
        printf("Usuario salvo com sucesso!\n");
    } else {
        // Exibe uma mensagem de erro se o arquivo não pôde ser aberto
        perror("Erro ao abrir o arquivo");
    }
}

char* obterNomeUsuario(const char *nomeArquivo, int idBusca) {
    //FILE *file = fopen('data/'+nomeArquivo, "r");
    char caminhoArquivo[100]; // Ajuste o tamanho conforme necessário
    sprintf(caminhoArquivo, "data/%s", nomeArquivo);
    FILE *file = fopen(caminhoArquivo, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    Usuario usuario;
    char *nomeEvento = NULL;

    while (fscanf(file, "%d '%30[^']' %s %s %s %d %d", &usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, &usuario.status, &usuario.id_evento) != EOF) {
        if (usuario.id == idBusca) {
            nomeEvento = (char*)malloc(strlen(usuario.nome) + 1);
            if (nomeEvento != NULL) {
                strcpy(nomeEvento, usuario.nome);
            } else {
                perror("Erro ao alocar memória para o nome do evento");
            }
            break;
        }
    }

    fclose(file);
    return nomeEvento;
}

void alterarStatusUsuario() {
    int escolhaIdUsuario;
    int idMax = carregarUltimoUsuario();

    do {
        system("cls");
        listarUsuarios();
        escolhaIdUsuario = centralizarEObterValorInt(
                "Escolha o codigo da venda que deseja ver o relatorio (ou digite 0 para SAIR): ");
        switch (escolhaIdUsuario) {
            case 0:
                menuAdministrador();
                break;
            default:
                if (escolhaIdUsuario < 1 || escolhaIdUsuario >= idMax) {
                    opcaoInvalida();
                } else {
                    alterarStatusDoUsuario(escolhaIdUsuario);
                }
        }
    } while (escolhaIdUsuario != 0 && (escolhaIdUsuario < 1 || escolhaIdUsuario >= idMax));
}
void alterarStatusDoUsuario(int idUsuario) {
    FILE *arquivo;
    arquivo = fopen("usuario.txt", "r+");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Usuario usuario;

    while (fread(&usuario, sizeof(Usuario), 1, arquivo)) {
        if (usuario.id == idUsuario) {
            fseek(arquivo, -sizeof(Usuario), SEEK_CUR);
            usuario.status = 0;
            fwrite(&usuario, sizeof(Usuario), 1, arquivo);
            printf("Status do usuário com ID %d alterado para 0.\n", idUsuario);
            fclose(arquivo);
            return;
        }
    }

    printf("Usuário com ID %d não encontrado.\n", idUsuario);
    fclose(arquivo);
}