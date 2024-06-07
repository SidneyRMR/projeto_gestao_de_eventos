#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "usuario.h"
#include "evento.h"
#include "components.h"
#include "menu.h"

// Função para verificar se o login já existe
int verificarLoginExistente(const char *login) {
    char caminhoArquivo[100]; // Ajuste o tamanho conforme necessário
    sprintf(caminhoArquivo, "data/usuarios.txt");
    FILE *file = fopen(caminhoArquivo, "r");

    if (file == NULL) {
        centralizarFrase("Não foi possível abrir o arquivo de usuários.", "error");
        return -1; // Retorna -1 se houver um erro ao abrir o arquivo
    }

    Usuario usuario;

    while (fscanf(file, "%d '%30[^']' '%[^']' '%[^']' %s %d %d", &usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, &usuario.status, &usuario.id_evento) != EOF) {
        if (strcmp(usuario.login, login) == 0) {
            fclose(file);
            return 1; // Retorna 1 se o login já existir
        }
    }

    fclose(file);
    return 0; // Retorna 0 se o login não existir
}
void criarUsuario() {
    Usuario usuario;

    imprimirTituloCabecarioDuplo("TELA DE CADASTRO DE USUARIO", NULL);
    centralizarFrase("Digite 0 a qualquer momento para sair","warning");
    imprimirLinhaDivisoria();

    char *p_nome = centralizarEObterValorChar("Digite o nome: ", 50);
    if (strcmp(p_nome, "0") == 0) {
        return; // Sai da função se o usuário digitar 0
    }
    char *p_login;
    int loginExistente;
    do {
        p_login = centralizarEObterValorChar("Digite o login: ", 20);
        if (strcmp(p_login, "0") == 0) {
            free(p_login); // Liberar a memória alocada para o login
            return; // Sai da função se o usuário digitar 0
        }
        loginExistente = verificarLoginExistente(p_login);
        if (loginExistente) {
            centralizarFrase("Login ja existe. Por favor, escolha outro login.", "warning");
            free(p_login); // Liberar a memória alocada para o login
        }
    } while (loginExistente);
    char *p_senha = centralizarEObterValorChar("Digite a senha: ", 10);
    if (strcmp(p_senha, "0") == 0) {
        return; // Sai da função se o usuário digitar 0
    }

    listarEventosCadastro();
    int eventoMax = carregarUltimoEvento();
    int opcaoEvento = 0;
    do {
        opcaoEvento = centralizarEObterValorInt("Digite o codigo do evento para o usuario: ");
        if (opcaoEvento == 0) {
            return; // Sai da função se o usuário digitar 0
        }
    } while(opcaoEvento < 1 || opcaoEvento >= eventoMax);
    char* nomeEvento = obterNomeEvento("eventos.txt", opcaoEvento);

    imprimirLinhaDivisoria();

    // Imprimir os valores lidos
    imprimirTituloCabecarioLista("Valores lidos", NULL);
    centralizarFraseDoisValores("Nome:  ", p_nome);
    centralizarFraseDoisValores("Login: ", p_login);
    //centralizarFraseDoisValores("Senha: ", p_senha);
    centralizarFraseDoisValores("Evento: ", nomeEvento);
    imprimirLinhaLista();

    // Solicitar confirmação
    char confirmacao[4];
    do {
        strcpy(confirmacao, centralizarEObterValorChar("Confirme se os valores estao corretos (sim/nao): ", 3));

        if (strcmp(confirmacao, "0") == 0) {
            return; // Sai da função se o usuário digitar 0
        }

        if (strcmp(confirmacao, "nao") == 0) {
            system("cls");
            criarUsuario(); // Chamada recursiva para inserir os valores novamente
            return; // Retorna após a chamada recursiva para evitar continuar o loop
        }

    } while (strcmp(confirmacao, "sim") != 0);


    // Preencher a estrutura do usuário com os dados inseridos
    usuario.id = carregarUltimoUsuario(); // Incrementar +1 a partir do ID do último usuário
    usuario.status = 1; // Status 1 é referente a usuário ativo
    strcpy(usuario.tipo, "vendedor"); // Todos os usuários novos que forem cadastrados serão vendedores
    strncpy(usuario.nome, p_nome, sizeof(usuario.nome) - 1);
    strncpy(usuario.login, p_login, sizeof(usuario.login) - 1);
    strncpy(usuario.senha, p_senha, sizeof(usuario.senha) - 1);
    usuario.id_evento = opcaoEvento;

    // Salvar o usuário
    salvarUsuario(usuario);

    //centralizarFrase("Usuario criado com sucesso.", "success");
}



