#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "VoeHeap.h"

#define TAM_MAX 1024

void exibir_menu() {
    printf("\n=======================================================\n");
    printf("         SISTEMA DE EMBARQUE E ORDENACAO VOEHEAP       \n");
    printf("=======================================================\n");
    printf("1. Inicializar Heap (Capacidade maxima do aviao)\n");
    printf("2. Inserir Passageiro\n");
    printf("3. Remover Passageiro (Proximo a embarcar - RemoveHeap)\n");
    printf("4. Imprimir Fila de Embarque (ImprimeHeap)\n");
    printf("5. Checar Integridade do Heap (ChecaHeap)\n");
    printf("6. Executar HeapSort e Imprimir Vetor Ordenado\n");
    printf("7. Comparativo de Desempenho (Heap, Quick, Insertion - 1024 elementos)\n");
    printf("0. Sair\n");
    printf("=======================================================\n");
    printf("Escolha a sua opcao: ");
}    

int main()
{
    /*semeia o gerador de numeros aleatorios usando o relogio do S.O*/
    srand(time(NULL));

    heap *h = NULL;
    int opcao, capacidade;

    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
        printf("\n[ERRO] Entrada invalida. Por favor, introduza um numero.\n"); 
        while(getchar() != '\n'); // Limpa o buffer do teclado
        continue;
        }

        switch (opcao) {

            case 0:{
                if (h != NULL){
                    destroiheap(h);
                    h = NULL;
                }
                printf ("\nEncerrando o sistema VoeHeap...\n");                
                break;
            }

            case 1:
                if (h != NULL) {
                    destroiheap(h);
                }
                printf("Informe a capacidade maxima do aviao (N): ");
                scanf("%d", &capacidade);
                h = InicHeap(capacidade);
                if (h != NULL) {
                    printf("\n[SUCESSO] Heap inicializado com capacidade para %d passageiros!\n", capacidade);
                } else {
                    printf("\n[ERRO] Falha ao alocar memoria para o Heap.\n");
                }
                break;

            case 2: {
                if (h == NULL){
                    printf("\n[AVISO] Inicialize o Heap primeiro (Opcao 1)!\n");
                    break;        
                }
                char nome[50];
                int prioridade;

                printf("Nome do passageiro: ");
                scanf("%s", nome);

                // Opção de gerar prioridade aleatória entre 1 e N ou manual
                printf("Deseja gerar prioridade aleatoria entre 1 e %d? (1-Sim / 2-Nao): ", capacidade);
                int escolha_prio;
                scanf("%d", &escolha_prio);

                if (escolha_prio == 1) {
                    prioridade = (rand() % capacidade) + 1;
                    printf("Prioridade gerada automaticamente: %d\n", prioridade);

                } else {
                    printf("Informe a prioridade (inteiro): ");
                    scanf("%d", &prioridade);

                }

                if (insereheap(h, nome, prioridade)) {
                    printf("\n[SUCESSO] Passageiro '%s' inserido com prioridade %d!\n", nome, prioridade);
                } else {
                    printf("\n[ERRO] Falha na insercao (Aviao lotado ou Heap invalido).\n");
                }
                break;
            }

            case 3: {
                if (h == NULL) {
                    printf("\n[AVISO] Heap nao inicializado.\n");
                    break;
                }
                char nome_removido[50];
                int prio_removida;

                if (removeheap(h, nome_removido, &prio_removida)) {
                    printf("\n========================================\n");
                    printf(" [EMBARQUE REALIZADO COM SUCESSO]       \n");
                    printf(" Passageiro: %s \n", nome_removido);
                    printf(" Prioridade: %d \n", prio_removida);
                    printf("========================================\n");
                } else {
                    printf("\n[AVISO] O Heap esta vazio! Nenhum passageiro para embarcar.\n");
                }
                break;
            }

            case 4:
                imprimeheap(h);
                break;

            case 5:
                if (h == NULL) {
                    printf("\n[AVISO] Heap nao inicializado.\n");
                    break;
                }
                if (checaheap(h)) {
                    printf("\n[OK] O Heap esta integro e satisfaz a propriedade de Max-Heap!\n");
                } else {
                    printf("\n[ALERTA] O Heap violou a propriedade de Max-Heap!\n");
                }
                break;

            case 6: {
                
                /*Nao precisamos verificar se o heap eh valido, pois no heapsort isso ja eh feito.*/

                int comp_count = 0, swaps = 0;
                
                heapsort(h, &comp_count, &swaps);
                
                printf("\n========================================\n");
                printf("          RELATORIO HEAPSORT            \n");
                printf("========================================\n");
                printf(" Comparacoes executadas: %d\n", comp_count);
                printf(" Trocas executadas:      %d\n", swaps);
                printf("========================================\n");
                
                imprimeheap(h);
                break;
            }

            case 7: {
                printf("\n[TESTE] A gerar 1024 passageiros com prioridades aleatorias...\n");

                // Criamos três heaps temporários idênticos para testes justos
                heap *h_heap = InicHeap(TAM_MAX);
                heap *h_quick = InicHeap(TAM_MAX);
                heap *h_insert = InicHeap(TAM_MAX);

                if (!h_heap || !h_quick || !h_insert) {
                    printf("[ERRO] Falha ao alocar memoria para os testes.\n");
                    break;
                }

                // Preenche com os mesmos dados aleatórios
                for (int i = 0; i < TAM_MAX; i++) {
                    char nome_gen[30];
                    sprintf(nome_gen, "Passageiro_%d", i + 1); /*Sprintf guarda o nome na 
                                                                variável nome_gen e não para a tela*/
                    int p = (rand() % TAM_MAX) + 1;
                    
                    insereheap(h_heap, nome_gen, p);
                    insereheap(h_quick, nome_gen, p);
                    insereheap(h_insert, nome_gen, p);
                }
                
                int comp_h = 0, swaps_h = 0;
                int comp_q = 0, swaps_q = 0;
                int comp_i = 0, swaps_i = 0;

                heapsort(h_heap, &comp_h, &swaps_h);
                quicksort (h_quick, 0, TAM_MAX - 1, &comp_q, &swaps_q);
                insertsort (h_insert, &comp_i, &swaps_i);

                /*Imprime a tabela de comparações e trocas.*/
                printf("\n=====================================================================\n");
                printf("       COMPARATIVO DE DESEMPENHO (N = %d ELEMENTOS)                \n", TAM_MAX);
                printf("=====================================================================\n");
                printf("| %-24s | %-18s | %-17s |\n", "Algoritmo", "Comparacoes", "Trocas (Swaps)");
                printf("---------------------------------------------------------------------\n");
                printf("| %-24s | %-18d | %-17d |\n", "HeapSort", comp_h, swaps_h);
                printf("| %-24s | %-18d | %-17d |\n", "QuickSort (Mediana de 3)", comp_q, swaps_q);
                printf("| %-24s | %-18d | %-17d |\n", "InsertSort", comp_i, swaps_i);
                printf("=====================================================================\n");
           
                /*Liberação de Memória dos Heaps.*/

                destroiheap(h_heap);
                destroiheap (h_quick);
                destroiheap (h_insert);
                break;
           
            }



       } 
    } while (opcao != 0);

    return 0;
}