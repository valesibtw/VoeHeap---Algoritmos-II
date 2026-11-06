#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VoeHeap.h"

typedef struct passenger
{
    char name[50];
    int priority;
} passenger;

typedef struct heap
{
    passenger *vetor;
    int current_size;
    int max_capacity;
} heap;

heap *InicHeap(int max_capacity)
{
    /*Aloca dinâmicamente o TAD Heap*/
    heap *h = (heap *)malloc(sizeof(heap));
    if (h == NULL)
        return NULL; /*FALHA*/

    /*Aloca o vetor de passageiros com a capacidade informada*/
    h->vetor = (passenger *)calloc(max_capacity , sizeof(passenger));
    if (h->vetor == NULL)
    {
        free(h);
        return NULL; /*FALHA*/
    }
    h->current_size = 0;
    h->max_capacity = max_capacity;

    return h;
}
/*A main deve se certifiacar que (heap *h) não é NULL*/
void destroiheap(heap *h)
{
    if (h != NULL)
    {
        if (h->vetor != NULL)
            free(h->vetor);
    }
    free(h);
}

void sift_up(heap *h)
{
    int i = h->current_size;
    while (i > 0 && h->vetor[i].priority > h->vetor[(i - 1) / 2].priority)
    {
        int pai = (i - 1) / 2;
        /*Troca os passageiros de lugar(swap da struct inteira)*/
        passenger temp = h->vetor[i];
        h->vetor[i] = h->vetor[pai];
        h->vetor[pai] = temp;
        /*Atualiza o índice do nó pai e continua o laço*/
        i = pai;
    }
}

int insereheap(heap *h, const char *name, int priority)
{
    if (h != NULL)
    {
        if (h->vetor != NULL)
        {
            if (h->current_size == h->max_capacity)
                return 0; /*Avião está lotado */

            h->vetor[h->current_size].priority = priority;
            strcpy(h->vetor[h->current_size].name, name);
            sift_up(h);

            /* Só depois da reorganização é que incrementamos o tamanho total*/
            h->current_size++;
        }
        return 1; /*sucesso*/
    }
    else
        return 0; /*h é inválido*/
}

int checaheap(heap *h) //cumpre as propriedades de max heap?
{
    if (h == NULL || h->vetor == NULL)
        return 0; // checa se eh nulo, se for retorna 0

    // Verifica a propriedade de Max Heap
    for (int i = 0; i <= (h->current_size - 2) / 2; i++) //percorre apenas os nos q possuem filhos
    {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;

        if (esq < h->current_size && h->vetor[i].priority < h->vetor[esq].priority)
            return 0; // Violaram propriedade do Heap
        if (dir < h->current_size && h->vetor[i].priority < h->vetor[dir].priority)
            return 0; // Violou propriedade
    }
    return 1; // eh um heap válido
}

void imprimeheap(heap *h) // permitir a qualquer momento a impressao dos passageiros que ainda devem ser embarcados
{
    if (h == NULL || h ->current_size == 0) {
        printf("\n[AVISO] O Heap esta vazio!\n"); // aviso
        return;
    }
    printf("\n=====================================\n");
    printf("     PASSAGEIROS NO HEAP (EMBARQUE)     \n");
    printf("\n=====================================\n");
    for (int i = 0; i < h->current_size; i++)
    {
        printf("[%d] Passageiros: %-20s | Prioridade: %d\n", i, h->vetor[i].name, h ->vetor[i].priority);
    }
        printf("=====================================\n");
}

void heapfy(heap*h, int index, int *comp_count, int *swaps){ 
    int maior = index;
    int esq = 2 * index + 1;
    int dir = 2 * index + 2;

    //Compara com o filho esquerdo
    if (esq < h->current_size){
        (*comp_count)++;
        if (h->vetor[esq].priority > h->vetor[maior].priority){
            maior = esq;
        }     
    }

    // compara com o filho direito
    if (dir < h->current_size){
        (*comp_count)++;
        if (h->vetor[dir].priority > h->vetor[maior].priority){
            maior = dir;
        }
    }

    // se o maior não é o atual, troca e continua o heapfy recursivamente
    if (maior != index) {
        passenger temp = h->vetor[index];
        h->vetor[index] = h->vetor[maior];
        h->vetor[maior] = temp;
        (*swaps)++;

        heapfy(h, maior, comp_count, swaps); // recursao
    }
}

