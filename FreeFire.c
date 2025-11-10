#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10
#define MAX_COMPONENTES 20

// ============================================================
// ESTRUTURAS DE DADOS
// ============================================================

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ============================================================
// VARIÁVEIS GLOBAIS
// ============================================================
int comparacoesSeq = 0;
int comparacoesBin = 0;

// ============================================================
// ASSINATURAS DAS FUNÇÕES
// ============================================================

// Módulo 1 - Mochila (vetor e lista encadeada)
void menuPrincipal();
void menuVetor();
void menuLista();

void inserirItemVetor(Item mochila[], int *qtd);
void removerItemVetor(Item mochila[], int *qtd);
void listarItensVetor(Item mochila[], int qtd);
int buscarSequencialVetor(Item mochila[], int qtd, char nome[]);
void ordenarVetor(Item mochila[], int qtd);
int buscarBinariaVetor(Item mochila[], int qtd, char nome[]);

void inserirItemLista(No **inicio);
void removerItemLista(No **inicio);
void listarItensLista(No *inicio);
No* buscarItemLista(No *inicio, char nome[]);

// Módulo 2 - Torre de Fuga
void menuTorre();
void cadastrarComponentes(Componente c[], int *n);
void mostrarComponentes(Componente c[], int n);
void bubbleSortNome(Componente c[], int n, int *comparacoes);
void insertionSortTipo(Componente c[], int n, int *comparacoes);
void selectionSortPrioridade(Componente c[], int n, int *comparacoes);
int buscaBinariaPorNome(Componente c[], int n, char nome[], int *comparacoes);
void medirTempo(void (*algoritmo)(Componente[], int, int*), Componente c[], int n);

// ============================================================
// FUNÇÃO PRINCIPAL
// ============================================================
int main() {
    menuPrincipal();
    return 0;
}

// ============================================================
// MENU PRINCIPAL
// ============================================================
void menuPrincipal() {
    int opcao;

    do {
        printf("\n===== SISTEMA DE SOBREVIVÊNCIA =====\n");
        printf("1 - Mochila (vetor)\n");
        printf("2 - Mochila (lista encadeada)\n");
        printf("3 - Torre de Fuga (ordenação e busca)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 3: menuTorre(); break;
            case 0: printf("\nEncerrando o sistema...\n"); break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);
}

// ============================================================
// MÓDULO 1: MOCHILA (VETOR)
// ============================================================
void menuVetor() {
    Item mochila[MAX_ITENS];
    int qtd = 0, opcao;
    char nomeBusca[30];

    do {
        printf("\n====== MOCHILA (VETOR) ======\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: inserirItemVetor(mochila, &qtd); break;
            case 2: removerItemVetor(mochila, &qtd); break;
            case 3: listarItensVetor(mochila, qtd); break;
            case 4:
                printf("Digite o nome do item: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                buscarSequencialVetor(mochila, qtd, nomeBusca);
                break;
            case 0: printf("\nVoltando...\n"); break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);
}

void inserirItemVetor(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }
    Item novo;
    printf("Nome: "); fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: "); fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: "); scanf("%d", &novo.quantidade); getchar();

    mochila[*qtd] = novo;
    (*qtd)++;
    printf("\nItem adicionado!\n");
}

void removerItemVetor(Item mochila[], int *qtd) {
    if (*qtd == 0) { printf("\nMochila vazia!\n"); return; }
    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *qtd - 1; j++) mochila[j] = mochila[j + 1];
            (*qtd)--;
            printf("\nItem removido!\n");
            return;
        }
    }
    printf("\nItem não encontrado!\n");
}

void listarItensVetor(Item mochila[], int qtd) {
    if (qtd == 0) { printf("\nMochila vazia!\n"); return; }
    for (int i = 0; i < qtd; i++)
        printf("%d) %s (%s) x%d\n", i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
}

int buscarSequencialVetor(Item mochila[], int qtd, char nome[]) {
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado: %s (%s) x%d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return i;
        }
    }
    printf("\nItem não encontrado!\n");
    return -1;
}

