#include <stdio.h>
#define N 10

struct Paciente 
{
    char cpf[14];
    char nome[20];
    int idade;
};

typedef struct Paciente Paciente;

int menu(int *opc);
int adicionarFilaNormal (Paciente filaNormal[], int IAN, int FAN, int *ILN, int *FLN, Paciente nodoFilaNormal);
int adicionarFilaEmergencia (Paciente filaEmergencia[], int IAE, int FAE, int *ILE, int *FLE, Paciente nodoFilaEmergencia);
int atenderPaciente (Paciente filaNormal[], int IAN, int FAN, int *ILN, int *FLN, Paciente filaEmergencia[], int IAE, int FAE, int *ILE, int *FLE); 
int visualizarListas (Paciente filaNormal[], int IAN, int FAN, int ILN, int FLN, Paciente filaEmergencia[], int IAE, int FAE, int ILE, int FLE);

int main()
{
    Paciente filaNormal[N], nodoFilaNormal;
    Paciente filaEmergencia[N], nodoFilaEmergencia; 
    
    int IAN = 0, FAN = N - 1, ILN = -1, FLN = -1;
    int IAE = 0, FAE = N - 1, ILE = -1, FLE = -1;
    int opc;
    
    do{
    
        menu(&opc);
        switch (opc){
            case 1: 
                if (IAN == ILN && FAN == FLN) {
                    printf("Lista cheia!\n");
                    printf("\n");
                }
                else{
                    printf("\n");
                    printf("Adicionar paciente na fila normal: \n");
                    printf("CPF: "); scanf("%s",nodoFilaNormal.cpf);
                    printf("Nome: "); scanf("%s",nodoFilaNormal.nome);
                    printf("Idade: "); scanf("%d",&nodoFilaNormal.idade);
                    adicionarFilaNormal (filaNormal, IAN, FAN, &ILN, &FLN, nodoFilaNormal);
                    printf("\n");
                }
                break;
            case 2:
                if (IAE == ILE && FAE == FLE){ 
                    printf("Lista cheia!\n");
                }
                else{
                    printf("\n");
                    printf("Adicionar paciente na fila de emergência: \n");
                    printf("CPF: "); scanf("%s",nodoFilaEmergencia.cpf);
                    printf("Nome: "); scanf("%s",nodoFilaEmergencia.nome);
                    printf("Idade: "); scanf("%d",&nodoFilaEmergencia.idade);
                    adicionarFilaEmergencia (filaEmergencia, IAE, FAE, &ILE, &FLE, nodoFilaEmergencia);
                    printf("\n");
                }
                break;
            case 3:
                atenderPaciente (filaNormal, IAN, FAN, &ILN, &FLN, filaEmergencia, IAE, FAE, &ILE, &FLE);
                printf("\n");
                break;
            case 4:
                printf("\n");
                visualizarListas (filaNormal, IAN, FAN, ILN, FLN, filaEmergencia, IAE, FAE, ILE, FLE);
                printf("\n");
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opc != 0);
}

int menu(int *opc) 
{
    printf("--------------------------------------------\n");
    printf("                   TRIAGEM                  \n");
    printf("--------------------------------------------\n");
    printf("[1] Adicionar Paciente na Fila Normal\n");
    printf("[2] Adicionar Paciente na Fila de Emergência\n");
    printf("[3] Atender Paciente\n");
    printf("[4] Visualizar Filas\n");
    printf("[0] Sair\n\n");
    printf("Escolha uma opção: ");
    scanf("%d", opc);
    return 0;
}

int adicionarFilaNormal (Paciente filaNormal[], int IAN, int FAN, int *ILN, int *FLN, Paciente nodoFilaNormal) 
{
    if (*ILN == -1)
        *ILN = *FLN = IAN;
    else if (*FLN < FAN)
            *FLN = *FLN+1;                  
    else 
    {       
        for (int i=*ILN; i>=*FLN; i++)
            filaNormal[i+1] = filaNormal[i];
        *FLN = *FLN+1;
    }
    filaNormal[*FLN] = nodoFilaNormal;
    return 0;
}

int adicionarFilaEmergencia (Paciente filaEmergencia[], int IAE, int FAE, int *ILE, int *FLE, Paciente nodoFilaEmergencia) 
{
    if (*ILE == -1)
        *ILE = *FLE = IAE;
    else if (*FLE < FAE)
        *FLE = *FLE+1;                  
    else 
    {       
        for (int i=*ILE; i>=*FLE; i++)
            filaEmergencia[i+1] = filaEmergencia[i];
        *FLE = *FLE+1;
    }
    filaEmergencia[*FLE] = nodoFilaEmergencia;
    return 0;
}

int atenderPaciente (Paciente filaNormal[], int IAN, int FAN, int *ILN, int *FLN, Paciente filaEmergencia[], int IAE, int FAE, int *ILE, int *FLE) {
    
    if(*ILE > -1){
        printf("Paciente a ser atendido: \n");
        printf("%s - %s - %d\n", filaEmergencia[*ILE].cpf, filaEmergencia[*ILE].nome, filaEmergencia[*ILE].idade);
        
        for(int i=IAE; i<=FAE; i++){
            filaEmergencia[i] = filaEmergencia[i+1];
        }
        (*FLE)--;
        if (*FLE < *ILE){ 
            *ILE = *FLE = -1;
        }
    }
    else if (*ILN > -1)
    {
        printf("Paciente a ser atendido: \n");
        printf("%s - %s - %d\n", filaNormal[*ILN].cpf, filaNormal[*ILN].nome, filaNormal[*ILN].idade);
        
        for(int i=IAN; i<=FAN; i++){
            filaNormal[i] = filaNormal[i+1];
        }
        (*FLN)--;
        if (*FLN < *ILN){ 
            *ILN = *FLN = -1;
        }
    }
    else
    {
        printf("Não há pacientes no momento!\n");
    }
}



int visualizarListas (Paciente filaNormal[], int IAN, int FAN, int ILN, int FLN, Paciente filaEmergencia[], int IAE, int FAE, int ILE, int FLE) 
{
    printf("Fila Emergência: \n");
    for(int i=IAE; i<=FAE; i++){
        if(i>=ILE && i<=FLE)
            printf("%s - %s - %d\n", filaEmergencia[i].cpf, filaEmergencia[i].nome, filaEmergencia[i].idade);
        else
            printf("-------\n");
    }
    
    printf("\n");
    
    printf("Fila Normal: \n");
    for(int i=IAN; i<=FAN; i++){
        if(i>=ILN && i<=FLN)
            printf("%s - %s - %d\n", filaNormal[i].cpf, filaNormal[i].nome, filaNormal[i].idade);
        else
            printf("-------\n");
    }
    return 0;
}







