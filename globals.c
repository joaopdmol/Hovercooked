#include "globals.h"
#include <pthread.h>
#include <time.h>

int bancadas_disponiveis = 2;
int cozinhas_disponiveis = 2;
int pedidos_atendidos = 1;
int pedidos_restantes = NUMERO_TOTAL_DE_PEDIDOS;
time_t tempo_inicio_jogo;
pthread_mutex_t pedido_mutex = PTHREAD_MUTEX_INITIALIZER;
CozinheiroStatus cozinheiro_status[NUM_COZINHEIROS] = {{0, 0, 0}, {0, 0, 0}};

bool tempo_expirado() {
    return difftime(time(NULL), tempo_inicio_jogo) >= TEMPO_TOTAL_DE_JOGO;
}
