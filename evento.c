#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "evento.h"
#include "menu.h"
#include "components.h"

// Definição da estrutura para armazenar os dados do evento
void criarEvento() {
    Evento evento;

    imprimirTituloCabecarioDuplo("TELA DE CADASTRO DE EVENTOS", NULL);

    char *p_evento = centralizarEObterValorChar("Digite o nome do evento: ", 21);
    char *p_descricao = centralizarEObterValorChar("Digite uma descricao para o evento: ", 51);

    imprimirLinhaDivisoria();

    // Imprimir os valores lidos
    imprimirTituloCabecarioLista("Valores lidos:", NULL);
    centralizarFraseDoisValores("Nome do Evento: ", p_evento);
    centralizarFraseDoisValores("Descricao: ", p_descricao);
    imprimirLinhaLista();

    // Preencher a estrutura do evento com os dados inseridos
    evento.id = carregarUltimoEvento() + 1; // Incrementar o ID do último evento
    strncpy(evento.evento, p_evento, sizeof(evento.evento) - 1);
    strncpy(evento.descricao, p_descricao, sizeof(evento.descricao) - 1);
    obterDataAtual(evento.data);
    evento.status = 1;

    // Solicitar confirmação
    char confirmacao[4];
    do {
        strcpy(confirmacao, centralizarEObterValorChar("Confirme se os valores estao corretos (sim/nao): ", 3));
        getchar(); // Limpar o buffer do teclado

        if (strcmp(confirmacao, "nao") == 0) {
            system("cls");
            criarEvento(); // Chamada recursiva para inserir os valores novamente
            return; // Retorna após a chamada recursiva para evitar continuar o loop
        }

    } while (strcmp(confirmacao, "sim") != 0);

    // Salvar o evento
    salvarEvento(evento);

    centralizarFrase("Evento criado com sucesso.");
}


void listarEventos() {
    FILE *file;
    char filename[] = "data/eventos.txt";
    file = fopen(filename, "r");

    if (file != NULL) {

        imprimirTituloCabecario("LISTA DE EVENTOS", NULL);
        imprimirUsuarioEData();

        printf("| %-3s | %-20s | %-57s | %-10s | %-10s |\n", "Cod", "Evento", "Descricao", "Data", "Status");
        imprimirLinhaDivisoria();

        // Variável para armazenar cada registro lido do arquivo
        Evento evento;

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%[^']' '%[^']' %s %d", &evento.id, evento.evento, evento.descricao, evento.data, &evento.status) != EOF) {
            char status[10];
            if(evento.id == 0) continue;
            if(evento.status == 1){
                strcpy(status, "Ativo");
            } else {
                strcpy(status, "Desativo");
            }
            printf("| %-3d | %-20s | %-57s | %-10s | %-10s |\n", evento.id, evento.evento, evento.descricao, evento.data, status);
        }
        imprimirLinhaDivisoria();
        fclose(file);
    } else {
        printf("Não foi possível abrir o arquivo %s.\n\n", filename);
    }
}

void listarEventosCadastro() {
    FILE *file;
    char filename[] = "data/eventos.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        imprimirTituloCabecarioLista("LISTA DE EVENTOS", NULL);
        char linha[80];  // Buffer para armazenar a linha completa
        snprintf(linha, sizeof(linha), "| %-4s | %-21s |", "Cod", "Evento");
        centralizarFraseSemBorda(linha);
        imprimirLinhaDivisoriaLista();

        // Variável para armazenar cada registro lido do arquivo
        Evento evento;

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%[^']' '%[^']' %s %d", &evento.id, evento.evento, evento.descricao, evento.data, &evento.status) != EOF) {
            if (evento.id == 0 || evento.status == 0) {
                continue;
            }
              // Buffer para armazenar a linha completa
            snprintf(linha, sizeof(linha), "| %-4d | %-21s |", evento.id, evento.evento);
            centralizarFraseSemBorda(linha);
        }

        imprimirLinhaDivisoriaLista();
        fclose(file);
    } else {
        printf("Não foi possível abrir o arquivo %s.\n\n", filename);
    }
}

