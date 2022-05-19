#include <stdio.h>
#include <stdlib.h>
#include "./Lib/util.h"
#include "./Lib/util.c"

#include "./Lib/linkedList.h"
#include "./Lib/linkedList.c"
#include "mainLinkedList.h"
#include "menu.h"
#include "menu.c"

void listarImpressora(No *);
Impressora cadastrarNovaImpressora();
void buscarPorInformacoesDeUmCampoEspecifico(No *);
No* atualizarUmaImpressora(No *);
int removerImpressora();
Impressora *importarDadosDeUmArquivoNoFormatoCSV(No *, char *);
void exportarDadosParaUmArquivoNoFormatoCSV(No *, char *);

int main()
{
    const int N_MENU = 10; // Número de elementos do menu
    char *menu[] = {
        "[0] Listar impressoras",
        "[1] Cadastrar uma nova impressora",
        "[2] Buscar por informacoes de um campo especifico",
        "[3] Atualizar dados impressora",
        "[4] Remover impressora",
        "[5] Limpar lista",
        "[6] Importar dados de um arquivo no formato CSV",
        "[7] Exportar dados para um arquivo no formato CSV",
        "[L] Limpar a tela",
        "[X] Sair do programa"
    };
    char opcao;
    No *removido, *lista = NULL;
    Impressora impressora;
    int posicaoNoVetor;
    
    do
    {
        opcao = exibirMenu(menu, N_MENU);
        switch (opcao)
        {
            case '0':
                listarImpressora(lista);
                break;
            case '1':
                impressora = cadastrarNovaImpressora();
                lista = linkedList_inserirNoFim(lista, impressora);
                if (lista == NULL) 
                    printf("--> ERRO no cadastro de uma nova impressora!\n");
                break;
            case '2':
                if (linkedList_size(lista) > 0)
                    BuscarPorInformacoesDeUmCampoEspecifico(lista); 
                else
                    printf("--> Nenhum registro encontrado, Operacao cancelada!\n");
                break;
            case '3':  
                if (linkedList_size(lista) > 0)
                    lista = atualizarUmaImpressora(lista);
                else
                    printf("--> Nenhum registro encontrado, Operacao cancelada!\n");
                break;
            case '4':
                 if (linkedList_size(lista) > 0){
                   posicaoNoVetor = removerImpressora();
                   linkedList_delete(&lista, posicaoNoVetor);
                   printf("Impressora removida!\n");
                }
                else
                    printf("--> Nenhum registro encontrado, Operacao cancelada!\n");
                break;
            case '5':
                if (linkedList_size(lista) > 0){
                    lista = linkedList_clear(lista);
                    printf("Lista vazia, array limpo!\n");
                }
                else 
                    printf("--> Nenhum registro encontrado, operacao cancelada!\n");
                break; 
            case '6':
                lista = linkedList_clear(lista);
                lista = importarDadosDeUmArquivoNoFormatoCSV(lista, "listaImpressoras.csv");
                if (linkedList_size(lista) == 0)
                    printf("--> Nenhum registro encontrado!\n");
                break;
            case '7':
                if (linkedList_size(lista) > 0)
                    exportarDadosParaUmArquivoNoFormatoCSV(lista, "listaImpressoras.csv");
                else
                    printf("--> Nenhum registro encontrado, Operacao cancelada!\n");
                break;
            case 'L':
                clrscr();
                break;
        }
    } while (opcao != 'X');

    return 0;
}

void listarImpressora(No *lista)
{
    No *p = lista;
    int i = 0;

    if (lista == NULL)
    {
        printf("--> Vetor vazio!\n");
        return;
    }

    printf(" %cndice | %-30s | %-30s | Tipo | Capacidade Mensal\n", 214, "Marca", "Modelo");
    printf("------------------------------------------------------------------------------------------------------\n");
    while (p != NULL)
    {
        printf(" %-6d | %-30s | %-30s | %-4.2c | %-4.1d\n", i, p->info.marca, p->info.modelo, p->info.tipo, p->info.capacidadeMensal);
        p = p->prox;
        i = i + 1;
    }
    printf("\n");
}

