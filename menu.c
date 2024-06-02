#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "evento/evento.h"
#include "usuario.h"
#include "produto.h"
#include "venda.h"
#include "menu.h"
#include "venda_detalhes.h"
#include "variaveis_compartilhadas.h"
#include "components/components.h"
#include "login.h"


int menuAdministrador() {
    int opcaoAdm = 999;

    system("cls");
    while(opcaoAdm != 0) {
    imprimirTituloCabecarioDuplo("MENU ADMINISTRATIVO",NULL);
    imprimirUsuarioEData();
    centralizarFrase("ESCOLHA UM NUMERO CORRESPONDENTE A SUA OPCAO","warning");
    imprimirLinhaDivisoria();
    printf("|       1   -   Ver Eventos           |       4   -   Criar Evento           |       7   -   Editar Evento         |\n");
    printf("|       2   -   Ver Usuarios          |       5   -   Criar Usuario          |       8   -   Editar Usuario        |\n");
    printf("|       3   -   Ver Produtos          |       6   -   Criar Produto          |       9   -   Editar Produto        |\n");
    imprimirLinhaDivisoria();
    printf("|      20   -   Relatorio de Vendas   |       0   -   Fazer Logoff           |      -1   -   Fechar programa       |\n");
    imprimirLinhaDivisoria();

    opcaoAdm = centralizarEObterValorInt("Escolha uma opcao:");
    int opcaoSair;


        switch (opcaoAdm) {
            case 1:
                system("cls");
                imprimirTituloCabecarioDuplo("LISTAGEM DE TODOS OS EVENTO", NULL);
                listarEventos();
                while (opcaoSair != 0) {
                    opcaoSair = centralizarEObterValorInt("Digite 0 para sair.");
                }
                //system("cls");
                break;
            case 2:
                system("cls");
                imprimirTituloCabecarioDuplo("LISTAGEM DE TODOS OS USUARIO", NULL);
                listarUsuarios();
                opcaoSair = 1;
                while (opcaoSair != 0) {
                    opcaoSair = centralizarEObterValorInt("Digite 0 para sair.");
                }
                //system("cls");
                break;
            case 3:
                system("cls");
                imprimirTituloCabecarioDuplo("LISTAGEM DE TODOS OS PRODUTOS", NULL);
                listarProdutos();
                opcaoSair = 1;
                while (opcaoSair != 0) {
                    opcaoSair = centralizarEObterValorInt("Digite 0 para sair.");
                }
                break;
            case 4:
                system("cls");
                criarEvento();
                //system("cls");
                break;
            case 5:
                system("cls");
                criarUsuario();
                //system("cls");
                break;
            case 6:
                system("cls");
                criarProduto();
                //system("cls");
                break;
            case 7:
                system("cls");
                menuEditarEvento();
                //system("cls");
                break;
            case 8:
                system("cls");
                menuEditarUsuario();
                //system("cls");
                break;
            case 9:
                system("cls");
                menuEditarProduto();
                //system("cls");
                break;
            case 20:
                system("cls");
                relatorioVendasAux();
                //system("cls");
                break;
            case -1:
                centralizarFrase("  Saindo do programa!", "info");
                Sleep(1000);
                exit(1);
            case 0:
                centralizarFrase("  Logoff feito com sucesso!", "info");
                //system("cls");
                login();
                break;
            default:
                opcaoInvalida();
                //system("cls");
                break;
        }
        menuAdministrador();
    system("cls");
    }

    return 0;
}

int selecaoEvento() {
    listarEventos();
    int idMaxEvento = carregarUltimoEvento();
    int idEvento;

    // Verifica se o ID do evento está dentro do intervalo válido
    do {
        idEvento = centralizarEObterValorInt("Escolha o evento que deseja alterar ( 0 - Sair):");

    } while (idEvento < 0 || idEvento >= idMaxEvento);
    if (idEvento == 0) {
        return menuAdministrador();
    } else {
        return idEvento;
    }
}

