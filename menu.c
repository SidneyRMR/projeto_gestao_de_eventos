#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "evento.h"
#include "usuario.h"
#include "produto.h"
#include "venda.h"
#include "menu.h"
#include "login.h"
#include "venda_detalhes.h"
#include "variaveis_compartilhadas.h"

void menuVendedor() {
    menuVenda();
}

void menuAdministrador() {
    int opcao = 999;

    system("cls");
    while(opcao != 0) {
    printf("===================================================================================================\n");
    printf("|                                       MENU ADMINISTRATIVO                                       |\n");
    printf("|-------------------------------------------------------------------------------------------------|\n");
    printf("| Opcao |   Listar              || Opcao |   Criar               || Opcao |   Desativar           |\n");
    printf("|-------------------------------------------------------------------------------------------------|\n");
    printf("|   1   |   Listar Eventos      ||   4   |   Criar Evento        ||   7   |   Desativar Evento    |\n");
    printf("|   2   |   Listar Usuarios     ||   5   |   Criar Usuario       ||   8   |   Desativar Usuario   |\n");
    printf("|   3   |   Listar Produtos     ||   6   |   Criar Produto       ||   9   |   Desativar Produto   |\n");
    printf("|-------------------------------------------------------------------------------------------------|\n");
    printf("|  20   |   Relatorio de Vendas                                                                   |\n");
    printf("|-------------------------------------------------------------------------------------------------|\n");
    printf("|   0   |   Sair do Menu Administrativo                          || Usuario: %-20s |\n",UsuarioCompartilhado.nome);
    printf("|-------------------------------------------------------------------------------------------------|\n");
    printf("Escolha uma opcao:");

    scanf("%d", &opcao);

        system("cls");
        switch (opcao) {
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
            case 20:
                relatorioVendasAux();
                system("PAUSE");
                system("cls");
                break;
            case 0:
                printf("Saindo do Menu Administrativo...\n");
                escolherMenu();
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }
}

int escolherMenu() {
    int opcaoMenu = 999;
    char dataAtual[11];
    char ddata[11];
    obterDataAtual(dataAtual);
    strcpy(ddata, dataAtual);
    system("cls");
    while(opcaoMenu != 0) {
        printf("======================================================\n");
        printf("|     BEM VINDO AO PROGRAMA DE GESTAO DE EVENTOS     |\n");
        printf("|----------------------------------------------------|\n");
        printf("| Opcao |              Descricao                     |\n");
        printf("|----------------------------------------------------|\n");
        printf("|   1   |   Menu de Vendas                           |\n");
        printf("|   2   |   Menu Administrativo                      |\n");
        printf("|             --------------------------             |\n");
        printf("|   0   |   Sair do Programa                         |\n");
        printf("|----------------------------------------------------|\n");
        printf("|  DATA: %-11s     | Usuario: %-11s      |\n", ddata, getUsuarioCompartilhado().nome);
        printf("|----------------------------------------------------|\n");
        printf("Escolha uma opcao:");

        scanf("%d", &opcaoMenu);
        system("cls");
        switch (opcaoMenu) {
            case 1:
                menuVendedor();
                system("PAUSE");
                system("cls");
                break;
            case 2:
                menuAdministrador();
                system("cls");
                break;
            case 0:
                system("cls");
                printf("Fazendo logoff...\n");
                system("PAUSE");
                system("cls");
                login();
                return 0;
            default:
                printf("Opcao invalida.\n");
        }
    }
}

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
