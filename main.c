#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cozinheiro.h"
#include "gerente.h"
#include "pedido.h"
#include "globals.h"
#include "exibicao.h"



int main() {
    srand(time(NULL));
    tempo_inicio_jogo = time(NULL);

    pthread_t threads_cozinheiros[NUM_COZINHEIROS];
    pthread_t thread_gerente;

    bancadas_disponiveis = 2;
    cozinhas_disponiveis = 2;

    inicializar_exibicao(); // Initialize ncurses

    // Inicializa pedidos
    for (int i = 1; i <= NUMERO_TOTAL_DE_PEDIDOS; i++) {
        adicionar_pedido(i, rand() % 5 + 1, rand() % 5 + 1);
    }

    // Cria threads para cozinheiros
    for (int i = 0; i < NUM_COZINHEIROS; i++) {
        pthread_create(&threads_cozinheiros[i], NULL, cozinheiro, (void *)(long)i);
    }

    // Cria thread para gerente
    pthread_create(&thread_gerente, NULL, gerenciar_pedidos, NULL);

    // Aguarda término das threads
    for (int i = 0; i < NUM_COZINHEIROS; i++) {
        pthread_join(threads_cozinheiros[i], NULL);
    }
    pthread_join(thread_gerente, NULL);

    finalizar_exibicao(); // Finalize ncurses

    return 0;
}