int selecaoUsuario() {
    listarUsuarios();
    int idMaxUsuario = carregarUltimoUsuario();
    int idUsuario;

    // Verifica se o ID do usuário está dentro do intervalo válido
    do {
        idUsuario = centralizarEObterValorInt("Escolha o usuario que deseja alterar ( 0 - Sair):");

    } while (idUsuario < 0 || idUsuario >= idMaxUsuario);
    if (idUsuario == 0) {
        menuAdministrador();
        return 0;
    } else {
        return idUsuario;
    }
}

int selecaoProduto() {
    listarProdutos();
    int idMaxProduto = carregarUltimoProduto();
    int idProduto;

    // Verifica se o ID do usuário está dentro do intervalo válido
    do {
        idProduto = centralizarEObterValorInt("Escolha o produto que deseja alterar ( 0 - Sair):");

    } while (idProduto < 0 || idProduto >= idMaxProduto);
    if (idProduto == 0) {
        menuAdministrador();
        return 0;
    } else {
        return idProduto;
    }
}

int menuEditarProduto() {
        imprimirTituloCabecarioDuplo("MENU DE EDICAO DE PRODUTO", NULL);

        int idProdutoAux = selecaoProduto();
    while (1) {
        Produto produto = buscarProdutoPorID(idProdutoAux);
        system("cls");
        imprimirTituloCabecarioDuplo("EDICAO DE PRODUTO", produto.descricao);
        char* nomeEvento = obterNomeEvento("eventos.txt", produto.id_evento);
        char prodAtivado[11];

        if (produto.status == 1) {
            strcpy(prodAtivado, "Ativo");
        } else {
            strcpy(prodAtivado, "Inativo");
        }
        imprimirLinhaDivisoria();
        printf("| %-3s | %-50s | %-10s | %-9s | %-15s | %-10s |\n", "Cod", "Descricao", "Preco", "Estoque", "Evento", "Status");
        imprimirLinhaDivisoria();
        printf("| %-3d | %-50.50s | %-10.2f | %-9d | %-15.15s | %-10s |\n",
               produto.id, produto.descricao, produto.preco, produto.estoque, nomeEvento, prodAtivado);
        imprimirLinhaDivisoria();
        imprimirLinhaDivisoriaAjustavel(47);
        imprimirCentralizadoLista(" COD |  ALTERAR                              ");
        imprimirLinhaDivisoriaAjustavel(47);
        imprimirCentralizadoLista("  1  |  NOME do produto                      ");
        imprimirCentralizadoLista("  2  |  PRECO do produto                     ");
        imprimirCentralizadoLista("  3  |  ESTOQUE do produto                   ");
        imprimirCentralizadoLista("  4  |  EVENTO do produto                    ");
        imprimirCentralizadoLista("  5  |  ATIVAR / DESATIVAR produto           ");
        imprimirLinhaDivisoriaAjustavel(47);
        imprimirCentralizadoLista("  0  |  SAIR                                 ");
        imprimirLinhaDivisoriaAjustavel(47);

        int opcaoAdmProduto = centralizarEObterValorInt("Escolha uma opcao (0 para selecionar outro produto):");

        switch (opcaoAdmProduto) {
            case 1: {
                char *novoNome = centralizarEObterValorChar("Digite o novo nome do evento: ", 50);
                strcpy(produto.descricao, novoNome);
                atualizarProduto(produto);
                break;
            }
            case 2: {
                double novopreco;
                do {
                    novopreco = centralizarEObterValorDouble("Digite o novo preco do produto: ");
                    if (novopreco > 1000) {
                        centralizarFrase("Erro: O preço nao pode ser maior que 1000. Por favor, insira novamente.", "warning");
                    }
                } while (novopreco > 1000);

                produto.preco = novopreco;
                atualizarProduto(produto);
                break;
            }
            case 3: {


                    ajustarEstoqueSelecionado(produto.id);
                    break;
                }
            case 4: {
                listarEventosCadastro();
                int eventoMax = carregarUltimoEvento();
                int idEvento = 0;

                do {
                    idEvento = centralizarEObterValorInt("Digite o novo evento para o produto: ");
                } while(idEvento < 1 || idEvento >= eventoMax);
                produto.id_evento = idEvento;
                atualizarProduto(produto);
                break;
            }
            case 5:{
                if (produto.status == 0) {
                    produto.status = 1;
                    atualizarProduto(produto);
                } else {
                    produto.status = 0;
                    atualizarProduto(produto);
                }
                break;
            }
            case 0:
                system("cls");
                menuEditarProduto();
                return 0;

            default:
                opcaoInvalida();
                break;
        }
        //system("cls");
    }
}

