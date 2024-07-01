#include "cozinheiro.h"
#include "pedido.h"
#include "globals.h"
#include "exibicao.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "gerente.h"
#include <stdlib.h>

extern pthread_mutex_t pedido_mutex;
extern Pedido *lista_pedidos;

bool tempo_expirado(); // Declare a função tempo_expirado

void* cozinheiro(void* arg) {
    int id = (int)(long)arg;

    while (1) {
        pthread_mutex_lock(&pedido_mutex);

        if (tempo_expirado() || pedidos_atendidos >= NUMERO_TOTAL_DE_PEDIDOS) {
            pthread_mutex_unlock(&pedido_mutex);
            break;
        }

        if (bancadas_disponiveis > 0 && cozinhas_disponiveis > 0 && lista_pedidos != NULL) {
            Pedido* pedido = lista_pedidos;
            lista_pedidos = pedido->proximo;

            bancadas_disponiveis--;
            cozinhas_disponiveis--;
            printf("\nBancadas disponíveis: %d", bancadas_disponiveis);
            printf("\nCozinhas disponíveis: %d", cozinhas_disponiveis);

            // Atualiza a exibição após pegar um pedido
            exibir_informacoes();

            pthread_mutex_unlock(&pedido_mutex);

            printf("\nCozinheiro %d preparando pedido %d", id, pedido->id);
            sleep(pedido->tempo_preparo);
            printf("\nCozinheiro %d cozinhando pedido %d", id, pedido->id);
            sleep(pedido->tempo_cozinha);

            pthread_mutex_lock(&pedido_mutex);
            bancadas_disponiveis++;
            cozinhas_disponiveis++;
            pedidos_atendidos++;
            printf("\nBancadas disponíveis: %d", bancadas_disponiveis);
            printf("\nCozinhas disponíveis: %d", cozinhas_disponiveis);

            if (pedidos_atendidos == NUMERO_TOTAL_DE_PEDIDOS) {
                printf("Número total de pedidos atendidos.\n");
                pthread_mutex_unlock(&pedido_mutex);
                break;
            }
            
            free(pedido);

            // Atualiza a exibição após concluir um pedido
            exibir_informacoes();
        }

        pthread_mutex_unlock(&pedido_mutex);
        usleep(1000000);
    }

    return NULL;
}