int carregarUltimoEvento() {
    FILE *file;
    char filename[] = "data/eventos.txt";
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
        //printf("|\tRegistro(s): %d\n", contador_linhas);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    return contador_linhas;
}

void salvarEvento(Evento evento) {
    FILE *file;
    char filename[] = "data/eventos.txt";
    file = fopen(filename, "a"); // Abrir o arquivo em modo de escrita, acrescentando ao final

    if (file != NULL) {
        fprintf(file, "%d '%s' '%s' %s %d\n", evento.id, evento.evento, evento.descricao, evento.data, evento.status);
        fclose(file);
        centralizarFrase("Evento salvo com sucesso!");
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }
}

Evento carregarEventoPorID(int id) {
    FILE *file;
    char filename[] = "data/eventos.txt";
    Evento evento;

    file = fopen(filename, "r");
    if (file != NULL) {
        while (fscanf(file, "%d '%[^']' '%[^']' %s %d", &evento.id, evento.evento, evento.descricao, evento.data, &evento.status) != EOF) {
            if (evento.id == id) {
                fclose(file);
                return evento;
            }
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    // Retornar um produto vazio caso não seja encontrado
    Evento eventoNaoEncontrado = {0, "", "", "", 0};
    return eventoNaoEncontrado;
}
/*
int EditarNomeEvento(int idEvento) {
    FILE *arquivo = fopen("data/eventos.txt", "r+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    Evento evento = carregarEventoPorID(idEvento);
    if (evento.id == -1) {
        printf("Evento não encontrado.\n");
        fclose(arquivo);
        return -1;
    }
    printf("%d", idEvento);
    char *novoNome = centralizarEObterValorChar("Digite o novo nome do evento: ", 21);

    rewind(arquivo);

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Erro ao criar o arquivo temporário");
        fclose(arquivo);
        return -1;
    }
    printf("%d", idEvento);

    Evento eventoAtual;
    while (fscanf(arquivo, "%d '%20[^']' '%50[^']' %10s %d\n", &eventoAtual.id, eventoAtual.evento, eventoAtual.descricao, eventoAtual.data, &eventoAtual.status) != EOF) {
        if (eventoAtual.id == idEvento) {
            strcpy(eventoAtual.evento, novoNome);
        }
        fprintf(temp, "%d '%s' '%s' %s %d\n", eventoAtual.id, eventoAtual.evento, eventoAtual.descricao, eventoAtual.data, eventoAtual.status);
    }

    fclose(arquivo);
    fclose(temp);

    remove("data/eventos.txt");
    rename("temp.txt", "data/eventos.txt");

    centralizarFrase("Nome do evento atualizado com sucesso.");
    return 0;
}*/
void atualizarEvento(Evento evento) {
    FILE *file;
    char filename[] = "data/eventos.txt";
    FILE *tempFile;
    char tempFilename[] = "data/tempEvento.txt";
    Evento tempEvento;

    file = fopen(filename, "r");
    tempFile = fopen(tempFilename, "w");

    if (file != NULL && tempFile != NULL) {
        while (fscanf(file, "%d '%20[^']' '%50[^']' %10s %d\n", &tempEvento.id, tempEvento.evento, tempEvento.descricao, tempEvento.data, &tempEvento.status) != EOF) {
            if (tempEvento.id == evento.id) {
                fprintf(tempFile, "%d '%s' '%s' %s %d\n", tempEvento.id, tempEvento.evento, tempEvento.descricao, tempEvento.data, tempEvento.status);
            } else {
                fprintf(tempFile, "%d '%s' '%s' %s %d\n", tempEvento.id, tempEvento.evento, tempEvento.descricao, tempEvento.data, tempEvento.status);
            }
        }
        fclose(file);
        fclose(tempFile);

        // Remover o arquivo original e renomear o arquivo temporário
        remove(filename);
        rename(tempFilename, filename);

        centralizarFrase("Evento atualizado com sucesso.");
    } else {
        if (file == NULL) {
            printf("Erro ao abrir o arquivo %s.\n", filename);
        }
        if (tempFile == NULL) {
            printf("Erro ao criar o arquivo temporário %s.\n", tempFilename);
        }
    }
}
int EditarNomeEvento(int idEvento) {
    FILE *arquivo = fopen("data/eventos.txt", "r+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    Evento evento = carregarEventoPorID(idEvento);
    if (evento.id == -1) {
        printf("Evento não encontrado.\n");
        fclose(arquivo);
        return -1;
    }

    char *novoNome = centralizarEObterValorChar("Digite o novo nome do evento: ", 21);

    FILE *temp = fopen("data/temp.txt", "w");
    if (temp == NULL) {
        perror("Erro ao criar o arquivo temporário");
        fclose(arquivo);
        return -1;
    }

    Evento eventoAtual;
    while (fscanf(arquivo, "%d '%20[^']' '%50[^']' %10s %d\n", &eventoAtual.id, eventoAtual.evento, eventoAtual.descricao, eventoAtual.data, &eventoAtual.status) != EOF) {
        if (eventoAtual.id == idEvento) {
            strcpy(eventoAtual.evento, novoNome);
        }
        fprintf(temp, "%d '%s' '%s' %s %d\n", eventoAtual.id, eventoAtual.evento, eventoAtual.descricao, eventoAtual.data, eventoAtual.status);
    }

    fclose(arquivo);
    fclose(temp);

    remove("data/eventos.txt");
    rename("data/temp.txt", "data/eventos.txt");

    centralizarFrase("Nome do evento atualizado com sucesso.");
    return 0;
}

int EditarDescricaoEvento(int idEvento){
    FILE *arquivo = fopen("data/eventos.txt", "r+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    Evento evento = carregarEventoPorID(idEvento);
    if (evento.id == -1) {
        printf("Evento não encontrado.\n");
        fclose(arquivo);
        return -1;
    }
    printf("%d", idEvento);
    char *novaDescricao = centralizarEObterValorChar("Digite o novo nome do evento: ", 51);

    rewind(arquivo);

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Erro ao criar o arquivo temporário");
        fclose(arquivo);
        return -1;
    }
    printf("%d", idEvento);

    Evento eventoAtual;
    while (fscanf(arquivo, "%d '%20[^']' '%50[^']' %10s %d\n", &eventoAtual.id, eventoAtual.evento, eventoAtual.descricao, eventoAtual.data, &eventoAtual.status) != EOF) {
        if (eventoAtual.id == idEvento) {
            strcpy(eventoAtual.descricao, novaDescricao);
        }
        fprintf(temp, "%d '%s' '%s' %s %d\n", eventoAtual.id, eventoAtual.evento, eventoAtual.descricao, eventoAtual.data, eventoAtual.status);
    }

    fclose(arquivo);
    fclose(temp);

    remove("data/eventos.txt");
    rename("temp.txt", "data/eventos.txt");

    centralizarFrase("Descricao do evento atualizada com sucesso.");
    return 0;
}
int DesativarEvento(int idEvento){
    FILE *arquivo = fopen("data/eventos.txt", "r+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    Evento evento = carregarEventoPorID(idEvento);
    if (evento.id == -1) {
        printf("Evento não encontrado.\n");
        fclose(arquivo);
        return -1;
    }

    rewind(arquivo);

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Erro ao criar o arquivo temporário");
        fclose(arquivo);
        return -1;
    }
    printf("%d", idEvento);

    Evento eventoAtual;
    while (fscanf(arquivo, "%d '%20[^']' '%50[^']' %10s %d\n", &eventoAtual.id, eventoAtual.evento, eventoAtual.descricao, eventoAtual.data, &eventoAtual.status) != EOF) {
        if (eventoAtual.id == idEvento) {
            eventoAtual.status = 0;
        }
        fprintf(temp, "%d '%s' '%s' %s %d\n", eventoAtual.id, eventoAtual.evento, eventoAtual.descricao, eventoAtual.data, eventoAtual.status);
    }

    fclose(arquivo);
    fclose(temp);

    remove("data/eventos.txt");
    rename("temp.txt", "data/eventos.txt");

    centralizarFrase("Evento desativado com sucesso.");
    return 0;
}