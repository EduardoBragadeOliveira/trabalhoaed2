#include <stdio.h>
#include <stdlib.h>
#define TAM 10

typedef struct{
    char nomeProduto[20];
    int idProduto;
    int quantidadeProduto;
} REGISTRO;

typedef struct{
    REGISTRO registros[TAM];
    int qtde;
} LISTA;

void inicializarFila(LISTA *lista){
    lista->qtde = 0;
}

void inserirProduto(LISTA *lista) {
    REGISTRO r;

    if(lista->qtde < TAM){
        printf("Digite o nome do produto: ");
        scanf("%s", &r.nomeProduto);

        printf("Digite a quantidade do produto: ");
        scanf("%d", &r.quantidadeProduto);

        r.idProduto = lista->qtde + 1;

        lista->registros[lista->qtde] = r;

        lista->qtde++;

        printf("Produto salvo com o id: %d", r.idProduto);
    }
}

void buscarProduto(LISTA *lista){
    int id, produtoEncontrado = 0;

    printf("Digite o id do produto a ser pesquisado: ");
    scanf("%d", &id);

    for(int i = 0; i < lista->qtde; i++){
        if(lista->registros[i].idProduto == id){
            printf("Produto encontrado!\n");
            printf("Nome do produto: %s\n", lista->registros[i].nomeProduto);
            printf("Quantidade: %d\n", lista->registros[i].quantidadeProduto);
            printf("ID do produto: %d\n", lista->registros[i].idProduto);
            produtoEncontrado = 1;
        }
    }

    if(produtoEncontrado == 0){
        printf("ID do produto invalido!\n");
    }
}

void menuAcoes(LISTA lista){
    int opcao;

    do {
        printf("\n---- Menu ----\n");
        printf("1. Inserir produto\n");
        printf("2. Buscar produto\n");
        printf("3. Atualizar estoque\n");
        printf("4. Excluir produto\n");
        printf("5. Listar estoque\n");
        printf("6. Ordenar estoque\n");
        printf("7. buscar dados\n");
        printf("8. Salvar dados\n");
        printf("9. Sair\n");
        printf("escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirProduto(&lista);
                break;
            case 2:
                buscarProduto(&lista);
                break;
            case 3:
                // Implementar atualização de estoque(mudar algum produto)
                break;
            case 4:
                // Implementar exclusão de produto
                break;
            case 5:
                // Implementar listagem de produtos
                break;
            case 6:
                // Implementar ordenação dos produtos
                break;
            case 7:
                // Implementar busca de dados do arquivo de texto
                break;
            case 8:
                // salvar dados em arquivo de texto
            case 9:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 9);
}

int main() {

    LISTA lista;

    inicializarFila(&lista);
    menuAcoes(lista);

    return 0;
}