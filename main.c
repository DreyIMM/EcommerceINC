#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Varivaveis Globais

int i, c, qtd_lojas, qtd_prod, active_loja, active_prod, escolha_loja, cod_pro_compra, 
respProd, posicaoProd, qtd, total, add_prod, totaL, tmc, cod_remover = -1, totalC = 0, removerOK = 0;
float totalItens, valorFinal;


// Struct
struct carrinho{  
    char nomePC[100];
    int codProd,qtdComprada;
    float totalItens, totalIten; 
}carrinho[4];

struct cadastro_loja{
    char nomeLoja[100], cnpj[100], ramo[100];
    int cod_loja;
}loja;

struct cadastro_produto{
    char nome[100], titulo[100];
    int categoria, qtdProduto, cod_p, qtd_min;
    float preco;
}produto[4];

// Funções Menus
int menu_vendedor(){
    int menu = 0;
    printf("\n--------------Menu Vendedor------------ \n\n");
    if (active_loja){
         printf("2 - Exibir lojas \n");
         if (active_prod){
            printf("3 - Novo produto \n");
            printf("4 - Exibir produto \n");    
         }else{
             printf("3 - Cadastrar produto");
         }
    }else{
         printf("1 - Cadastrar uma loja \n");
         printf("5 - Sair \n");
    }
    printf("\nDigite..: ");
    scanf("%d", &menu);
    printf("\n_______________________________________________\n\n");
    return menu;
}

int menu_comprador(){
    int menu = 0;
    printf("\n--------------- Comprador -------------- \n");
    printf("\n1- Comprar produto");
    if(tmc>0){
        printf("\n2- Visualizar Carrinho");
        printf("\n3- Remover produto");
        printf("\n4- Finalizar compra");
    }
    printf("\n5- Sair");
    printf("\nSelecione..:");
    scanf("%d", &menu);
    printf("\n_______________________________________________\n\n");
    return menu;
}

int menu_inicial(){
    int menu = 0;
    printf("\n-------------Menu Principal------------ \n\n");
    printf("1 - Entre como Vendedor \n");
    printf("2 - Entre como Comprador \n");
    printf("3 - Sair \n\n");
    printf("Digite..: ");
    scanf("%d", &menu);
    printf("\n\n");
    return menu;
}

// Funções void
void categorias(){
    printf("\n___________ Categorias ___________");
    printf("\n1- Internet das coisas");
    printf("\n2- Inteligencia Artificial");
    printf("\n3- Manufatura Aditiva");
    printf("\n4- Computacao em nuvem");
   
}

void cadastrar_loja(){
        active_loja = 1;
        printf("---------Cadastrando Loja--------- \n");
        printf("\nDigite o nome da loja:..:");
        fflush(stdin);
        gets(loja.nomeLoja);
        printf("Digite o CNPJ da loja..:");
        fflush(stdin);
        gets(loja.cnpj);
        printf("Digite o segmento da empresa..:");
        gets(loja.ramo); 
}

void exibir_loja(){
    printf("------------ Dados da loja cadastrada--------------- \n");
        printf("\nNome da loja: %s", loja.nomeLoja);
        printf("\t\tcnpj da loja: %s", loja.cnpj);
        printf("\t\tCodigo da loja: %i ",loja.cod_loja);
        printf("\tRamo: %s", loja.ramo);
        printf("\n\n------------------------------------------\n");
}

void cadastrar_produto(){
   active_prod = 1;
   printf("---------Cadastrando produto--------- \n");
   printf("\nQuantos produtos deseja criar ?");
   scanf("%i" ,&qtd_prod);
   totaL = totaL + qtd_prod;
   fflush(stdin);
   for (i = total; i < totaL; i++){
       int p = 1;
       printf("\nNome do produto..:");
       fgets(produto[i].nome, 100, stdin);
       printf("\nTitulo do anuncio..:");
       fgets(produto[i].titulo, 100, stdin);
       categorias();
       printf("\n\nSelecione uma categoria..:");
       scanf("%i",&produto[i].categoria);
       printf("\nDigite o valor..:");
       scanf("%f" ,&produto[i].preco);
       fflush(stdin);
       printf("\nDigite a quantidade em estoque..:");
       scanf("%i",&produto[i].qtdProduto);
       printf("\nQuantidade minima necessaria em estoque..:");
       scanf("%i", &produto[i].qtd_min);
       fflush(stdin);
       produto[i].cod_p = produto[i].cod_p + i;
   }
   total = total + i;
}

void exibir_produto(){
    printf("------------Lista de Produtos--------------- \n");
    for (i = 0; i < totaL; i++){
        printf("produto: %s", produto[i].nome);
        printf("\n\nTitulo: %s", produto[i].titulo);
        printf("Categoria: %i \n",produto[i].categoria);
        printf("Preco..: %.2f\n",produto[i].preco);
        printf("Quantidade do estoque: %i\n",produto[i].qtdProduto);
        printf("Nome da empresa: %s\n", loja.nomeLoja);
        printf("Codigo do produto: %i\n",produto[i].cod_p); 
        printf("\n\n_______________________________________________\n");
    }
}

int local;

