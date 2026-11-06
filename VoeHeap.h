#ifndef VOEHEAP_H
#define VOEHEAP_H

/*Estrutura "opaca" que representa
os dados dos passageiros, ou seja, nome e prioridade*/
typedef struct passenger passenger;

/*Estrutura "opaca" que representa o TAD heap (vetor dinâmico)*/
typedef struct heap heap;

/* Inicialização e Limpeza*/
heap *InicHeap(int max_capacity);
void destroiheap(heap *h);

/* Operações principais do TAD heap */
int insereheap(heap *h, const char *name, int priority);

/* Retorna 1 se removeu com sucesso, retornando os dados por referência
os parâmetros*/
int removeheap(heap *h, char *removed_name, int *removed_priority);

void imprimeheap(heap *h);

// Verifica a propriedade do heap
int checaheap(heap *h);

/* Manutenção e Ordenação */
void heapfy(heap *h, int index, int *comp_count, int *swaps);
void heapsort(heap *h, int *comp_count, int *swaps);

/* Algoritmos de ordenação adicionais*/

void quicksort(heap *h, int left, int right, int *comp_count, int *swaps);
void insertsort(heap *h, int *comp_count, int *swaps);

#endif