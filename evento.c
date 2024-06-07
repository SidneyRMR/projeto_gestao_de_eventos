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
    centralizarFrase("Digite 0 a qualquer momento para sair","warning");
    imprimirLinhaDivisoria();

    char *p_evento = centralizarEObterValorChar("Digite o nome do evento: ", 20);
    if (strcmp(p_evento, "0") == 0) {
        return; // Sai da função se o usuário digitar 0
    }
    char *p_descricao = centralizarEObterValorChar("Digite uma descricao para o evento: ", 50);
    if (strcmp(p_descricao, "0") == 0) {
        return; // Sai da função se o usuário digitar 0
    }

    imprimirLinhaDivisoria();

    // Imprimir os valores lidos
    imprimirTituloCabecarioLista("Valores lidos", NULL);
    centralizarFraseDoisValores("Nome do Evento: ", p_evento);
    centralizarFraseDoisValores("Descricao: ", p_descricao);
    imprimirLinhaLista();

    // Preencher a estrutura do evento com os dados inseridos
    evento.id = carregarUltimoEvento() ; // Incrementar o ID do último evento
    strcpy(evento.evento, p_evento);
    strcpy(evento.descricao, p_descricao);
    obterDataAtual(evento.data);
    evento.status = 1;

    // Solicitar confirmação
    char confirmacao[4];
    do {
        strcpy(confirmacao, centralizarEObterValorChar("Confirme se os valores estao corretos (sim/nao): ", 3));

        if (strcmp(confirmacao, "0") == 0) {
            return; // Sai da função se o usuário digitar 0
        }

        if (strcmp(confirmacao, "nao") == 0) {
            system("cls");
            criarEvento(); // Chamada recursiva para inserir os valores novamente
            return; // Retorna após a chamada recursiva para evitar continuar o loop
        }

    } while (strcmp(confirmacao, "sim") != 0);

    // Salvar o evento
    salvarEvento(evento);

    //centralizarFrase("Evento criado com sucesso.", "success");
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

        Evento evento;
        int encontrouEventos = 0;

        while (fscanf(file, "%d '%[^']' '%[^']' %s %d", &evento.id, evento.evento, evento.descricao, evento.data, &evento.status) != EOF) {
            char status[10];
            if(evento.id == 0) continue; // Condição para ignorar registros com ID zero, se necessário
            if(evento.status == 1){
                strcpy(status, "Ativo");
            } else {
                strcpy(status, "Inativo");
            }
            printf("| %-3d | %-20s | %-57s | %-10s | %-10s |\n", evento.id, evento.evento, evento.descricao, evento.data, status);
            encontrouEventos = 1;
        }
        if (!encontrouEventos) {
            centralizarFrase("Nenhum evento encontrado.", "warning");
        }
        imprimirLinhaDivisoria();
        fclose(file);
    } else {
        centralizarFrase("Não foi possível abrir o arquivo.", "error");
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
        centralizarFrase(linha,"default");
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
            centralizarFrase(linha,"default");
        }

        imprimirLinhaDivisoriaLista();
        fclose(file);
    } else {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
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
    } else {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
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
        centralizarFrase("Evento salvo com sucesso!", "success");
    } else {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
    }
}

Evento buscarEventoPorID(int id) {
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
        centralizarFrase("Não foi possível abrir o arquivo.","error");
    }

    // Retornar um produto vazio caso não seja encontrado
    Evento eventoNaoEncontrado = {0, "", "", "", 0};
    return eventoNaoEncontrado;
}

void atualizarEvento(Evento evento) {
    FILE *file;
    char filename[] = "data/eventos.txt";
    FILE *tempFile;
    char tempFilename[] = "data/tempEvento.txt";
    Evento tempEvento;

    file = fopen(filename, "r");
    tempFile = fopen(tempFilename, "w");

    if (file != NULL && tempFile != NULL) {
        while (fscanf(file, "%d '%[^']' '%[^']' %s %d", &tempEvento.id, tempEvento.evento, tempEvento.descricao, tempEvento.data, &tempEvento.status) != EOF) {
            if (tempEvento.id == evento.id) {
                // Escrever o evento atualizado no arquivo temporário
                fprintf(tempFile, "%d '%s' '%s' %s %d\n", evento.id, evento.evento, evento.descricao, evento.data, evento.status);
            } else {
                // Escrever o evento sem modificação no arquivo temporário
                fprintf(tempFile, "%d '%s' '%s' %s %d\n", tempEvento.id, tempEvento.evento, tempEvento.descricao, tempEvento.data, tempEvento.status);
            }
        }
        fclose(file);
        fclose(tempFile);

        // Remover o arquivo original e renomear o arquivo temporário
        remove(filename);
        rename(tempFilename, filename);

        centralizarFrase("Evento atualizado com sucesso.", "success");
    } else {
        if (file == NULL) {
            centralizarFrase("Não foi possível abrir o arquivo.","error");
        }
        if (tempFile == NULL) {
            centralizarFrase("Não foi possível abrir o arquivo temporario.","error");
        }
    }
}


