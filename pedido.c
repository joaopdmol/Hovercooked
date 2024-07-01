#include "pedido.h"
#include <stdlib.h>
#include "globals.h"
#include "exibicao.h"
#include <ncurses.h>

Pedido *lista_pedidos = NULL;

void adicionar_pedido(int id, int tempo_preparo, int tempo_cozinha) {
    if (pedidos_restantes <= 0) {
        return;  // Não aceita mais pedidos
    }

    Pedido *novo_pedido = (Pedido *)malloc(sizeof(Pedido));
    novo_pedido->id = id;
    novo_pedido->tempo_preparo = tempo_preparo;
    novo_pedido->tempo_cozinha = tempo_cozinha;
    novo_pedido->proximo = lista_pedidos;
    lista_pedidos = novo_pedido;

    pedidos_restantes--;
    atualizar_exibicao();
}

void remover_pedido(int id) {
    Pedido *anterior = NULL;
    Pedido *atual = lista_pedidos;

    while (atual != NULL) {
        if (atual->id == id) {
            if (anterior == NULL) {
                lista_pedidos = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            pedidos_atendidos++;
            atualizar_exibicao();
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}
