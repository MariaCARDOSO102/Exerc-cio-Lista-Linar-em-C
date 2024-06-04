#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct TipoNodo{
    char info[50];
    struct TipoNodo *elo;
};

typedef struct TipoNodo TipoNodo;

int menu(void);
int insereInicio (TipoNodo **ponteiroLista, char *dados);
int remocao (TipoNodo **ponteiroLista);
void exibir (TipoNodo *ponteiroLista);

int main()
{
    TipoNodo *ponteiroLista;
    int opc, sucesso;
    char dados[50];
    ponteiroLista = NULL;
    do
    {
        printf("\n");
        opc = menu(); 
        switch(opc)
        {
            case 1:
                printf("+ Nova Página\n");
                printf("Digite a Url: ");
                scanf("%s", dados);
                sucesso = insereInicio(&ponteiroLista, dados);
                if(sucesso == 0){
                    printf("Url inserida com sucesso!");
                    printf("\n");
                }
                else{
                    printf("Lista cheia!");
                    printf("\n");
                }
                break;
            case 2:
                sucesso = remocao(&ponteiroLista);
                if(sucesso == 0){
                    printf("- Voltar para página anterior\n");
                    printf("Página anterior: %s", ponteiroLista->info);
                    printf("\n");
                }
                else{
                    printf("Lista vazia!");
                    printf("\n");
                }
                break;
            case 3:
                exibir(ponteiroLista);
                break;
            case 0:
                break;
            default:
                printf("Opção Inválida!\n");
        }
    }while(opc != 0);
    
}

int menu(void)
{
    int opc;
    printf("--------------- M E N U ---------------\n");
    printf("| [1] Visitar uma nova página          |\n");
    printf("| [2] Voltar à página anterior         |\n");
    printf("| [3] Exibir o histórico de navegação  |\n");
    printf("| [0] Sair do navegador                |\n");
    printf("----------------------------------------\n");
    printf("Digite uma opção: ");
    scanf("%d", &opc);
    printf("\n");
    return opc;
}

int insereInicio (TipoNodo **ponteiroLista, char *dados)
{
    TipoNodo* ponteiroNovo = (TipoNodo*) malloc(sizeof(TipoNodo));
    if (ponteiroNovo == NULL)
        return 1;
    else
    {
        strcpy(ponteiroNovo->info, dados);
        ponteiroNovo->elo = *ponteiroLista;
        *ponteiroLista = ponteiroNovo;
        return 0;
    }
}

void exibir (TipoNodo *ponteiroLista) 
{
    TipoNodo *pont;
    printf("\n");
    printf("| * Histórico   |\n");
    for(pont = ponteiroLista; pont != NULL; pont = pont->elo)
        printf("- %s\n", pont->info);
}

int remocao (TipoNodo **ponteiroLista)
{
    if (*ponteiroLista == NULL) 
    {
        return 1;
    } 
    else {
        TipoNodo *PontK = *ponteiroLista;
        *ponteiroLista = PontK->elo; // PontK->elo é o próximo elemento da lista
        free(PontK);
        if(*ponteiroLista == NULL)
        {
            return 1;
        }
        else 
            return 0;
    }   
}
