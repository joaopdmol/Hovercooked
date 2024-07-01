#ifndef GLOBALS_H
#define GLOBALS_H

#include <pthread.h>
#include <time.h>
#include<stdbool.h>

#define NUMERO_TOTAL_DE_PEDIDOS 15
#define TEMPO_TOTAL_DE_JOGO 60
#define NUM_COZINHEIROS 2

typedef struct CozinheiroStatus {
    int ocupado;
    int cozinhando;
    int pedido_id;
} CozinheiroStatus;

extern int bancadas_disponiveis;
extern int cozinhas_disponiveis;
extern int pedidos_atendidos;
extern int pedidos_restantes;
extern time_t tempo_inicio_jogo;
extern pthread_mutex_t pedido_mutex;
extern CozinheiroStatus cozinheiro_status[];

bool tempo_expirado();

#endif // GLOBALS_H
