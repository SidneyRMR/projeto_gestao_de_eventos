#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "evento.h"
#include "usuario.h"
#include "produto.h"
#include "venda.h"
#include "menu.h"
#include "venda_detalhes.h"
#include "variaveis_compartilhadas.h"
#include "components.h"
#include "login.h"


void menuAdministrador() {
    int opcaoAdm = 999;

    system("cls");
    while(opcaoAdm != 0) {

    imprimirTituloCabecario("MENU ADMINISTRATIVO",NULL);
    imprimirUsuarioEData();
    printf("| Opcao |     Listar                   | Opcao |     Criar                    | Opcao |     Desativar              |\n");
    imprimirLinhaDivisoria();
    printf("|   1   |     Listar Eventos           |   4   |     Criar Evento             |   7   |     Desativar Evento       |\n");
    printf("|   2   |     Listar Usuarios          |   5   |     Criar Usuario            |   8   |     Desativar Usuario      |\n");
    printf("|   3   |     Listar Produtos          |   6   |     Criar Produto            |   9   |     Desativar Produto      |\n");
    imprimirLinhaDivisoria();
    printf("|  20   |   Relatorio de Vendas        |   21  |     Ajustar estoque          |   0   |   Fazer Logoff             |\n");
    imprimirLinhaDivisoria();

    opcaoAdm = centralizarEObterValorInt("Escolha uma opcao:");

        system("cls");
        switch (opcaoAdm) {
            case 1:
                listarEventos();
                system("PAUSE");
                system("cls");
                break;
            case 2:
                listarUsuarios();
                system("PAUSE");
                system("cls");
                break;
            case 3:
                listarProdutos();
                system("PAUSE");
                system("cls");
                break;
            case 4:
                criarEvento();
                system("cls");
                break;
            case 5:
                criarUsuario();
                system("cls");
                break;
            case 6:
                criarProduto();
                system("cls");
                break;
            case 7:
                desativarEvento();
                system("cls");
                break;
            case 8:
                desativarUsuario();
                system("cls");
                break;
            case 9:
                desativarProduto();
                system("cls");
                break;
            case 20:
                relatorioVendasAux();
                system("PAUSE");
                system("cls");
                break;
            case 21:
                ajustarEstoque();
                //system("PAUSE");
                system("cls");
                break;
            case 0:
                centralizarFrase("Logoff feito com sucesso!...");
                login();
                break;
            default:
                opcaoInvalida();
        }
    }
}

int escolherMenu() {
    char dataAtual[11];
    char ddata[11];
    char tipoUsuario[15];
    char nomeUsuario[21];

    strcpy(tipoUsuario, getUsuarioCompartilhado().tipo);
    strcpy(nomeUsuario, getUsuarioCompartilhado().nome);
    obterDataAtual(dataAtual);

    strcpy(ddata, dataAtual);
    system("cls");

    if(strcmp(tipoUsuario, "administrador")) {
        menuVenda();
    } else {
        menuAdministrador();
    }
}

// Obtem a data atual
void obterDataAtual(char *dataAtual) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dataAtual, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

char* obterNomeEvento(const char *nomeArquivo, int idEventoBusca) {
    //FILE *file = fopen('data/'+nomeArquivo, "r");
    char caminhoArquivo[100]; // Ajuste o tamanho conforme necessário
    sprintf(caminhoArquivo, "data/%s", nomeArquivo);
    FILE *file = fopen(caminhoArquivo, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    Evento evento;
    char *nomeEvento = NULL;

    while (fscanf(file, "%d '%50[^']' '%100[^']' %10s %d", &evento.id, evento.evento, evento.descricao, evento.data, &evento.status) != EOF) {
        if (evento.id == idEventoBusca) {
            nomeEvento = (char*)malloc(strlen(evento.evento) + 1);
            if (nomeEvento != NULL) {
                strcpy(nomeEvento, evento.evento);
            } else {
                perror("Erro ao alocar memória para o nome do evento");
            }
            break;
        }
    }

    fclose(file);
    return nomeEvento;
}
