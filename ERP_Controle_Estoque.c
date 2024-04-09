#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void inicializarLista(LISTA *lista){
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

int buscarProduto(LISTA *lista){
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
    return 0;
}
void removerproduto(LISTA *lista){
     int pos = buscarProduto(lista);
    if(pos>=0){
        for(int i = pos; i < lista->qtde - 1; i++){
            lista->registros[i] = lista->registros[i+1];
        }
        printf("item  removido!");
        lista->qtde--;
    }
}

void listarProdutos(LISTA *lista){
    
    printf("----------------------------------\n");
    for(int i = 0; i < lista->qtde; i++){
        printf("ProdutoID: %d\n", lista->registros[i].idProduto);
        printf("Nome Produto: %s\n", lista->registros[i].nomeProduto);
        printf("Quantidade Produto: %d\n", lista->registros[i].quantidadeProduto);
        printf("----------------------------------\n");
    }
}

void salvar_dados(LISTA *lista){
    char *nome_temp[20];
    int id_temp;
    int qntd_temp;
    FILE *arquivo = fopen("arquivo.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para escrita.\n");
    }
    if(lista->qtde > 0){
        for(int i = 0; i < lista->qtde; i++){
            *nome_temp = NULL;
            *nome_temp = lista->registros[i].nomeProduto;
            id_temp = lista->registros[i].idProduto;
            qntd_temp = lista->registros[i].quantidadeProduto;
            fprintf(arquivo, "%05d \n%s \n%03d \n",id_temp, *nome_temp, qntd_temp);
            printf("%d salvo com sucesso\n");
        }
        fclose(arquivo);
    }else{
        printf("A lista esta vazia!\n");
    }

}

void buscar_arquivo(LISTA *lista){
    FILE *arquivo = fopen("arquivo.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    while (lista->qtde < TAM && fscanf(arquivo, "%d", &lista->registros[lista->qtde].idProduto) != EOF) {
        fscanf(arquivo, "%s", lista->registros[lista->qtde].nomeProduto);
        fscanf(arquivo, "%d", &lista->registros[lista->qtde].quantidadeProduto);
        lista->qtde++;
    }

    fclose(arquivo);
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
            removerproduto(&lista);
                // Implementar exclusão de produto
                break;
            case 5:
                listarProdutos(&lista);
                break;
            case 6:
                // Implementar ordenação dos produtos
                break;
            case 7:
                buscar_arquivo(&lista);
                break;
            case 8:
                salvar_dados(&lista);
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

    inicializarLista(&lista);
    menuAcoes(lista);

    return 0;
}