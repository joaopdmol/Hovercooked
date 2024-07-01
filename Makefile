CC = gcc
CFLAGS = -Wall -pthread
LDFLAGS = -lncurses

SRCS = main.c pedido.c cozinheiro.c exibicao.c gerente.c globals.c
OBJS = $(SRCS:.c=.o)

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJS) main
