# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -g 
EXEC = voeheap

# Regra principal que será chamada ao rodar apenas 'make'
all: $(EXEC)

# Linkagem do executável
$(EXEC): main.o VoeHeap.o
	$(CC) $(CFLAGS) -o $(EXEC) main.o VoeHeap.o

# Compilação do main
main.o: main.c VoeHeap.h
	$(CC) $(CFLAGS) -c main.c

# Compilação do TAD Heap
VoeHeap.o: VoeHeap.c VoeHeap.h
	$(CC) $(CFLAGS) -c VoeHeap.c

# Limpeza dos arquivos gerados
clean:
	rm -f *.o $(EXEC)

# Regra para compilar e rodar o projeto rapidamente
run: $(EXEC)
	./$(EXEC)

# Regra auxiliar para análise de memória
valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC)