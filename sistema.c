#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
char nome[50];
float preco;
int quantidade;
int id;
}Produto;

void limpabuffer(){
    int c; 
    while((c = getchar()) != '\n');
}

int salvaarquivo(Produto *produtos, int capacidade){
FILE *arquivo = fopen("produtos.txt", "w");
if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return 1;
}
for(int i = 0; i < capacidade; i++){
    fprintf(arquivo, "%s,%.2f,%d,%d\n", produtos[i].nome, produtos[i].preco, produtos[i].quantidade, produtos[i].id);
    }
fclose(arquivo);
return 0;
}

Produto* carregarArquivo(int *totalPtr){
    FILE *arquivo = fopen("produtos.txt", "r"); 

    if (arquivo == NULL) {
       *totalPtr = 0;
        return NULL;
    }

    int capacidadeAtual = 5;      
    int total = 0;                
    Produto *produtos = malloc(sizeof(Produto) * capacidadeAtual);
    if (produtos == NULL) {
        printf("Erro ao alocar memória!\n");
        *totalPtr = 0;
        return NULL;
    }
    Produto temp; 
    while (fscanf(arquivo, "%49[^,],%f,%d,%d\n", temp.nome, &temp.preco, &temp.quantidade, &temp.id) == 4) {
        if (total == capacidadeAtual) {
            capacidadeAtual = capacidadeAtual * 2;  
            Produto *novoPonteiro = realloc(produtos, sizeof(Produto) * capacidadeAtual);

            if (novoPonteiro == NULL) {
                printf("Erro ao expandir memória!\n");
                fclose(arquivo);
                *totalPtr = total;  
                return produtos;    
            }
            produtos = novoPonteiro;  
        }
        produtos[total] = temp;  
                total++;                 
    }
    fclose(arquivo);
    *totalPtr = total;  
    return produtos;     
}

Produto* cadastrarProduto(Produto *produtos, int *totalPtr){
    int n;
    printf("Quantos produtos novos para cadastrar? \n");
    scanf("%d", &n);
    int capacidade = *totalPtr + n;

    Produto *novoPonteiro = realloc(produtos, sizeof(Produto) * capacidade);
    if (novoPonteiro == NULL) {
        printf("Erro ao expandir memória!\n");
        return produtos;
    }
    produtos = novoPonteiro;
    limpabuffer();

    for(int i = *totalPtr; i < capacidade; i++){
        printf("Nome: \n");
        fgets(produtos[i].nome, 50, stdin);
        produtos[i].nome[strcspn(produtos[i].nome, "\n")] = '\0';
        printf("Preço: \n");
        scanf("%f", &produtos[i].preco);
        printf("Quantidade: \n");
        scanf("%d", &produtos[i].quantidade);
        printf("ID: \n");
        scanf("%d", &produtos[i].id);
        limpabuffer();
    }

    *totalPtr = capacidade;

    return produtos;
}

void listarProdutos(Produto *produtos, int total){
    for(int i = 0; i < total; i++){
        printf("Nome: %s\n", produtos[i].nome);
        printf("ID: %d\n", produtos[i].id);
        printf("Preço: %.2f\n", produtos[i].preco);
        printf("Unidades: %d\n", produtos[i].quantidade);
    }
}

void buscarPorId(Produto *produtos, int total){
    int idBuscado;
    int encontrado;  

    do {
        printf("Digite o ID do produto que deseja buscar: \n");
        scanf("%d", &idBuscado);
        limpabuffer();

        encontrado = 0; 

        for(int i = 0; i < total; i++){
            if(produtos[i].id == idBuscado){
                printf("Produto encontrado!\n");
                printf("Nome: %s\n", produtos[i].nome);
                printf("Preço: %.2f\n", produtos[i].preco);
                printf("Unidades: %d\n", produtos[i].quantidade);
                encontrado = 1;
                break;   
            }
        }

        if (!encontrado) {
            printf("Produto com esse ID não encontrado. Tente novamente.\n");
        }

    } while (!encontrado);
}

int main(){
    int total = 0;
    Produto *produtos = carregarArquivo(&total);

    int opcao;
    do {
        printf("\n--- MENU ---\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Buscar por ID\n");
        printf("3 - Listar produtos\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: \n");
        scanf("%d", &opcao);
        limpabuffer();

        switch(opcao){
            case 1:
                produtos = cadastrarProduto(produtos, &total);
                break;
            case 2:
                buscarPorId(produtos, total);
                break;
            case 3:
                listarProdutos(produtos, total);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 4);

    int resultado = salvaarquivo(produtos, total);
    if (resultado != 0) {
        printf("Algo deu errado ao salvar!\n");
    }

    return 0;
}