Impressora cadastrarNovaImpressora()
{
    Impressora impressora; // Criado na "stack"
    char tipo;
    int capacidadeMes;

    printf("--> Cadastro de um nova impressora\n");

    printf("Marca: ");
    gets(impressora.marca);

    printf("Modelo: ");
    gets(impressora.modelo);

    do
    {
        printf("Tipo: ");
        scanf("%c", &tipo);
        getchar();

    } while (!(tipo == 'T' || tipo == 't' || tipo == 'C' || tipo == 'c'));

    do
    {
        printf("Capacidade Mensal: ");
        scanf("%d", &capacidadeMes);
        getchar();

    } while (capacidadeMes >= 50000 || capacidadeMes <= 0);

    impressora.tipo = tipo;
    impressora.capacidadeMensal = capacidadeMes;

    return impressora;
}

void BuscarPorInformacoesDeUmCampoEspecifico(No *lista){
    const int N_SUBMENU = 6;
    char *sub_menu[] ={
        "[0] Buscar pela marca",
        "[1] Buscar pelo modelo",
        "[2] Buscar pelo tipo",
        "[3] Buscar pela capacidade mensal",
        "[L] Limpar a tela",
        "[X] Sair do sub menu"
    };
    char opcao; 
    char marca[100];
    char modelo[100];
    char tipo;
    int capacidadeMensal, i;


     do
    {
        No *p = lista;
        opcao = exibirMenu(sub_menu, N_SUBMENU);

        switch (opcao)
        {
            case '0':
                i = 0;
                printf("Digite o nome da marca da impressora pelo qual voce quer buscar: ");
                gets(marca);
                
                printf("\n%cndice | %-30s | %-30s | Tipo | Capacidade Mensal\n", 214, "Marca", "Modelo");
                printf("------------------------------------------------------------------------------------------------------\n");
                while (p != NULL)
                {
                    if(strcmp(p->info.marca, marca) == 0){
                        printf("%-6d | %-30s | %-30s | %-4.2c | %-4.1d\n", i, p->info.marca, p->info.modelo, p->info.tipo, p->info.capacidadeMensal);
                        i = i + 1;
                    }   
                    p = p->prox;
                }
                printf("\n");
                break;
            case '1':
                i = 0;
                printf("Digete o nome do modelo de impressora pelo qual voce quer buscar: ");
                gets(modelo);
                
                printf("\n%cndice | %-30s | %-30s | Tipo | Capacidade Mensal\n", 214, "Marca", "Modelo");
                printf("------------------------------------------------------------------------------------------------------\n");
                while (p != NULL)
                {
                    if(strcmp(p->info.modelo, modelo) == 0){
                        printf("%-6d | %-30s | %-30s | %-4.2c | %-4.1d\n", i, p->info.marca, p->info.modelo, p->info.tipo, p->info.capacidadeMensal);
                        i = i + 1;
                    }
                    p = p->prox;
                    
                }
                printf("\n");

                break;
            case '2':
                i = 0;
                printf("Digete o nome do tipo: T(toner) ou C(cartucho) pelo qual voce quer buscar: ");
                scanf("%c", &tipo);
                getchar();
               
                printf("\n%cndice | %-30s | %-30s | Tipo | Capacidade Mensal\n", 214, "Marca", "Modelo");
                printf("------------------------------------------------------------------------------------------------------\n");
                while (p != NULL)
                {
                    if(p->info.tipo == tipo){
                        printf("%-6d | %-30s | %-30s | %-4.2c | %-4.1d\n", i, p->info.marca, p->info.modelo, p->info.tipo, p->info.capacidadeMensal);    
                        i = i + 1;
                    }
                    p = p->prox;
                }
                printf("\n");

                break;
            case '3':
                i = 0;
                printf("Digete a capacidade mensal pelo qual voce deseja buscar: "); 
                scanf("%d", &capacidadeMensal);
                getchar();

                printf("\n%cndice | %-30s | %-30s | Tipo | Capacidade Mensal\n", 214, "Marca", "Modelo");
                printf("------------------------------------------------------------------------------------------------------\n");
                while (p != NULL)
                {
                    if(p->info.capacidadeMensal == capacidadeMensal){
                        printf("%-6d | %-30s | %-30s | %-4.2c | %-4.1d\n", i, p->info.marca, p->info.modelo, p->info.tipo, p->info.capacidadeMensal);
                        i = i + 1;
                    }
                    p = p->prox;
                }
                printf("\n");
                break;
            case 'L':
                clrscr();
                break;
        }
    } while (opcao != 'X');
}

