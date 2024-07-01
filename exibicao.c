#include "exibicao.h"
#include <ncurses.h>
#include "globals.h"

void inicializar_exibicao() {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    clear();
    refresh();
}

void finalizar_exibicao() {
    endwin();
}

void exibir_informacoes() {
    clear(); // Clear the screen before printing new information
    mvprintw(0, 0, "Estado Atual:");
    mvprintw(1, 0, "--------------");
    mvprintw(2, 0, "Bancadas disponíveis: %d", bancadas_disponiveis);
    mvprintw(3, 0, "Cozinhas disponíveis: %d", cozinhas_disponiveis);
    mvprintw(4, 0, "Pedidos atendidos: %d", pedidos_atendidos);
    mvprintw(5, 0, "Pedidos restantes: %d", pedidos_restantes);

    for (int i = 0; i < NUM_COZINHEIROS; i++) {
        if (cozinheiro_status[i].ocupado) {
            mvprintw(6 + i, 0, "\nCozinheiro %d %s pedido %d",
                     i,
                     cozinheiro_status[i].cozinhando ? "\ncozinhando" : "\npreparando",
                     cozinheiro_status[i].pedido_id);
        } else {
            mvprintw(6 + i, 0, "\nCozinheiro %d aguardando", i);
        }
    }

    refresh();
}

void atualizar_exibicao() {
    exibir_informacoes();
}
