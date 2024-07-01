#include "gerente.h"
#include "globals.h"
#include "exibicao.h"
#include <pthread.h>
#include <unistd.h>
#include <ncurses.h>

void* gerenciar_pedidos(void* arg) {
    while (1) {
        pthread_mutex_lock(&pedido_mutex);

        if (tempo_expirado() || pedidos_restantes == 0 || pedidos_atendidos >= NUMERO_TOTAL_DE_PEDIDOS) {
            pthread_mutex_unlock(&pedido_mutex);
            break;
        }

        exibir_informacoes(); // Update the display after each check

        pthread_mutex_unlock(&pedido_mutex);
        usleep(500000);
    }

    finalizar_exibicao(); // Finalize the display at the end of the game
    return NULL;
}
