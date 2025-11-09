#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10  // número máximo de itens que cabem na mochila

// Estrutura que representa um item na mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções principais
void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
void buscarItem(Item mochila[], int qtd);

int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0; // controla quantos itens estão cadastrados
    int opcao;

    do {
        printf("\n====== MOCHILA DO JOGADOR ======\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer do teclado

        switch(opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 0:
                printf("\nSaindo do inventário...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}

// -------------------------------------------
// FUNÇÃO: INSERIR ITEM
// -------------------------------------------
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\nNome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove o \n

    printf("Tipo do item (arma, munição, cura, ferramenta...): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("\n✅ Item adicionado com sucesso!\n");
    listarItens(mochila, *qtd);
}

// -------------------------------------------
// FUNÇÃO: REMOVER ITEM
// -------------------------------------------
void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\nA mochila está vazia! Nada para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = 0;

    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            // Move os itens seguintes uma posição para trás
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtd)--;
            printf("\n🗑️ Item '%s' removido com sucesso!\n", nomeRemover);
            break;
        }
    }

    if (!encontrado)
        printf("\nItem não encontrado na mochila.\n");

    listarItens(mochila, *qtd);
}

// -------------------------------------------
// FUNÇÃO: LISTAR ITENS
// -------------------------------------------
void listarItens(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    printf("\n📦 ITENS NA MOCHILA (%d/%d):\n", qtd, MAX_ITENS);
    printf("---------------------------------\n");
    for (int i = 0; i < qtd; i++) {
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
        printf("---------------------------------\n");
    }
}

// -------------------------------------------
// FUNÇÃO: BUSCAR ITEM (BUSCA SEQUENCIAL)
// -------------------------------------------
void buscarItem(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item para buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n🔎 Item encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\n❌ Item não encontrado na mochila.\n");
}
