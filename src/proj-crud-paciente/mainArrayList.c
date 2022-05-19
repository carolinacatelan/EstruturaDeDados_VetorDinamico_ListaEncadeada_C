#include <stdio.h>
#include <stdlib.h>
#include "./Lib/util.h"
#include "./Lib/util.c"

#include "./Lib/arrayList.h"
#include "./Lib/arrayList.c"
#include "mainArrayList.h"
#include "menu.h"
#include "menu.c"

void listarImpressora(Impressora *, const int);
Impressora cadastrarNovaImpressora();
void buscarPorInformacoesDeUmCampoEspecifico(Impressora *, const int);
Impressora *atualizarUmaImpressora(Impressora *, int *);
int removerImpressora();
Impressora *importarDadosDeUmArquivoNoFormatoCSV(Impressora *, int *, char *);
void exportarDadosParaUmArquivoNoFormatoCSV(Impressora *, int, char *);

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
    Impressora *v = NULL;
    int n = sizeof(v)/sizeof(v[0]), posicaoNoVetor = 0;
    Impressora impressora;

    do
    {
        opcao = exibirMenu(menu, N_MENU);
        switch (opcao)
        {
            case '0':
                listarImpressora(v, n);
                break;
            case '1':
                impressora = cadastrarNovaImpressora();
                v = array_adicionarNoFim(v, &n, impressora);
                if (v == NULL) 
                    printf("--> ERRO no cadastro de uma nova impressora!\n");
                break;
            case '2':
                if (n > 0){
                    BuscarPorInformacoesDeUmCampoEspecifico(v, n); 
                }
                else
                    printf("--> Nenhum registro encontrado, Operacao cancelada!\n");
                break;
            case '3': 
                if (n > 0){
                    v = atualizarUmaImpressora(v, &n);
                }
                else
                    printf("--> Nenhum registro encontrado, Operacao cancelada!\n");
                break;
            case '4':
                if (n > 0){
                   posicaoNoVetor = removerImpressora();
                   v = array_removerElemento(v, &n, posicaoNoVetor);
                }
                else
                    printf("--> Nenhum registro encontrado, Operacao cancelada!\n");
                break;
            case '5':
                if (n > 0){
                v = array_limpar(v, &n);
                    printf("Lista vazia, array limpo!\n");
                }
                else 
                    printf("--> Nenhum registro encontrado, operacao cancelada!\n");
                break; 
            case '6':
                v = array_limpar(v, &n);
                v = importarDadosDeUmArquivoNoFormatoCSV(v, &n, "listaImpressoras.csv");
                if (n == 0)
                    printf("--> Nenhum registro encontrado!\n");
                break;
            case '7':
                if (n > 0)
                    exportarDadosParaUmArquivoNoFormatoCSV(v, n, "listaImpressoras.csv");
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

void listarImpressora(Impressora v[], const int N)
{
    int i;

    if (v == NULL || N == 0)
    {
        printf("--> Vetor vazio!\n");
        return;
    }

    printf(" %cndice | %-30s | %-30s | Tipo | Capacidade Mensal\n", 214, "Marca", "Modelo");
    printf("------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < N; i++)
        printf(" %-6d | %-30s | %-30s | %-4.2c | %-4.1d\n", i, v[i].marca, v[i].modelo, v[i].tipo, v[i].capacidadeMensal);
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
    }while (!(tipo == 'T' || tipo == 't' || tipo == 'C' || tipo == 'c'));

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

void BuscarPorInformacoesDeUmCampoEspecifico(Impressora v[], const int N){
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
        opcao = exibirMenu(sub_menu, N_SUBMENU);
        switch (opcao)
        {
            case '0':
                printf("Digite o nome da marca da impressora pelo qual voce quer buscar: ");
                gets(marca);
                
                printf("\n%cndice | %-30s | %-30s | Tipo | Capacidade Mensal\n", 214, "Marca", "Modelo");
                printf("------------------------------------------------------------------------------------------------------\n");
                for (i = 0; i < N; i++) {
                    if(strcmp(v[i].marca, marca) == 0)
                        printf(" %-6d | %-30s | %-30s | %-4.2c | %-4.1d\n", i, v[i].marca, v[i].modelo, v[i].tipo, v[i].capacidadeMensal);  
                }
                printf("\n");
                break;
            case '1':
                printf("Digete o nome do modelo de impressora pelo qual voce quer buscar: ");
                gets(modelo);
                
                printf("%cndice | %-30s | %-30s | Tipo | Capacidade Mensal\n", 214, "Marca", "Modelo");
                printf("------------------------------------------------------------------------------------------------------\n");
                for (i = 0; i < N; i++) {
                    if(strcmp(v[i].modelo, modelo) == 0)
                        printf(" %-6d | %-30s | %-30s | %-4.2c | %-4.1d\n", i, v[i].marca, v[i].modelo, v[i].tipo, v[i].capacidadeMensal);  
                }
                printf("\n");

                break;
            case '2':
                printf("Digete o nome do tipo: T(toner) ou C(cartucho) pelo qual voce quer buscar: ");
                scanf("%c", &tipo);
                getchar();
               
                printf("%cndice | %-30s | %-30s | Tipo | Capacidade Mensal\n", 214, "Marca", "Modelo");
                printf("------------------------------------------------------------------------------------------------------\n");
                for (i = 0; i < N; i++) {
                    if(v[i].tipo == tipo)
                        printf(" %-6d | %-30s | %-30s | %-4.2c | %-4.1d\n", i, v[i].marca, v[i].modelo, v[i].tipo, v[i].capacidadeMensal);  
                }
                printf("\n");

                break;
            case '3':
                printf("Digete a capacidade mensal pelo qual voce deseja buscar: "); 
                scanf("%d", &capacidadeMensal);
                getchar();

                printf("%cndice | %-30s | %-30s | Tipo | Capacidade Mensal\n", 214, "Marca", "Modelo");
                printf("------------------------------------------------------------------------------------------------------\n");
                for (i = 0; i < N; i++) {
                    if(v[i].capacidadeMensal == capacidadeMensal)
                        printf(" %-6d | %-30s | %-30s | %-4.2c | %-4.1d\n", i, v[i].marca, v[i].modelo, v[i].tipo, v[i].capacidadeMensal);  
                }
                printf("\n");
                break;
            case 'L':
                clrscr();
                break;
        }
    } while (opcao != 'X');
}

Impressora *atualizarUmaImpressora(Impressora v[], int *v_length){
    char tipo;
    int  i, index, capacidadeMes;

    printf("Entre com o %cndice da impressora a ser atualizado ou -1 para cancelar a opera%c%co: ", 161, 135, 198);
    scanf("%d", &index);
    getchar();

    for(i = 0; i < v_length; i++){
        if(i == index){
            printf("\n--> Atualizacao do cadastro da impressora\n\n");

            printf("Marca atual -> %s, digite a nova marca: ", v[i].marca);
            gets(v[i].marca);

            printf("Modelo atual -> %s, digite o novo modelo: ", v[i].modelo);
            gets(v[i].modelo);

            do
            {
                printf("Tipo atual -> %c, digite o novo tipo: ", v[i].tipo);
                scanf("%c", &tipo);
                getchar();

            } while (!(tipo == 'T' || tipo == 't'|| tipo == 'C' || tipo == 'c'));

            do
            {
                printf("Capacidade Mensal -> %d, digite a nova capacidade: ", v[i].capacidadeMensal);
                scanf("%d", &capacidadeMes);
                getchar();

            } while (capacidadeMes >= 50000 || capacidadeMes <= 0);

            v[i].tipo = tipo;
            v[i].capacidadeMensal = capacidadeMes;
        }
        else
            continue;
    }

    return v;
}

int removerImpressora()
{
    int index = -1;

    printf("Entre com o %cndice da impressora a ser removido ou -1 para cancelar a opera%c%co: ", 161, 135, 198);
    scanf("%d", &index);
    getchar();

    return index;
}

Impressora *importarDadosDeUmArquivoNoFormatoCSV(Impressora v[], int *v_length, char *filename)
{
    FILE *arquivo = NULL;
    Impressora reg;
    char str[200];
    int num_campos;

    // Abre o arquivo para leitura
    if ((arquivo = fopen(filename, "r")) == NULL)
    {
        printf("--> Erro na abertura do arquivo!\n\n");
        return v;
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
            v = array_adicionarNoFim(v, v_length, reg);
        }
    }
    fclose(arquivo);

    return v;
}

void exportarDadosParaUmArquivoNoFormatoCSV (Impressora *v, int v_length, char *filename)
{
    FILE *arquivo = NULL;
    int i;

    // Abre o arquivo para escrita
    if ((arquivo = fopen(filename, "w")) == NULL)
    {
        printf("Erro na abertura do arquivo!\n\n");
        return;
    }

    for (i = 0; i < v_length; i++)
    {
        fprintf(arquivo, "%s,%s,%c,%d\n", v[i].marca, v[i].modelo, v[i].tipo, v[i].capacidadeMensal);
    }
    printf("--> Dados exportados...\n");

    fclose(arquivo);
}