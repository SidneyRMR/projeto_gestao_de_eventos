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
                imprimirTituloCabecarioDuplo("LISTAGEM DE TODOS OS EVENTO", NULL);
                listarEventos();
                system("PAUSE");
                system("cls");
                break;
            case 2:
                imprimirTituloCabecarioDuplo("LISTAGEM DE TODOS OS USUARIO", NULL);
                listarUsuarios();
                system("PAUSE");
                system("cls");
                break;
            case 3:
                imprimirTituloCabecarioDuplo("LISTAGEM DE TODOS OS PRODUTOS", NULL);
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
                menuEditarEvento();
                system("cls");
                break;
            case 8:
                //menuEditarUsuario();
                system("cls");
                break;
            case 9:
                //menuEditarProduto();
                system("cls");
                break;
            case 20:
                relatorioVendasAux();
                system("PAUSE");
                system("cls");
                break;
            case 21:
                ajustarEstoque();
                system("cls");
                break;
            case 0:
                centralizarFrase("Logoff feito com sucesso!...");
                login();
                break;
            default:
                opcaoInvalida();
                break;
        }
    }
}

int selecaoEvento() {
    listarEventos();
    int idMaxEvento = carregarUltimoEvento();
    int idEvento;

    // Verifica se o ID do evento está dentro do intervalo válido
    do {
        idEvento = centralizarEObterValorInt("Escolha o evento que deseja alterar:");

    } while (idEvento <= 0 || idEvento >= idMaxEvento);
    return idEvento;
}


int menuEditarEvento() {
    system("cls");
    imprimirTituloCabecarioDuplo("MENU DE EDICAO DE EVENTO", NULL);

    int idEventoAux;
    idEventoAux = selecaoEvento();
    int opcaoAdmEvento = 0;


    printf("opcao adm %d \n", opcaoAdmEvento);
    printf("idEvento %d \n", idEventoAux);

    imprimirLinhaDivisoriaAjustavel(48);
    imprimirCentralizadoLista(" Cod |  Descricao                           ");
    imprimirLinhaDivisoriaAjustavel(48);
    imprimirCentralizadoLista("  1  |  Para editar o nome deste evento     ");
    imprimirCentralizadoLista("  2  |  Para editar a descricao deste evento");
    imprimirCentralizadoLista("  3  |  Para desativar este evento          ");
    imprimirLinhaDivisoriaAjustavel(48);
    imprimirCentralizadoLista("  0  |  Para voltar ao menu principal       ");
    imprimirLinhaDivisoriaAjustavel(48);

    printf("opcao adm %d \n", opcaoAdmEvento);
    printf("idEvento %d \n", idEventoAux);

    opcaoAdmEvento = centralizarEObterValorInt("Escolha uma opcao:");

    printf("opcao adm %d \n", opcaoAdmEvento);
    printf("idEvento %d \n", idEventoAux);
    system("PAUSE");

    switch (opcaoAdmEvento) {
        case 1:
            EditarNomeEvento(idEventoAux);
            break;
        case 2:
            EditarDescricaoEvento(idEventoAux);
            break;
        case 3:
            DesativarEvento(idEventoAux);
            break;
        case 0:
            menuAdministrador();
            return 0;
        default:
            opcaoInvalida();
            break;
    }
    system("PAUSE");
    menuEditarEvento();

    return 0;
}



int menuEditarUsuario() {
    // todo - a fazer
}

int menuEditarProduto() {
    // todo - a fazer
}

int escolherMenu() {
    char dataAtual[11];
    char ddata[11];
    char tipoUsuario[15];

    strcpy(tipoUsuario, getUsuarioCompartilhado().tipo);
    obterDataAtual(dataAtual);

    strcpy(ddata, dataAtual);
    system("cls");

    if(strcmp(tipoUsuario, "administrador")) {
        limparResumo();
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
