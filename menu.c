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

    imprimirTituloCabecarioDuplo("MENU ADMINISTRATIVO",NULL);
    imprimirUsuarioEData();
    printf("| Opcao |     Listar                   | Opcao |     Criar                    | Opcao |     Desativar              |\n");
    imprimirLinhaDivisoria();
    printf("|   1   |     Listar Eventos           |   4   |     Criar Evento             |   7   |     Editar Evento          |\n");
    printf("|   2   |     Listar Usuarios          |   5   |     Criar Usuario            |   8   |     Editar Usuario         |\n");
    printf("|   3   |     Listar Produtos          |   6   |     Criar Produto            |   9   |     Editar Produto         |\n");
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
                //desativarEvento();
                system("cls");
                break;
            case 8:
                alterarStatusUsuario();
                system("cls");
                break;
            case 9:
                //desativarProduto();
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
/*
void menuAdministrador() {
    int opcaoAdm = 999;
    int idMaxEvento = carregarUltimoEvento();
    system("cls");
    while(opcaoAdm != 0) {

    imprimirTituloCabecarioDuplo("MENU ADMINISTRATIVO ",NULL);
    listarEventos();
        centralizarFrase("Cod  |  Para selecionar o evento que deseja gerenciar");
        centralizarFrase("100  |  Para ver relatorios das vendas               ");
        centralizarFrase("  0  |  Para fazer logoff                            ");
        imprimirLinhaDivisoria();
    opcaoAdm = centralizarEObterValorInt("Escolha uma opcao:");

        system("cls");
        switch (opcaoAdm) {
            //case 4:
            //    criarEvento();
            //    system("cls");
            //    break;
            //case 5:
            //    criarUsuario();
            //    system("cls");
            //    break;
            //case 6:
            //    criarProduto();
            //    system("cls");
            //    break;

            case 100:
                relatorioVendasAux();
                system("PAUSE");
                system("cls");
                break;
            case 0:
                centralizarFrase("Logoff feito com sucesso!...");
                login();
                break;
            //case 21:
            //    ajustarEstoque();
            //    //system("PAUSE");
            //    system("cls");
            //    break;
            default:
                if (opcaoAdm > 0 && opcaoAdm <= idMaxEvento-1) {
                    menuEvento(opcaoAdm);
                    system("cls");
                    menuVenda();

                } else {
                    system("cls");
                    opcaoInvalida();
                    menuVenda();
                }
        }
    }
}*/
/*
int menuEvento(int idEvento){
    int opcaoAdmEvento;
    char SubtituloEvento[21];
    Evento evento = carregarEventoPorID(idEvento);

    snprintf(SubtituloEvento, sizeof(SubtituloEvento), "Evento: %-21s", evento.evento);
    imprimirTituloCabecarioDuplo("MENU ADMINISTRATIVO",SubtituloEvento);

    centralizarFrase("  1  |  Para ver e editar os produtos deste evento  ");
    centralizarFrase("  2  |  Para ver e editar os vendedores deste evento");
    centralizarFrase("  3  |  Para ver os relatorios deste evento         ");
    centralizarFrase("  0  |  Para voltar ao menu principal               ");
    imprimirLinhaDivisoria();
    opcaoAdmEvento = centralizarEObterValorInt("Escolha uma opcao:");

    system("cls");
    switch (opcaoAdmEvento) {
        case 1:
            menuProdutos(idEvento);
            system("PAUSE");
            system("cls");
            menuEvento(idEvento);
            break;
        case 2:
            menuVendedores(idEvento);
            system("PAUSE");
            system("cls");
            menuEvento(idEvento);
            break;
        case 3:
            relatorioEventoEspecifico("vendas_detalhes.txt", idEvento);
            system("PAUSE");
            system("cls");
            menuEvento(idEvento);
            break;
        case 0:
            menuAdministrador();
            break;
        default:
            opcaoInvalida();
            break;
    }
    return 0;
}
int menuProdutos(int idEvento){
    int opcao;
    imprimirTituloCabecarioDuplo("MENU ADMINISTRATIVO","PRODUTOS");
    listarProdutos();

    centralizarFrase("  1  |  Para adicionar um novo produto                   ");
    centralizarFrase("  2  |  Para selecionar um produto para editar           ");
    centralizarFrase("  3  |  Para selecionar um produto para ajustar o estoque");
    centralizarFrase("  0  |  Para voltar ao menu do evento                    ");
    imprimirLinhaDivisoria();
    opcao = centralizarEObterValorInt("Escolha uma opcao:");

    system("cls");
    switch (opcao) {
        case 1:
            criarProduto(idEvento);
            system("PAUSE");
            system("cls");
            menuProdutos(idEvento);
            break;
        case 2: {
            int codProdEditar = centralizarEObterValorInt("Qual o codigo do produto que deseja editar: ");
            editarProduto(codProdEditar, idEvento); // todo - fazer verificação se existe este produto neste evento
            system("PAUSE");
            system("cls");
            menuProdutos(idEvento);
            break;
        }
        case 3: {
            int codProdAjustarEstoque = centralizarEObterValorInt("Qual o codigo do produto que deseja ajustar o estoque: ");
            ajustarEstoque(codProdAjustarEstoque); //todo - ajustar a funcao para funcionar bem com este menu
            system("PAUSE");
            system("cls");
            menuProdutos(idEvento);
            break;
        }
        case 0:
            menuEvento(idEvento);
            break;
        default:
            opcaoInvalida();
            break;
    }
    return 0;
}
int menuVendedores(int idEvento){
    int opcao;
    imprimirTituloCabecarioDuplo("MENU ADMINISTRATIVO","VENDEDORES");
    listarUsuarios();

    centralizarFrase("  1  |  Para adicionar um novo vendedor                ");
    centralizarFrase("  2  |  Para selecionar um vendedor para editar        ");
    centralizarFrase("  3  |  Para ver os relatorios de vendas deste vendedor");
    centralizarFrase("  0  |  Para voltar ao menu do evento                  ");
    imprimirLinhaDivisoria();
    opcao = centralizarEObterValorInt("Escolha uma opcao:");

    system("cls");
    switch (opcao) {
        case 1:
            criarProduto(idEvento);
            system("PAUSE");
            system("cls");
            menuVendedores(idEvento);
            break;
        case 2: {
            int codProdEditar = centralizarEObterValorInt("Qual o codigo do produto que deseja editar: ");
            editarProduto(codProdEditar, idEvento); // todo - fazer verificação se existe este produto neste evento
            system("PAUSE");
            system("cls");
            menuVendedores(idEvento);
            break;
        }
        case 3:
            relatorioVendaEspecifico("vendas_detalhes.txt", idEvento);
            system("PAUSE");
            system("cls");
            menuVendedores(idEvento);
            break;
        case 0:
            menuEvento(idEvento);
            break;
        default:
            opcaoInvalida();
            break;
    }
    return 0;
}*/



int escolherMenu() {
    char dataAtual[11];
    char ddata[11];
    char tipoUsuario[15];

    strcpy(tipoUsuario, getUsuarioCompartilhado().tipo);
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