// ============================================================
// MÓDULO 2: MOCHILA (LISTA ENCADEADA)
// ============================================================
void menuLista() {
    No *inicio = NULL;
    int opcao;
    char nomeBusca[30];

    do {
        printf("\n====== MOCHILA (LISTA) ======\n");
        printf("1 - Inserir item\n2 - Remover item\n3 - Listar itens\n4 - Buscar item\n0 - Voltar\nEscolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: inserirItemLista(&inicio); break;
            case 2: removerItemLista(&inicio); break;
            case 3: listarItensLista(inicio); break;
            case 4:
                printf("Nome do item: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                buscarItemLista(inicio, nomeBusca);
                break;
            case 0: printf("\nVoltando...\n"); break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);
}

void inserirItemLista(No **inicio) {
    No *novo = (No*) malloc(sizeof(No));
    printf("Nome: "); fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: "); fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: "); scanf("%d", &novo->dados.quantidade); getchar();
    novo->proximo = *inicio;
    *inicio = novo;
    printf("\nItem inserido!\n");
}

void removerItemLista(No **inicio) {
    if (*inicio == NULL) { printf("\nLista vazia!\n"); return; }
    char nome[30];
    printf("Nome do item a remover: "); fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    No *atual = *inicio, *anterior = NULL;
    while (atual && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (!atual) { printf("\nItem não encontrado!\n"); return; }
    if (!anterior) *inicio = atual->proximo;
    else anterior->proximo = atual->proximo;
    free(atual);
    printf("\nItem removido!\n");
}

void listarItensLista(No *inicio) {
    if (!inicio) { printf("\nLista vazia!\n"); return; }
    int i = 1;
    while (inicio) {
        printf("%d) %s (%s) x%d\n", i++, inicio->dados.nome, inicio->dados.tipo, inicio->dados.quantidade);
        inicio = inicio->proximo;
    }
}

No* buscarItemLista(No *inicio, char nome[]) {
    while (inicio) {
        if (strcmp(inicio->dados.nome, nome) == 0) {
            printf("\nItem encontrado: %s (%s) x%d\n", inicio->dados.nome, inicio->dados.tipo, inicio->dados.quantidade);
            return inicio;
        }
        inicio = inicio->proximo;
    }
    printf("\nItem não encontrado!\n");
    return NULL;
}

// ============================================================
// MÓDULO 3: TORRE DE FUGA (ORDENAÇÃO E BUSCA)
// ============================================================
void menuTorre() {
    Componente c[MAX_COMPONENTES];
    int n = 0, opcao, comparacoes = 0;
    char chave[30];

    do {
        printf("\n====== TORRE DE FUGA ======\n");
        printf("1 - Cadastrar componentes\n");
        printf("2 - Ordenar por nome (Bubble Sort)\n");
        printf("3 - Ordenar por tipo (Insertion Sort)\n");
        printf("4 - Ordenar por prioridade (Selection Sort)\n");
        printf("5 - Busca binária por nome\n");
        printf("6 - Mostrar componentes\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarComponentes(c, &n); break;
            case 2: medirTempo(bubbleSortNome, c, n); break;
            case 3: medirTempo(insertionSortTipo, c, n); break;
            case 4: medirTempo(selectionSortPrioridade, c, n); break;
            case 5:
                printf("Nome do componente-chave: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';
                comparacoes = 0;
                if (buscaBinariaPorNome(c, n, chave, &comparacoes) != -1)
                    printf("\nComponente encontrado!\n");
                else
                    printf("\nComponente não encontrado!\n");
                printf("Comparações: %d\n", comparacoes);
                break;
            case 6: mostrarComponentes(c, n); break;
            case 0: printf("\nRetornando ao menu principal...\n"); break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);
}

void cadastrarComponentes(Componente c[], int *n) {
    printf("\nQuantos componentes deseja cadastrar (max %d)? ", MAX_COMPONENTES);
    scanf("%d", n); getchar();
    if (*n > MAX_COMPONENTES) *n = MAX_COMPONENTES;

    for (int i = 0; i < *n; i++) {
        printf("\nComponente %d:\n", i+1);
        printf("Nome: "); fgets(c[i].nome, sizeof(c[i].nome), stdin);
        c[i].nome[strcspn(c[i].nome, "\n")] = '\0';
        printf("Tipo: "); fgets(c[i].tipo, sizeof(c[i].tipo), stdin);
        c[i].tipo[strcspn(c[i].tipo, "\n")] = '\0';
        printf("Prioridade (1-10): "); scanf("%d", &c[i].prioridade); getchar();
    }
}

void mostrarComponentes(Componente c[], int n) {
    if (n == 0) { printf("\nNenhum componente cadastrado.\n"); return; }
    printf("\n--- COMPONENTES ---\n");
    for (int i = 0; i < n; i++)
        printf("%d) %s | Tipo: %s | Prioridade: %d\n", i+1, c[i].nome, c[i].tipo, c[i].prioridade);
}

void bubbleSortNome(Componente c[], int n, int *comparacoes) {
    Componente temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            (*comparacoes)++;
            if (strcmp(c[j].nome, c[j+1].nome) > 0) {
                temp = c[j]; c[j] = c[j+1]; c[j+1] = temp;
            }
        }
    }
}

void insertionSortTipo(Componente c[], int n, int *comparacoes) {
    for (int i = 1; i < n; i++) {
        Componente chave = c[i];
        int j = i - 1;
        while (j >= 0 && strcmp(c[j].tipo, chave.tipo) > 0) {
            (*comparacoes)++;
            c[j + 1] = c[j];
            j--;
        }
        c[j + 1] = chave;
    }
}

void selectionSortPrioridade(Componente c[], int n, int *comparacoes) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (c[j].prioridade < c[min].prioridade) min = j;
        }
        if (min != i) {
            Componente temp = c[i]; c[i] = c[min]; c[min] = temp;
        }
    }
}

int buscaBinariaPorNome(Componente c[], int n, char nome[], int *comparacoes) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(c[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

void medirTempo(void (*algoritmo)(Componente[], int, int*), Componente c[], int n) {
    int comparacoes = 0;
    clock_t inicio = clock();
    algoritmo(c, n, &comparacoes);
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nOrdenação concluída!\nComparações: %d\nTempo de execução: %.6f segundos\n", comparacoes, tempo);
}