void ProdutoCarrinho(int cpc){
    for (i = 0; i < totaL; i++)
    {
        if (cpc == produto[i].cod_p)
        {
            respProd = 1;    // econtrou o produto
            posicaoProd = i; // Posição (índice) onde está o codigo do produto
        }
    }
    if (respProd == 1)
    {
        printf("Quantidade..: ");
        scanf("%d", &qtd);
        if (produto[posicaoProd].qtdProduto >= qtd && produto[posicaoProd].qtdProduto != 0)
        {
            tmc++;
            // atualiza o estoque
            produto[posicaoProd].qtdProduto = produto[posicaoProd].qtdProduto - qtd;
            totalItens = produto[posicaoProd].preco * qtd;

            for (c = totalC; c < tmc; c++)
            {
                carrinho[c].totalIten = produto[posicaoProd].preco;
                carrinho[c].qtdComprada = qtd;
                carrinho[c].codProd = cpc;
                carrinho[c].totalItens = totalItens;
            }
            totalC = totalC + 1;
            valorFinal = valorFinal + totalItens;
            // exibir valor do produto
            printf("\n___________ Produto adcionado ao Carrinho ___________");
            printf("\n\nProduto..: %i", cpc);
            printf("\nQuantidade..: %i", qtd);
            printf("\nValor Total do item..: %.2f", totalItens);
        }
        else
        {
            printf("Quantidade indisponivel");
        }
        respProd = 0;
    }else{ 

        printf("\n _________Produto nao disponivel_________\n");
    }
}

void remover(){
    listarCarrinho();
    printf("\n\t\t Retirar produto do carrinho");
    printf("\nCodigo:");
    scanf("%i" ,&cod_remover);

    for (i = 0; i < totalC; i++)
    {
        if (cod_remover == carrinho[i].codProd)
        {
            local = i;
            removerOK = 1;
        }
    }
    if (removerOK){
        carrinho[local].codProd = 0;
        valorFinal =   valorFinal - carrinho[local].totalItens;
        carrinho[local].totalItens = 0;
        carrinho[local].qtdComprada = 0;
    }else
    {
        valorFinal = valorFinal + totalItens;
        printf("\nCodigo para remover Invalido");
    }
}

void listarCarrinho(){
    printf("\n\n_________Produtos no Carrinho_________");
    for (i =0; i < totalC; i++){
        printf("\nCodigo produto: %i", carrinho[i].codProd);
        printf("\nQuantidade: %i ", carrinho[i].qtdComprada);
        printf("\nValor Unitario: %.2f", carrinho[i].totalIten);
        printf("\nValor: %.2f", carrinho[i].totalItens);
        printf("\n______________________________________\n");
    }
}

void finalizarCompra(){
    printf("\nCompra finalizada");
    printf("\nTotal: %.2f" ,valorFinal);
}

int main(){
    menu_inicial:
        switch (menu_inicial()){
        menu_vendedor:
        case 1:
            switch (menu_vendedor()){
            case 1:
                // Função que cadastra novas lojas e, em seguida, as exibe
                cadastrar_loja();
                goto menu_vendedor;
                break;
            case 2:
                // Função que exibe lojas cadastradas
                exibir_loja();
                goto menu_vendedor;
                break;
            case 3:
                // Função que cadastra produtos
                cadastrar_produto();
                goto menu_inicial;
                break;
            case 4:
                exibir_produto();
                goto menu_inicial;
                break;
            default:
                goto menu_inicial;
                break;
            }
        case 2:
        menu_comprador:
            switch (menu_comprador()){
            case 1:
                categoria:
                do{
                categorias();
                int opP;
                printf("\n\nSelecione..:");
                scanf("%i", &opP);
                if (opP == 1){
                    printf("\n\n - - - -  Lista de produtos Internet das coisas - - - - -\n");
                }else if (opP == 2){
                    printf("\n\n - - - -  Lista de produtos Inteligencia Artificial - - - - -\n");
                }else if (opP == 3){
                    printf("\n\n - - - -  Lista de produtos Sistemas Ciber-fisicos - - - - -\n");
                }else if (opP == 4){
                    printf("\n\n - - - -  Lista de produtos Equipamentos para escritorio - - - - -\n");
                }else{
                    printf("\n Categoria invalida\n");
                    goto categoria;
                }
                for (i = 0; i < totaL; i++){
                    if (produto[i].categoria == opP){
                        printf("\nNome do produto: %s", produto[i].nome);
                        printf("Titulo do produto: %s", produto[i].titulo);
                        printf("Nome da empresa: %s", loja.nomeLoja);
                        printf("\nValor do produto:  %.2f",produto[i].preco);
                        printf("\nEstoque: %i", produto[i].qtdProduto);
                        printf("\nCodigo do produto: %i", produto[i].cod_p);
                        printf("\n_______________________________________________\n");
                    }
                }
                printf("\nInsira o codigo do produto..:");
                scanf("%i", &cod_pro_compra);
                ProdutoCarrinho(cod_pro_compra);
                printf("\n\nDeseja adcionar um novo produto\n1-sim 2-nao:");
                scanf("%i",&add_prod);
                }while(add_prod == 1);
                goto menu_comprador;
                break;
            case 2:
                listarCarrinho();
                printf("Total: %.2f",valorFinal);
                goto menu_comprador;
                break;
            case 3:
                remover();
                goto menu_comprador;
                break;
            case 4:
                finalizarCompra();
                goto menu_comprador;
                break;
            case 5:
                goto menu_inicial;
                break;
            }
            break;
        default:
            break;
        }
    system("pause");
    return 0;
}