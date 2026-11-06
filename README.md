# VoeHeap: Embarque Aéreo com Prioridade

Trabalho Prático da disciplina **CI1056 - Algoritmos e Estruturas de Dados II** (2026/2) — Bacharelado em Ciência da Computação (UFPR).
**Prof.** Elias P. Duarte Jr.

## Autores
* **Pedro Valesi**
* **Nicolas Lazzarin**

## Sobre o Projeto
Implementação do Tipo Abstrato de Dados (TAD) **Max-Heap** em vetor dinâmico para o gerenciamento de filas de prioridade de embarque aéreo da companhia *VoeHeap*, acompanhado de análise experimental comparativa entre os algoritmos de ordenação **HeapSort**, **QuickSort (Mediana de 3)** e **InsertSort** para N = 1024 elementos.

## Como Compilar e Executar
* **Compilar o projeto:** `make`
* **Compilar e executar:** `make run`
* **Verificar memória (Valgrind):** `make valgrind`
* **Limpar binários:** `make clean`

## Estrutura do Repositório
* `main.c`, `VoeHeap.c`, `VoeHeap.h`, `makefile`: Código-fonte do sistema e script de compilação.
* `web/`: Relatório técnico em HTML (`index.html`), logs de testes (`logs.txt`) e listagens do código-fonte em formato `.txt`.