int removeheap (heap *h, char *removed_name, int *removed_priority) //?
{
    if (h == NULL || h ->current_size <= 0)
    return 0; // Heap vazio ou inválido

    //salva o elemento de maior prioridade (raiz)
    strcpy(removed_name, h->vetor[0].name);
    *removed_priority= h ->vetor[0].priority;

    //move o ultimo elemento para a raiz
    h->vetor[0] = h->vetor[h->current_size -1];
    h->current_size--;

    /*imprimir o número de comparações e trocas*/
    int comp = 0, swaps = 0;
    printf(" [Heapfy] Comparacoes: %d | Trocas: %d\n", comp, swaps);
    // Reorganiza o heap a partir da raiz
    heapfy(h, 0, &comp,&swaps);

    return 1; //sucesso
}

void heapsort(heap *h, int *comp_count, int *swaps)
{
    if (h == NULL || h->current_size <= 1) 
        return;

    int tam_original = h->current_size;

    //1. Constroí o Heap inicial (bottom-Up)
    for (int i = (h->current_size/2) -1; i >=0; i --){
        heapfy(h,i,comp_count,swaps);
    }

    //2.extrai os elementos um a um do heap
    for (int i = h->current_size-1; i > 0; i --) {
        //move a raiz atual (maior) para o fim
        passenger temp = h->vetor[0];
        h->vetor[0] = h->vetor[i];
        h->vetor[i] = temp;
        (*swaps)++;

        //reduz temporariamente o tamanho lófico do heap para a ordenação
        h->current_size--;
        heapfy(h,0,comp_count,swaps);
    }

    // restaura o tamanho original do heap após a ordenação
    h->current_size = tam_original;
}

void insertsort (heap *h,int *comp_count,int *swaps){
    if (h == NULL || h->vetor == NULL || h->current_size <= 1) return;
    int n = h->current_size;
    passenger *vet = h ->vetor; // usa o vetor interno diretamente

    for (int i = 0; i < n; i++)
    {
        passenger chave = vet[i];
        int j = i - 1;

        while (j >=0){
            (*comp_count)++;
            if (vet[j].priority> chave.priority){
                vet[j+1]= vet[j];
                (*swaps)++;
                j--;
                } else {
                    break;
                }
            }
            vet [j+1] = chave;
        }
    }

int mediana_de_tres(passenger *vet, int left, int right, int *comp_count){
    int mid = left + (right-left) / 2;
    int a = left, b = mid, c = right;
    
    (*comp_count)++;
    if (vet[a].priority > vet[b].priority){int temp = a; a = b; b = temp;}
    (*comp_count)++;
    if (vet[a].priority > vet[c].priority){int temp = a; a = c; c = temp;}
    (*comp_count)++;
    if (vet[b].priority > vet[c].priority){int temp = b; b = c; c = temp;}

    return b;
}
    
void quicksort_rec(passenger *vet, int left, int right, int *comp_count, int *swaps)
{
    if (left < right) {
        int indice_pivo = mediana_de_tres(vet, left, right, comp_count);
        passenger pivo = vet[indice_pivo];

        vet[indice_pivo] = vet[right];
        vet[right] = pivo;
        (*swaps)++;

        int i = left - 1;
        for (int j = left; j < right; j++) {
            (*comp_count)++;
            if (vet[j].priority <= pivo.priority) {
                i++;
                passenger temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;
                (*swaps)++;
            }
        }
        passenger temp = vet[i + 1];
        vet[i + 1] = vet[right];
        vet[right] = temp;
        (*swaps)++;

        int pivo_idx = i + 1;

        quicksort_rec(vet, left, pivo_idx - 1, comp_count, swaps);
        quicksort_rec(vet, pivo_idx + 1, right, comp_count, swaps);
    }
}

// Implementação exigida pelo VoeHeap.h
void quicksort(heap *h, int left, int right, int *comp_count, int *swaps)
{
    if (h == NULL || h->vetor == NULL) return;
    quicksort_rec(h->vetor, left, right, comp_count, swaps);
}

