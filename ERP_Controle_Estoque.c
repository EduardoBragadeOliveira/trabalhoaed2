#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_ESTOQUE 1000
#define TAM_CATEGORIA 100



typedef struct
{
    int ano;
    int mes;
    int dia;
} DATA;

typedef struct
{
    int idCategoria;
    char nomeCategoria[40];
    float margemLucro;
} CATEGORIA;

typedef struct
{
    CATEGORIA categorias[TAM_CATEGORIA];
    int qtde;
} LISTA_CATEGORIAS;

typedef struct
{
    char nomeProduto[40];
    int idProduto;
    int quantidadeProduto;
    float precoCusto;
    float precoVenda;
    DATA dataValidade;
    CATEGORIA categoria;
} PRODUTO;

typedef struct
{
    PRODUTO produtos[TAM_ESTOQUE];
    int qtde;
} ESTOQUE;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inicializarEstoqueEListaCategorias(ESTOQUE *estoque, LISTA_CATEGORIAS *listaCategorias)
{
    estoque->qtde = 0;
    listaCategorias->qtde = 0;
}

void inserirProduto(ESTOQUE *estoque, LISTA_CATEGORIAS *listaCategorias)
{
    PRODUTO produto;
    CATEGORIA categoriaPadrao = {0, "Sem_Categoria", 0};
    int posCategoria, opcao;

    if (estoque->qtde < TAM_ESTOQUE)
    {
        fflush(stdin);
        printf("Digite o nome do produto: ");
        fflush(stdin);
        scanf("%s", produto.nomeProduto);

        printf("Digite a quantidade do produto: ");
        scanf("%d", &produto.quantidadeProduto);

        printf("Digite o preco de custo: R$ ");
        scanf("%f", &produto.precoCusto);

        printf("Digite o dia validade (somente numeros): ");
        scanf("%d", &produto.dataValidade.dia);

        printf("Digite o mes validade (somente numeros): ");
        scanf("%d", &produto.dataValidade.mes);

        printf("Digite o ano validade (somente numeros): ");
        scanf("%d", &produto.dataValidade.ano);

        if (listaCategorias->qtde > 0)
        {
            printf("Encontramos %d categoria(s)\n", listaCategorias->qtde);
            printf("1. Listar e escolher categoria\n");
            printf("2. Criar categoria nova\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            if (opcao == 1)
            {
                listarCategorias(listaCategorias);

                do
                {
                    posCategoria = buscarCategoria(listaCategorias, 2);
                } while (posCategoria == -1);
            }
            else if (opcao == 2)
            {
                posCategoria = inserirCategoria(listaCategorias);
            }

            produto.categoria = listaCategorias->categorias[posCategoria];
        }
        else
        {
            printf("Nao encontramos categorias \n");
            printf("Deseja criar uma categoria? \n");
            printf("1. Sim\n");
            printf("2. Nao, quero deixar sem categoria\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            if (opcao == 1)
            {
                posCategoria = inserirCategoria(listaCategorias);
                produto.categoria = listaCategorias->categorias[posCategoria];
            }
            else if (opcao == 2)
            {
                produto.categoria = categoriaPadrao;
            }
        }

        produto.precoVenda = produto.precoCusto + (produto.precoCusto * (produto.categoria.margemLucro / 100));

        produto.idProduto = estoque->qtde + 1;

        estoque->produtos[estoque->qtde] = produto;

        estoque->qtde++;

        printf("Produto salvo com o id: %d", produto.idProduto);
    }
}

int inserirCategoria(LISTA_CATEGORIAS *listaCategorias)
{
    CATEGORIA categoria;

    if (listaCategorias->qtde < TAM_CATEGORIA)
    {
        fflush(stdin);
        printf("Digite o nome da categoria: ");
        fflush(stdin);
        scanf("%s", categoria.nomeCategoria);

        printf("Digite a margem de lucro na categoria: ");
        scanf("%f", &categoria.margemLucro);

        categoria.idCategoria = listaCategorias->qtde + 1;

        listaCategorias->categorias[listaCategorias->qtde] = categoria;

        listaCategorias->qtde++;

        printf("Categoria salva com o id: %d\n", categoria.idCategoria);

        return listaCategorias->qtde - 1;
    }
}

int buscarProduto(ESTOQUE *estoque)
{
    int id;

    printf("Digite o id do produto a ser buscado: ");
    scanf("%d", &id);

    for (int i = 0; i < estoque->qtde; i++)
    {
        if (estoque->produtos[i].idProduto == id)
        {
            printf("Produto encontrado!\n");
            printf("----------------------------------\n");
            printf("Nome do produto: %s", estoque->produtos[i].nomeProduto);
            printf("Quantidade: %d\n", estoque->produtos[i].quantidadeProduto);
            printf("ID do produto: %d\n", estoque->produtos[i].idProduto);
            printf("----------------------------------\n");
            return i;
        }
    }

    printf("ID do produto invalido!\n");
    return -1;
}

int buscarCategoria(LISTA_CATEGORIAS *listaCategorias, int tipoBusca)
{
    int id;

    if (tipoBusca == 1)
    {
        printf("Digite o id da categoria a ser buscada: ");
    }
    else if (tipoBusca == 2)
    {
        printf("Digite o id da categoria a ser escolhida: ");
    }

    scanf("%d", &id);

    for (int i = 0; i < listaCategorias->qtde; i++)
    {
        if (listaCategorias->categorias[i].idCategoria == id)
        {
            if (tipoBusca == 1)
            {
                printf("Categoria encontrada encontrado!\n");
                printf("----------------------------------\n");
                printf("Categoria ID: %d\n", listaCategorias->categorias[i].idCategoria);
                printf("Nome Categoria: %s", listaCategorias->categorias[i].nomeCategoria);
                printf("Porcentagem Extra: %.2f%%\n", listaCategorias->categorias[i].margemLucro);
                printf("----------------------------------\n");
            }
            return i;
        }
    }

    printf("ID da categoria invalido!\n");
    return -1;
}
void atualizarProduto(ESTOQUE *estoque, LISTA_CATEGORIAS *listaCategorias)
{
    int opcao, posCategoria;

    if(estoque->qtde > 0){
        int posProduto = buscarProduto(estoque);

        printf("Deseja atualizar o nome?\n");
        printf("1. Sim\n");
        printf("2. Nao\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            getchar();
            printf("Digite o novo nome do produto: ");
            fgets(estoque->produtos[posProduto].nomeProduto, sizeof(estoque->produtos[posProduto].nomeProduto), stdin);
        }

        printf("Deseja atualizar a quantidade?\n");
        printf("1. Sim\n");
        printf("2. Nao\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            printf("Digite a nova quantidade do produto: ");
            scanf("%d", &estoque->produtos[posProduto].quantidadeProduto);
        }

        printf("Deseja atualizar o preco de custo?\n");
        printf("1. Sim\n");
        printf("2. Nao\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            printf("Digite o novo preco de custo: R$ ");
            scanf("%f", &estoque->produtos[posProduto].precoCusto);
        }

        printf("Deseja atualizar a data de validade?\n");
        printf("1. Sim\n");
        printf("2. Nao\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            printf("Digite o novo dia validade (somente numeros): ");
            scanf("%d", &estoque->produtos[posProduto].dataValidade.dia);

            printf("Digite o novo mes validade (somente numeros): ");
            scanf("%d", &estoque->produtos[posProduto].dataValidade.mes);

            printf("Digite o novo ano validade (somente numeros): ");
            scanf("%d", &estoque->produtos[posProduto].dataValidade.ano);
        }

        printf("Deseja atualizar a categoria?\n");
        printf("1. Sim\n");
        printf("2. Nao\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            printf("Encontramos %d categoria(s)\n", listaCategorias->qtde);
            printf("1. Listar e escolher categoria\n");
            printf("2. Criar categoria nova\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            if (opcao == 1)
            {
                listarCategorias(listaCategorias);

                do
                {
                    posCategoria = buscarCategoria(listaCategorias, 2);
                } while (posCategoria == -1);
            }
            else if (opcao == 2)
            {
                posCategoria = inserirCategoria(listaCategorias);
            }

            estoque->produtos[posProduto].categoria = listaCategorias->categorias[posCategoria];
        }

        estoque->produtos[posProduto].precoVenda = estoque->produtos[posProduto].precoCusto + (estoque->produtos[posProduto].precoCusto * (estoque->produtos[posProduto].categoria.margemLucro / 100));

        printf("Produto %d atualizado com sucesso!\n", estoque->produtos[posProduto].idProduto);
    }
}

void atualizarCategoria(LISTA_CATEGORIAS *listaCategorias, ESTOQUE *estoque){
    int opcao, posCategoria;

    if(listaCategorias->qtde > 0){
        posCategoria = buscarCategoria(listaCategorias, 1);

        printf("Deseja atualizar o nome?\n");
        printf("1. Sim\n");
        printf("2. Nao\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            getchar();
            printf("Digite o novo nome da categoria: ");
            fgets(listaCategorias->categorias[posCategoria].nomeCategoria, sizeof(listaCategorias->categorias[posCategoria].nomeCategoria), stdin);
        }

        printf("Deseja atualizar a margem de lucro?\n");
        printf("1. Sim\n");
        printf("2. Nao\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            getchar();
            printf("Digite a nova margem de lucro da categoria: ");
            scanf("%f", &listaCategorias->categorias[posCategoria].margemLucro);
        }

        for (int i = 0; i < estoque->qtde; i++)
        {
            if(estoque->produtos[i].categoria.idCategoria == listaCategorias->categorias[posCategoria].idCategoria){
                estoque->produtos[i].categoria = listaCategorias->categorias[posCategoria];
                estoque->produtos[i].precoVenda = estoque->produtos[i].precoCusto + (estoque->produtos[i].precoCusto * (listaCategorias->categorias[posCategoria].margemLucro / 100));
            }
        }
        
    }
}

void removerProduto(ESTOQUE *estoque)
{
    int pos = buscarProduto(estoque);
    if (pos >= 0)
    {
        for (int i = pos; i < estoque->qtde - 1; i++)
        {
            estoque->produtos[i] = estoque->produtos[i + 1];
        }
        printf("Produto removido!");
        estoque->qtde--;
    }
}
void removerCategoria(LISTA_CATEGORIAS *listaCategorias, ESTOQUE *estoque)
{
    int pos = buscarCategoria(listaCategorias, 1);
    CATEGORIA categoriaPadrao = {0, "Sem Categoria", 0};
    if (pos >= 0)
    {
        if (estoque->qtde > 0)
        {
            for (int i = 0; i < estoque->qtde; i++)
            {
                if (estoque->produtos[i].categoria.idCategoria == listaCategorias->categorias[pos].idCategoria)
                {
                    estoque->produtos[i].categoria = categoriaPadrao;
                }
            }
        }

        for (int i = pos; i < listaCategorias->qtde - 1; i++)
        {
            listaCategorias->categorias[i] = listaCategorias->categorias[i + 1];
        }
        printf("Categoria removida!");
        listaCategorias->qtde--;
    }
}
void listarProdutos(ESTOQUE *estoque)
{
    int mesValidade, diaValidade, anoValidade;

    if (estoque->qtde > 0)
    {
        printf("----------------------------------\n");
        for (int i = 0; i < estoque->qtde; i++)
        {
            diaValidade = estoque->produtos[i].dataValidade.dia;
            mesValidade = estoque->produtos[i].dataValidade.mes;
            anoValidade = estoque->produtos[i].dataValidade.ano;

            printf("Produto ID: %d\n", estoque->produtos[i].idProduto);
            printf("Nome Produto: %s\n", estoque->produtos[i].nomeProduto);
            printf("Quantidade Produto: %d\n", estoque->produtos[i].quantidadeProduto);
            printf("Preco de custo: R$ %.2f\n", estoque->produtos[i].precoCusto);
            printf("Preco de venda: R$ %.2f\n", estoque->produtos[i].precoVenda);
            printf("Data de validade: %d/%d/%d\n", diaValidade, mesValidade, anoValidade);
            printf("Categoria: %s\n", estoque->produtos[i].categoria.nomeCategoria);
            printf("----------------------------------\n");
        }
    }
    else
    {
        printf("Nao ha produtos no estoque!\n");
    }
}

void listarCategorias(LISTA_CATEGORIAS *listaCategorias)
{
    if (listaCategorias->qtde > 0)
    {
        printf("----------------------------------\n");
        for (int i = 0; i < listaCategorias->qtde; i++)
        {
            printf("Categoria ID: %d\n", listaCategorias->categorias[i].idCategoria);
            printf("Nome Categoria: %s\n", listaCategorias->categorias[i].nomeCategoria);
            printf("Porcentagem Extra: %.2f%%\n", listaCategorias->categorias[i].margemLucro);
            printf("----------------------------------\n");
        }
    }
    else
    {
        printf("Nao ha categorias criadas!\n");
    }
}

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particao(int vet[], int inicio, int fim, int ordenacao){
    int pivo = vet[(inicio + fim)/2];
    int a = inicio-1;
    int b = fim+1;

    if(ordenacao == 1){ //crescente
        while(a<b){
            do{
                a++;
            } while(vet[a] < pivo);
            do{
                b--;
            } while(vet[b] > pivo);
            if(a<b) trocar(&vet[a], &vet[b]);
        }
    }
    else if(ordenacao == 2){ //descrescente
        while(a<b){
            do{
                a++;
            } while(vet[a] > pivo); 
            do{
                b--;
            } while(vet[b] < pivo); 
            if(a<b) trocar(&vet[a], &vet[b]);
        }
    }
    return b;
}

    void quickSort(int vet[], int inicio, int fim, int ordenacao){
        if(inicio<fim){
            int meio = particao(vet,inicio,fim, ordenacao);
            quickSort(vet,inicio,meio, ordenacao);
            quickSort(vet,meio+1,fim, ordenacao);
        }
    }

    void ordenarProdutoQtde(ESTOQUE *estoque){
        int op;
        printf("entre com:\n(1) para ordenar crescente\n(2) para ordenar decrescente\n");
        scanf("%d", &op);

        if(op == 1){
            printf("Ordenando quantidade de forma crescente . . .\n");

            int quantidades[TAM_ESTOQUE];

            for (int i = 0; i < estoque->qtde; i++) {
                quantidades[i] = estoque->produtos[i].quantidadeProduto;
            }
            quickSort(quantidades, 0, estoque->qtde - 1, op);
        
            for (int i = 0; i < estoque->qtde; i++){
                for (int j = 0; j < estoque->qtde; j++) {
                    if (estoque->produtos[j].quantidadeProduto == quantidades[i]) {
                        printf("Nome Produto: %s\n", estoque->produtos[j].nomeProduto);
                        printf("Quantidade Produto: %d\n", estoque->produtos[j].quantidadeProduto);
                        printf("Produto ID: %d\n", estoque->produtos[j].idProduto);
                        printf("Categoria: %s\n", estoque->produtos[j].categoria.nomeCategoria);
                        printf("----------------------------------\n");
                        break;
                    }
                }
            }
        }
        else if(op==2){
            printf("Ordenando quantidade de forma decrescente . . .\n");
            
            int quantidades[TAM_ESTOQUE];

            for (int i = 0; i < estoque->qtde; i++) {
                quantidades[i] = estoque->produtos[i].quantidadeProduto;
            }
            quickSort(quantidades, 0, estoque->qtde - 1, op);
        
            for (int i = 0; i < estoque->qtde; i++){
                for (int j = 0; j < estoque->qtde; j++) {
                    if (estoque->produtos[j].quantidadeProduto == quantidades[i]) {
                        printf("Nome Produto: %s\n", estoque->produtos[j].nomeProduto);
                        printf("Quantidade Produto: %d\n", estoque->produtos[j].quantidadeProduto);
                        printf("Produto ID: %d\n", estoque->produtos[j].idProduto);
                        printf("Categoria: %s\n", estoque->produtos[j].categoria.nomeCategoria);
                        printf("----------------------------------\n");
                        break;
                    }
                }
            }   
        }
    }

    void trocarFloat(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
    }

    float particaoFloat(float vet[], int inicio, int fim, int ordenacao) {
        float pivo = vet[(inicio + fim) / 2];
        int a = inicio - 1;
        int b = fim + 1;

        if (ordenacao == 1) { // crescente
            while (a < b) {
                do {
                    a++;
                } while (vet[a] < pivo);
                do {
                    b--;
                } while (vet[b] > pivo);
                if (a < b) trocarFloat(&vet[a], &vet[b]);
            }
        } else if (ordenacao == 2) { // decrescente
            while (a < b) {
                do {
                    a++;
                } while (vet[a] > pivo);
                do {
                    b--;
                } while (vet[b] < pivo);
                if (a < b) trocarFloat(&vet[a], &vet[b]);
            }
        }
        return b;
    }

    void quickSortFloat(float vet[], int inicio, int fim, int ordenacao) {
    if (inicio < fim) {
        int meio = particaoFloat(vet, inicio, fim, ordenacao);
        quickSortFloat(vet, inicio, meio, ordenacao);
        quickSortFloat(vet, meio + 1, fim, ordenacao);
    }
}

void ordenarPrecoVenda(ESTOQUE *estoque){
    int op;
    float precos[TAM_ESTOQUE];
    printf("entre com:\n(1) para ordenar crescente\n(2) para ordenar decrescente\n");
    scanf("%d", &op);

    if (op == 1){
        printf("Ordenando preco de venda de forma crescente . . .\n");

        for (int i = 0; i < estoque->qtde; i++) {
            precos[i] = estoque->produtos[i].precoVenda;
        }
        quickSortFloat(precos, 0, estoque->qtde - 1, op);
    
        for (int i = 0; i < estoque->qtde; i++){
            for (int j = 0; j < estoque->qtde; j++) {
                if (estoque->produtos[j].precoVenda == precos[i]) {
                    printf("Nome Produto: %s\n", estoque->produtos[j].nomeProduto);
                    printf("Preco de venda: R$ %.2f\n", estoque->produtos[j].precoVenda); 
                    printf("Preco de custo: R$ %.2f\n", estoque->produtos[j].precoCusto); 
                    printf("Produto ID: %d\n", estoque->produtos[j].idProduto); 
                    printf("Categoria: %s\n", estoque->produtos[j].categoria.nomeCategoria); 
                    printf("----------------------------------\n");
                    break;
                }
            }
        }
    }
    else if(op==2){
        printf("Ordenando preco de venda de forma decrescente . . .\n");
        
        for (int i = 0; i < estoque->qtde; i++) {
            precos[i] = estoque->produtos[i].precoVenda;
        }
        quickSortFloat(precos, 0, estoque->qtde - 1, op);
    
        for (int i = 0; i < estoque->qtde; i++){
            for (int j = 0; j < estoque->qtde; j++) {
                if (estoque->produtos[j].precoVenda == precos[i]) {
                    printf("Nome Produto: %s\n", estoque->produtos[j].nomeProduto); 
                    printf("Preco de venda: R$ %.2f\n", estoque->produtos[j].precoVenda);
                    printf("Preco de custo: R$ %.2f\n", estoque->produtos[j].precoCusto); 
                    printf("Produto ID: %d\n", estoque->produtos[j].idProduto); 
                    printf("Categoria: %s\n", estoque->produtos[j].categoria.nomeCategoria);
                    printf("----------------------------------\n");
                    break;
                }
            }
        }   
    }
}

void salvarTabelaProdutos(ESTOQUE *estoque)
{
    char *TEMP_nomeProduto[20];
    int TEMP_idProduto;
    int TEMP_quantidadeProduto;
    float TEMP_precoCusto;
    float TEMP_precoVenda;
    int TEMP_ano;
    int TEMP_mes;
    int TEMP_dia;
    int TEMP_idCategoria;
    char *TEMP_nomeCategoria[20];

    FILE *arquivo = fopen("arquivoProdutos.txt", "w");
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo para escrita.\n");
    }
    if (estoque->qtde > 0)
    {
        for (int i = 0; i < estoque->qtde; i++)
        {   
            *TEMP_nomeProduto = NULL;
            *TEMP_nomeCategoria = NULL;
            *TEMP_nomeProduto = estoque->produtos[i].nomeProduto;
            TEMP_idProduto = estoque->produtos[i].idProduto;
            TEMP_quantidadeProduto = estoque->produtos[i].quantidadeProduto;
            TEMP_precoCusto = estoque->produtos[i].precoCusto;
            TEMP_precoVenda = estoque->produtos[i].precoVenda;
            TEMP_ano = estoque->produtos[i].dataValidade.ano;
            TEMP_mes = estoque->produtos[i].dataValidade.mes;
            TEMP_dia = estoque->produtos[i].dataValidade.dia;
            *TEMP_nomeCategoria = estoque->produtos[i].categoria.nomeCategoria;
            fprintf(arquivo, "%s\n%05d \n%03d \n", *TEMP_nomeProduto, TEMP_idProduto, TEMP_quantidadeProduto);
            fprintf(arquivo, "%.2f \n%.2f \n", TEMP_precoCusto, TEMP_precoVenda);
            fprintf(arquivo, "%02d\n%02d\n%04d \n%s\n", TEMP_dia, TEMP_mes, TEMP_ano, *TEMP_nomeCategoria);
        }
        printf("Relacao salva com sucesso!\n");
        fclose(arquivo);
    }
    else
    {
        printf("O estoque esta vazio!\n");
    }
}
 
void salvarTabelaCategorias(LISTA_CATEGORIAS *lista_categorias)
{
    char *TEMP_nomeCategoria[20];
    float TEMP_margemLucro;
    int TEMP_idCategoria;

    FILE *arquivo = fopen("arquivoCategorias.txt", "w");
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo para escrita.\n");
    }
    if (lista_categorias->qtde > 0)
    {
        for (int i = 0; i < lista_categorias->qtde; i++)
        {   
            *TEMP_nomeCategoria = NULL;
            *TEMP_nomeCategoria = lista_categorias->categorias[i].nomeCategoria;
            TEMP_margemLucro = lista_categorias->categorias[i].margemLucro;
            TEMP_idCategoria = lista_categorias->categorias[i].idCategoria;
            fprintf(arquivo, "%s\n%.2f \n%05d \n", *TEMP_nomeCategoria, TEMP_margemLucro, TEMP_idCategoria);  
        }
        printf("Relacao salva com sucesso!\n");
        fclose(arquivo);
    }
    else
    {
        printf("Nao ha categorias cadastradas!\n");
    }
}

void buscarTabelaProdutos(ESTOQUE *estoque)
{
    FILE *arquivo = fopen("arquivoProdutos.txt", "r");
    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo da relacao de estoque.\n");
        return;
    }

    while (estoque->qtde < TAM_ESTOQUE && fscanf(arquivo, "%d", &estoque->produtos[estoque->qtde].idProduto) != EOF)
    {
        fscanf(arquivo, "%s", estoque->produtos[estoque->qtde].nomeProduto);
        fscanf(arquivo, "%d", &estoque->produtos[estoque->qtde].idProduto);
        fscanf(arquivo, "%d", &estoque->produtos[estoque->qtde].quantidadeProduto);
        fscanf(arquivo, "%f", &estoque->produtos[estoque->qtde].precoCusto);
        fscanf(arquivo, "%f", &estoque->produtos[estoque->qtde].precoVenda);
        fscanf(arquivo, "%d", &estoque->produtos[estoque->qtde].dataValidade.dia);
        fscanf(arquivo, "%d", &estoque->produtos[estoque->qtde].dataValidade.mes);
        fscanf(arquivo, "%d", &estoque->produtos[estoque->qtde].dataValidade.ano);
        fscanf(arquivo, "%d", &estoque->produtos[estoque->qtde].categoria.idCategoria);
        fscanf(arquivo, "%s", &estoque->produtos[estoque->qtde].categoria.nomeCategoria);

        estoque->qtde++;
    }

    fclose(arquivo);
}

