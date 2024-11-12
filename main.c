#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    char descricao[100];
    int quantidade;
    float preco;
    char categoria[30];
} Item;


void criarRegistro(Item **itens, int *tamanho);
void listarRegistros(Item *itens, int tamanho);
void buscarRegistro(Item *itens, int tamanho);
void editarRegistro(Item *itens, int tamanho);
void deletarRegistro(Item **itens, int *tamanho);
void salvarDados(Item *itens, int tamanho);
void carregarDados(Item **itens, int *tamanho);

int main() {
    Item *itens = NULL;
    int tamanho = 0;
    int opcao;

    carregarDados(&itens, &tamanho);

    do {
        printf("\nMENU:\n");
        printf("1. Criar Registro\n");
        printf("2. Listar Registros\n");
        printf("3. Buscar Registro\n");
        printf("4. Editar Registro\n");
        printf("5. Deletar Registro\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                criarRegistro(&itens, &tamanho);
                salvarDados(itens, tamanho);
                break;
            case 2:
                listarRegistros(itens, tamanho);
                break;
            case 3:
                buscarRegistro(itens, tamanho);
                break;
            case 4:
                editarRegistro(itens, tamanho);
                salvarDados(itens, tamanho);
                break;
            case 5:
                deletarRegistro(&itens, &tamanho);
                salvarDados(itens, tamanho);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    free(itens);
    return 0;
}

void criarRegistro(Item **itens, int *tamanho) {
    (*tamanho)++;
    *itens = realloc(*itens, (*tamanho) * sizeof(Item));

    printf("ID: ");
    scanf("%d", &(*itens)[*tamanho - 1].id);
    printf("Nome: ");
    scanf(" %[^\n]", (*itens)[*tamanho - 1].nome);
    printf("Descricao: ");
    scanf(" %[^\n]", (*itens)[*tamanho - 1].descricao);
    printf("Quantidade: ");
    scanf("%d", &(*itens)[*tamanho - 1].quantidade);
    printf("Preco: ");
    scanf("%f", &(*itens)[*tamanho - 1].preco);
    printf("Categoria: ");
    scanf(" %[^\n]", (*itens)[*tamanho - 1].categoria);

    printf("Registro criado com sucesso!\n");
}

void listarRegistros(Item *itens, int tamanho) {
    if (tamanho == 0) {
        printf("Nenhum registro encontrado.\n");
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        printf("\nID: %d\nNome: %s\nDescricao: %s\nQuantidade: %d\nPreco: %.2f\nCategoria: %s\n",
            itens[i].id, itens[i].nome, itens[i].descricao, itens[i].quantidade, itens[i].preco, itens[i].categoria);
    }
}

void buscarRegistro(Item *itens, int tamanho) {
    int id;
    printf("Digite o ID do item que deseja buscar: ");
    scanf("%d", &id);

    for (int i = 0; i < tamanho; i++) {
        if (itens[i].id == id) {
            printf("\nID: %d\nNome: %s\nDescricao: %s\nQuantidade: %d\nPreco: %.2f\nCategoria: %s\n",
                itens[i].id, itens[i].nome, itens[i].descricao, itens[i].quantidade, itens[i].preco, itens[i].categoria);
            return;
        }
    }
    printf("Registro com ID %d nao encontrado.\n", id);
}

void editarRegistro(Item *itens, int tamanho) {
    int id;
    printf("Digite o ID do item que deseja editar: ");
    scanf("%d", &id);

    for (int i = 0; i < tamanho; i++) {
        if (itens[i].id == id) {
            printf("Novo nome: ");
            scanf(" %[^\n]", itens[i].nome);
            printf("Nova descricao: ");
            scanf(" %[^\n]", itens[i].descricao);
            printf("Nova quantidade: ");
            scanf("%d", &itens[i].quantidade);
            printf("Novo preco: ");
            scanf("%f", &itens[i].preco);
            printf("Nova categoria: ");
            scanf(" %[^\n]", itens[i].categoria);
            printf("Registro editado com sucesso!\n");
            return;
        }
    }
    printf("Registro com ID %d nao encontrado.\n", id);
}

void deletarRegistro(Item **itens, int *tamanho) {
    int id;
    printf("Digite o ID do item que deseja deletar: ");
    scanf("%d", &id);

    for (int i = 0; i < *tamanho; i++) {
        if ((*itens)[i].id == id) {
            for (int j = i; j < *tamanho - 1; j++) {
                (*itens)[j] = (*itens)[j + 1];
            }
            (*tamanho)--;
            *itens = realloc(*itens, (*tamanho) * sizeof(Item));
            printf("Registro deletado com sucesso!\n");
            return;
        }
    }
    printf("Registro com ID %d nao encontrado.\n", id);
}

void salvarDados(Item *itens, int tamanho) {
    FILE *arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar os dados.\n");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d\n%s\n%s\n%d\n%.2f\n%s\n",
            itens[i].id, itens[i].nome, itens[i].descricao, itens[i].quantidade, itens[i].preco, itens[i].categoria);
    }
    fclose(arquivo);
}

void carregarDados(Item **itens, int *tamanho) {
    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        return;
    }

    Item temp;
    while (fscanf(arquivo, "%d\n%49[^\n]\n%99[^\n]\n%d\n%f\n%29[^\n]\n",
            &temp.id, temp.nome, temp.descricao, &temp.quantidade, &temp.preco, temp.categoria) != EOF) {
        (*tamanho)++;
        *itens = realloc(*itens, (*tamanho) * sizeof(Item));
        (*itens)[*tamanho - 1] = temp;
    }
    fclose(arquivo);
}
