#ifndef EVENTO_H
#define EVENTO_H

typedef struct {
    int id;
    char evento[21];
    char descricao[51];
    char data[11];
    int status;
} Evento;

void criarEvento();

void listarEventos();

int carregarUltimoEvento();

void salvarEvento(Evento evento);

void listarEventosCadastro();

Evento buscarEventoPorID(int id);

void atualizarEvento(Evento evento);

#endif // EVENTO_H