int menuEditarEvento() {
    imprimirTituloCabecarioDuplo("MENU DE EDICAO DE EVENTO", NULL);

    int idEventoAux = selecaoEvento(); // Seleciona o evento a ser editado
    Evento evento = buscarEventoPorID(idEventoAux); // Obtém informações do evento selecionado

    while (1) { // Loop para manter o menu em execução
        system("cls");

        imprimirTituloCabecarioDuplo("EDICAO DE EVENTO", evento.evento); // Título do menu de edição com nome do evento

        // Exibição das informações do evento
        printf("| %-3s | %-30s | %-60s | %-10s |\n", "Cod", "Nome", "Descricao", "Status");
        imprimirLinhaDivisoria();
        printf("| %-3d | %-30.30s | %-60.60s | %-10s |\n",
               evento.id, evento.evento, evento.descricao, evento.status == 1 ? "Ativo" : "Inativo");
        imprimirLinhaDivisoria();

        // Menu de opções para edição do evento
        imprimirLinhaDivisoriaAjustavel(47);
        imprimirCentralizadoLista(" COD |  ALTERAR                              ");
        imprimirLinhaDivisoriaAjustavel(47);
        imprimirCentralizadoLista("  1  |  NOME do evento                       ");
        imprimirCentralizadoLista("  2  |  DESCRICAO do evento                  ");
        imprimirCentralizadoLista("  3  |  ATIVAR / DESATIVAR evento            ");
        imprimirLinhaDivisoriaAjustavel(47);
        imprimirCentralizadoLista("  0  |  SAIR                                 ");
        imprimirLinhaDivisoriaAjustavel(47);

        int opcaoAdmEvento = centralizarEObterValorInt("Escolha uma opcao:");

        switch (opcaoAdmEvento) {
            case 1: {
                char *novoNome = centralizarEObterValorChar("Digite o novo nome do evento: ", 20);
                strcpy(evento.evento, novoNome);
                atualizarEvento(evento);
                break;
            }
            case 2: {
                char *novaDescricao = centralizarEObterValorChar("Digite a nova descricao do evento: ", 50);
                strcpy(evento.descricao, novaDescricao);
                atualizarEvento(evento);
                break;
            }
            case 3: {
                evento.status = evento.status == 0 ? 1 : 0; // Inverte o status do evento
                atualizarEvento(evento);
                break;
            }
            case 0: // Opção para sair do menu
                system("cls");
                menuEditarEvento();
            default:
                opcaoInvalida();
                break;
        }
    }
}
int menuEditarUsuario() {
    imprimirTituloCabecarioDuplo("MENU DE EDICAO DE USUARIO", NULL);

    int idUsuarioAux = selecaoUsuario(); // Seleciona o usuário a ser editado
    Usuario usuario = buscarUsuarioPorId(idUsuarioAux); // Obtém informações do usuário selecionado

    while (1) { // Loop para manter o menu em execução
        system("cls");

        imprimirTituloCabecarioDuplo("EDICAO DE USUARIO", usuario.nome); // Título do menu de edição com nome do usuário
        char* nomeEvento = obterNomeEvento("eventos.txt", usuario.id_evento);
        // Exibição das informações do usuário
        printf("| %-3s | %-30s | %-20s | %-13s | %-20s | %-11s |\n", "Cod", "Nome", "Login", "Tipo", "Evento", "Status");
        imprimirLinhaDivisoria();
        printf("| %-3d | %-30.30s | %-20.20s | %-13s | %-20.20s | %-11s |\n",
               usuario.id, usuario.nome, usuario.login, usuario.tipo, nomeEvento, usuario.status == 1 ? "Ativo" : "Inativo");
        imprimirLinhaDivisoria();

        // Menu de opções para edição do usuário
        imprimirLinhaDivisoriaAjustavel(47);
        imprimirCentralizadoLista(" COD |  ALTERAR                              ");
        imprimirLinhaDivisoriaAjustavel(47);
        imprimirCentralizadoLista("  1  |  NOME do usuario                      ");
        imprimirCentralizadoLista("  2  |  LOGIN do usuario                     ");
        imprimirCentralizadoLista("  3  |  SENHA do usuario                     ");
        imprimirCentralizadoLista("  4  |  EVENTO DO usuario                    ");
        imprimirCentralizadoLista("  5  |  ATIVAR / DESATIVAR usuario           ");
        imprimirLinhaDivisoriaAjustavel(47);
        imprimirCentralizadoLista("  0  |  Para voltar ao menu principal        ");
        imprimirLinhaDivisoriaAjustavel(47);

        int opcaoAdmUsuario = centralizarEObterValorInt("Escolha uma opcao:");

        switch (opcaoAdmUsuario) {
            case 1: {
                char *novoNome = centralizarEObterValorChar("Digite o novo nome do usuario: ", 50);
                strcpy(usuario.nome, novoNome);
                atualizarUsuario(usuario);
                break;
            }
            case 2: {

                char *novoLogin;
                int loginExistente;
                do {
                    novoLogin = centralizarEObterValorChar("Digite o novo login do usuario: ", 20);

                    loginExistente = verificarLoginExistente(novoLogin);
                    if (loginExistente) {
                        centralizarFrase("Login ja existe. Por favor, escolha outro login.", "warning");
                        free(novoLogin); // Liberar a memória alocada para o login
                    }
                } while (loginExistente);
                strcpy(usuario.login, novoLogin);
                atualizarUsuario(usuario);
                break;

            }
            case 3: {
                char *senhaAcesso = centralizarEObterValorSenha("Senha de autorizacao: ", 11);
                if (senhaAcesso != NULL && strcmp(senhaAcesso, getUsuarioCompartilhado().senha) == 0) {
                    char *novaSenha = centralizarEObterValorSenha("Digite a nova senha do usuario: ", 11);
                    strcpy(usuario.senha, novaSenha);
                    atualizarUsuario(usuario);
                } else {
                    centralizarFrase("Senha administrativa incorreta.","warning");
                }
                // Liberar a memória alocada para senhaAcesso
                free(senhaAcesso);
                break;
            }
            case 4: {
                listarEventosCadastro();
                int eventoMax = carregarUltimoEvento();
                int idEvento = 0;

                do {
                    idEvento = centralizarEObterValorInt("Digite o novo evento para o usuario: ");
                } while(idEvento < 1 || idEvento >= eventoMax);
                usuario.id_evento = idEvento;
                atualizarUsuario(usuario);
                break;
            }
            case 5: {
                usuario.status = usuario.status == 0 ? 1 : 0; // Inverte o status do usuário
                atualizarUsuario(usuario);
                break;
            }
            case 0: // Opção para sair do menu
                return 0;
            default:
                opcaoInvalida();
                break;
        }
    }
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
        centralizarFrase("Erro ao abrir o arquivo","error");
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
                centralizarFrase("Erro ao alocar memória","error");
            }
            break;
        }
    }

    fclose(file);
    return nomeEvento;
}
void menuVenda() {
    system("cls");
    imprimirTituloCabecarioDuplo("MENU DE VENDAS",NULL);
    listarProdutosVenda();
    resumoVenda();
    opcoesVenda();
}
