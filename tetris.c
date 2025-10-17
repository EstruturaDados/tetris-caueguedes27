#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5  // Tamanho fixo da fila

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// Estrutura que representa a fila circular
typedef struct {
    Peca pecas[TAM_FILA];
    int frente;  // Índice do primeiro elemento
    int tras;    // Índice do último elemento
    int qtd;     // Quantidade de peças na fila
} Fila;

// Inicializa a fila vazia
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->qtd = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *fila) {
    return fila->qtd == TAM_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->qtd == 0;
}

// Gera automaticamente uma nova peça com tipo aleatório
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4]; // Escolhe tipo aleatoriamente
    nova.id = id;
    return nova;
}

// Insere uma peça no final da fila (enqueue)
void inserirPeca(Fila *fila, Peca p) {
    if (filaCheia(fila)) {
        printf("\n⚠️ A fila está cheia! Não é possível adicionar uma nova peça.\n");
        return;
    }
    fila->tras = (fila->tras + 1) % TAM_FILA;
    fila->pecas[fila->tras] = p;
    fila->qtd++;
    printf("\n✅ Peça [%c %d] adicionada ao final da fila.\n", p.nome, p.id);
}

// Remove a peça da frente da fila (dequeue)
void jogarPeca(Fila *fila) {
    if (filaVazia(fila)) {
        printf("\n⚠️ A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca p = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % TAM_FILA;
    fila->qtd--;
    printf("\n🎮 Peça [%c %d] jogada (removida da fila).\n", p.nome, p.id);
}

// Exibe o estado atual da fila
void exibirFila(Fila *fila) {
    if (filaVazia(fila)) {
        printf("\nA fila está vazia.\n");
        return;
    }

    printf("\n🧱 Fila atual de peças:\n");
    for (int i = 0; i < fila->qtd; i++) {
        int idx = (fila->frente + i) % TAM_FILA;
        printf("[%c %d] ", fila->pecas[idx].nome, fila->pecas[idx].id);
    }
    printf("\n");
}

// Função principal
int main() {
    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL));

    int idAtual = 0;
    int opcao;

    // Inicializa a fila com 5 peças automáticas
    for (int i = 0; i < TAM_FILA; i++) {
        inserirPeca(&fila, gerarPeca(idAtual++));
    }

    // Menu interativo
    do {
        exibirFila(&fila);
        printf("\n===== MENU TETRIS STACK =====\n");
        printf("1 - Jogar (remover) a peça da frente\n");
        printf("2 - Inserir nova peça automaticamente\n");
        printf("3 - Visualizar fila atual\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila, gerarPeca(idAtual++));
                break;
            case 3:
                exibirFila(&fila);
                break;
            case 4:
                printf("\n👋 Encerrando o programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