int listarUsuarios() {
    FILE *file;
    char filename[] = "data/usuarios.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        // Imprimir cabeçalho da tabela
        imprimirTituloCabecario("LISTA DE USUARIOS", NULL);
        imprimirUsuarioEData();

        printf("| %-3s | %-30s | %-20s | %-13s | %-23s | %-8s |\n", "Cod", "Nome", "Login", "Tipo", "Evento", "Status");
        imprimirLinhaDivisoria();

        Usuario usuario;
        int encontrouUsuarios = 0;

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%30[^']' '%15[^']' '%11[^']' %s %d %d", &usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, &usuario.status, &usuario.id_evento) != EOF) {
            char status[10];
            if(usuario.status == 1){
                strcpy(status, "Ativo");
            } else {
                strcpy(status, "Inativo");
            }
            char* nomeEvento = obterNomeEvento("eventos.txt", usuario.id_evento);

            printf("| %-3d | %-30.30s | %-20.20s | %-13s | %-23.23s | %-8s |\n",
                   usuario.id, usuario.nome, usuario.login, usuario.tipo, nomeEvento, status);

            free(nomeEvento);  // Liberar memória alocada para o nome do evento
            encontrouUsuarios = 1;
        }
        if (!encontrouUsuarios) {
            centralizarFrase("Nenhum usuário encontrado.", "warning");
        }
        imprimirLinhaDivisoria();
        fclose(file);


    } else {
        centralizarFrase("Não foi possível abrir o arquivo.", "error");
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
    } else {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
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
        fprintf(file, "%d '%s' '%s' '%s' %s %d %d\n", usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, usuario.status, usuario.id_evento);
        fclose(file);
        centralizarFrase("Usuario salvo com sucesso!","success");
    } else {
        // Exibe uma mensagem de erro se o arquivo não pôde ser aberto
        centralizarFrase("Não foi possível abrir o arquivo.","error");
    }
}

char* obterNomeUsuario(const char *nomeArquivo, int idBusca) {
    //FILE *file = fopen('data/'+nomeArquivo, "r");
    char caminhoArquivo[100]; // Ajuste o tamanho conforme necessário
    sprintf(caminhoArquivo, "data/%s", nomeArquivo);
    FILE *file = fopen(caminhoArquivo, "r");

    if (file == NULL) {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
        return NULL;
    }

    Usuario usuario;
    char *nomeEvento = NULL;

    while (fscanf(file, "%d '%30[^']' '%[^']' '%[^']' %s %d %d", &usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, &usuario.status, &usuario.id_evento) != EOF) {
        if (usuario.id == idBusca) {
            nomeEvento = (char*)malloc(strlen(usuario.nome) + 1);
            if (nomeEvento != NULL) {
                strcpy(nomeEvento, usuario.nome);
            } else {
                centralizarFrase("Erro ao alocar memória para o nome do evento","error");
            }
            break;
        }
    }

    fclose(file);
    return nomeEvento;
}

Usuario buscarUsuarioPorId(int id) {
    FILE *file;
    char filename[] = "data/usuarios.txt";
    Usuario usuario;

    file = fopen(filename, "r");
    if (file != NULL) {
        while (fscanf(file, "%d '%[^']' '%[^']' '%[^']' %s %d %d", &usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, &usuario.status, &usuario.id_evento) != EOF) {
            if (usuario.id == id) {
                fclose(file);
                return usuario;
            }
        }
        fclose(file);
    } else {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
    }

    // Retornar um usuário vazio caso não seja encontrado
    Usuario usuarioNaoEncontrado = {0, "", "", "", "", 0, 0};
    return usuarioNaoEncontrado;
}


void atualizarUsuario(Usuario usuario) {

    FILE *file;
    char filename[] = "data/usuarios.txt";
    FILE *tempFile;
    char tempFilename[] = "data/tempUsuarios.txt";
    Usuario tempUsuario;

    file = fopen(filename, "r");
    tempFile = fopen(tempFilename, "w");

    if (file != NULL && tempFile != NULL) {
        while (fscanf(file, "%d '%[^']' '%[^']' '%[^']' %s %d %d", &tempUsuario.id, tempUsuario.nome, tempUsuario.login, tempUsuario.senha, tempUsuario.tipo, &tempUsuario.status, &tempUsuario.id_evento) != EOF) {
            if (tempUsuario.id == usuario.id) {
                // Escrever o usuário atualizado no arquivo temporário
                fprintf(tempFile, "%d '%s' '%s' '%s' %s %d %d\n", usuario.id, usuario.nome, usuario.login, usuario.senha, usuario.tipo, usuario.status, usuario.id_evento);
            } else {
                // Escrever o usuário sem modificação no arquivo temporário
                fprintf(tempFile, "%d '%s' '%s' '%s' %s %d %d\n", tempUsuario.id, tempUsuario.nome, tempUsuario.login, tempUsuario.senha, tempUsuario.tipo, tempUsuario.status, tempUsuario.id_evento);
            }
        }
        fclose(file);
        fclose(tempFile);

        // Remover o arquivo original e renomear o arquivo temporário
        remove(filename);
        rename(tempFilename, filename);

        centralizarFrase("Usuario atualizado com sucesso.", "success");
    } else {
        if (file == NULL) {
            centralizarFrase("Não foi possível abrir o arquivo.","error");
        }
        if (tempFile == NULL) {
            centralizarFrase("Não foi possível abrir o arquivo temporario.","error");
        }
    }
}
