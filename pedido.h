#ifndef PEDIDO_H
#define PEDIDO_H
#include <pthread.h>
#include"globals.h"

extern int bancadas_disponiveis;
extern int cozinhas_disponiveis;
extern int pedidos_atendidos;
extern int pedidos_nao_atendidos;

typedef struct Pedido {
    int id;
    int tempo_preparo;
    int tempo_cozinha;
    struct Pedido *proximo;
} Pedido;

extern Pedido *lista_pedidos;
extern pthread_mutex_t pedido_mutex;

void adicionar_pedido(int id, int tempo_preparo, int tempo_cozinha);
void remover_pedido(int id);

#endif // PEDIDO_H