void buscarTabelaCategorias(LISTA_CATEGORIAS *categorias)
{
    FILE *arquivo = fopen("arquivoCategorias.txt", "r");
    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo da relacao de estoque.\n");
        return;
    }

    while (categorias->qtde < TAM_ESTOQUE && fscanf(arquivo, "%d", &categorias->categorias[categorias->qtde].idCategoria) != EOF)
    {
        fscanf(arquivo, "%s", categorias->categorias[categorias->qtde].nomeCategoria);
        fscanf(arquivo, "%f", &categorias->categorias[categorias->qtde].margemLucro);
        fscanf(arquivo, "%d", &categorias->categorias[categorias->qtde].idCategoria);
        

        categorias->qtde++;
    }

    fclose(arquivo);
}

void menuAcoes(ESTOQUE estoque, LISTA_CATEGORIAS listaCategorias)
{
    int opcao;

    do
    {
        printf("\n============================== Menu ==============================\n");
        printf("1. ========================== Inserir no estoque\n");
        printf("2. =========================== Buscar no estoque\n");
        printf("3. =========================== Atualizar estoque\n");
        printf("4. ============================= Remover estoque\n");
        printf("5. ============================== Listar estoque\n");
        printf("6. ============================= Ordenar estoque\n");
        printf("7. ============================== Buscar estoque\n");
        printf("8. ============================== Salvar estoque\n");
        printf("9. ======================================== Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("1. Inserir produto\n");
            printf("2. Inserir categoria\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            if (opcao == 1)
            {
                inserirProduto(&estoque, &listaCategorias);
            }
            else if (opcao == 2)
            {
                inserirCategoria(&listaCategorias);
            }

            break;
        case 2:
            printf("1. Buscar produto\n");
            printf("2. Buscar categoria\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            if (opcao == 1)
            {
                buscarProduto(&estoque);
            }
            else if (opcao == 2)
            {
                buscarCategoria(&listaCategorias, 1);
            }

            break;
        case 3:
            printf("1. Atualizar produto\n");
            printf("2. Atualizar categoria\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            if (opcao == 1)
            {
                atualizarProduto(&estoque, &listaCategorias);
            }
            else if (opcao == 2)
            {
                atualizarCategoria(&listaCategorias, &estoque);
            }
            break;
        case 4:
            printf("1. Remover produto\n");
            printf("2. Remover categoria\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            if (opcao == 1)
            {
                removerProduto(&estoque);
            }
            else if (opcao == 2)
            {
                removerCategoria(&listaCategorias, &estoque);
            }
            break;
        case 5:
            printf("1. Listar produtos\n");
            printf("2. Listar categorias\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            if (opcao == 1)
            {
                listarProdutos(&estoque);
            }
            else if (opcao == 2)
            {
                listarCategorias(&listaCategorias);
            }

            break;
        case 6:
           do{
                printf("1. para ordenar por preco de venda\n2. para ordenar por quantidade \n");
                scanf("%d", &opcao);
                    if(opcao == 1){
                        ordenarPrecoVenda(&estoque);
                    }
                    else if(opcao == 2){
                        ordenarProdutoQtde(&estoque);
                    }
                }while((opcao>2) || (opcao<1));
            break;
        case 7:
            printf("Buscando dados...\n");
            buscarTabelaCategorias(&listaCategorias);
            buscarTabelaProdutos(&estoque);
        case 8:
            printf("Salvando dados...\n");
            salvarTabelaProdutos(&estoque);
            salvarTabelaCategorias(&listaCategorias);
            break;
        case 9:
            printf("Fazendo Backup...\n");
            salvarTabelaProdutos(&estoque);
            salvarTabelaCategorias(&listaCategorias);
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 9);
}

int main()
{
    ESTOQUE estoque;
    LISTA_CATEGORIAS listaCategorias;
    printf("\n");
    printf("------------------------------------\n");
    printf("Buscando Banco de Dados!\n");
    printf("------------------------------------\n");

    inicializarEstoqueEListaCategorias(&estoque, &listaCategorias);
    buscarTabelaCategorias(&listaCategorias);
    buscarTabelaProdutos(&estoque);
    menuAcoes(estoque, listaCategorias);

    return 0;
}