No* atualizarUmaImpressora(No *lista){
    No *p = lista;
    char tipo;
    int  i = 0, index, capacidadeMes;


    printf("Entre com o %cndice da impressora a ser atualizado ou -1 para cancelar a opera%c%co: ", 161, 135, 198);
    scanf("%d", &index);
    getchar();

    while (p != NULL){
        if(i == index){
            printf("\n--> Atualizacao do cadastro da impressora\n\n");

            printf("Marca atual -> %s, digite a nova marca: ", p->info.marca);
            gets(p->info.marca);

            printf("Modelo atual -> %s, digite o novo modelo: ", p->info.modelo);
            gets(p->info.modelo);

            do
            {
                printf("Tipo atual -> %c, digite o novo tipo: ", p->info.tipo);
                scanf("%c", &tipo);
                getchar();

            } while (!(tipo == 'T'  || tipo == 't' || tipo == 'C' || tipo == 'c'));

            do
            {
                printf("Capacidade Mensal -> %d, digite a nova capacidade: ", p->info.capacidadeMensal);
                scanf("%d", &capacidadeMes);
                getchar();
                
            } while (capacidadeMes >= 50000 || capacidadeMes <= 0);

            p->info.tipo = tipo;
            p->info.capacidadeMensal = capacidadeMes;
            
            break;
        }
        else{
            i = i + 1;
            p = p->prox;  
        }
    }

    return p;
}

int removerImpressora()
{
    int index = -1;

    printf("Entre com o %cndice da impressora a ser removido ou -1 para cancelar a opera%c%co: ", 161, 135, 198);
    scanf("%d", &index);
    getchar();

    return index;
}

Impressora *importarDadosDeUmArquivoNoFormatoCSV(No *lista, char *filename){
    FILE *arquivo = NULL;
    Impressora reg;
    char str[200];
    int num_campos;

    // Abre o arquivo para leitura
    if ((arquivo = fopen(filename, "r")) == NULL)
    {
        printf("--> Erro na abertura do arquivo!\n\n");
        return lista;
    }

    printf("--> Importando dados...\n");
    while (!feof(arquivo))
    {
        strcpy(str, "");
        fgets(str, 200, arquivo);
        // Validação da entrada do registro
        num_campos = sscanf(str, "%[^,],%[^,],%c,%d", reg.marca, reg.modelo, &reg.tipo, &reg.capacidadeMensal);
        if (num_campos == 4)
        {
            printf("%s  %s  %c  %d\n", reg.marca, reg.modelo, reg.tipo, reg.capacidadeMensal);
            lista = linkedList_inserirNoFim(lista, reg);
        }
    }
    fclose(arquivo);

    return lista;
}

void exportarDadosParaUmArquivoNoFormatoCSV (No *lista, char *filename)
{
    FILE *arquivo = NULL;
    No *p = lista; 

    // Abre o arquivo para escrita
    if ((arquivo = fopen(filename, "w")) == NULL)
    {
        printf("Erro na abertura do arquivo!\n\n");
        return;
    }

    while (p != NULL)
    {
        fprintf(arquivo, "%s,%s,%c,%d\n", p->info.marca, p->info.modelo, p->info.tipo, p->info.capacidadeMensal);;
        p = p->prox;
    }
    printf("--> Dados exportados...\n");

    fclose(arquivo);
}
