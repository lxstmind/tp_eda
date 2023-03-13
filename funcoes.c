#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int getId() {
    FILE *fp_clientes = fopen("clientes.txt", "r");
    FILE *fp_gestores = fopen("gestores.txt", "r");
    int id_clientes = 0, id_gestores = 0;
    char buffer[MAX_LOCAL_LENGTH + MAX_MORADA_LENGTH + MAX_NAME_LENGTH + MAX_PASSWORD_LENGTH + 1]; //tamanho todo da minha linha

    if (fp_clientes) { //verificar se o ficheiro existe
        //abre o ficheiro de clientes e verifica linha a linha no tamanho dos caracteretes
        while (fgets(buffer, MAX_LOCAL_LENGTH + MAX_MORADA_LENGTH + MAX_NAME_LENGTH + MAX_PASSWORD_LENGTH + 1, fp_clientes) != NULL) { 
            int current_id = atoi(strtok(buffer, ";")); //pega no id atual que é até ao primeiro ";" só até ao primeiro ;
            if (current_id > id_clientes) { //verificar os casos das linhas duplicadas (muito raro, quase impossivel só um burro é que fode isso ao por um numero negativo)
                id_clientes = current_id;
            }
        }
        fclose(fp_clientes);
    }

    if (fp_gestores) {
        while (fgets(buffer, MAX_LOCAL_LENGTH + MAX_MORADA_LENGTH + MAX_NAME_LENGTH + MAX_PASSWORD_LENGTH + 1, fp_gestores) != NULL) {
            int current_id = atoi(strtok(buffer, ";"));
            if (current_id > id_gestores) {
                id_gestores = current_id;
            }
        }
        fclose(fp_gestores);
    }
    //compara o id dos clientes com o dos gestores e se for maior ele adiciona 1 ao ultimo id quer seja cliente ou gestor
    return (id_clientes > id_gestores) ? id_clientes + 1 : id_gestores + 1;
}

void clear_console(){
     system("@cls||clear"); // linux ou windows
 }


// C L I E N T E


void menuCliente(){
    int opcaoCliente = 0;
    int id = getId();
    cliente* inicio = NULL;
    char password[MAX_PASSWORD_LENGTH + 1];
    int id_received = 0;
    char nome[MAX_NAME_LENGTH + 1];
    char morada[MAX_MORADA_LENGTH +1];
    int nif;
    float saldo=0;
    do{
    printf("M E N U   C L I E N T E\n\n");
    printf("1 Iniciar Sessao\n");
    printf("2 Criar Conta\n");
    printf("0 Voltar atras\n");
    scanf("%d", &opcaoCliente);

    switch(opcaoCliente){
        case 1:
		printf("Introduza o seu ID:\n");
        scanf("%d", &id_received);
        printf("Introduza a sua password:\n");
        scanf("%s", password);

        if (id=verifLoginCliente(inicio, id,password)==0){
            printf("teste");
            fflush(stdin);
            getchar();
        }
        break;
	
        case 2:
        printf("Qual e o teu nome?\n");
        scanf("%63s", nome);
        //Loop para garantir que o nif tem 9 numeros
            do {
                printf("Qual e o teu NIF?\n");
                scanf("%d", &nif);

            if (nif <= 0 || nif < 100000000 || nif > 999999999) {
                printf("Erro: o NIF deve ser um numero positivo e ter 9 digitos.\n");
            }
            } while (nif <= 0 || nif < 100000000 || nif > 999999999);
        printf("Qual e a tua morada?\n");
        scanf("%63s", morada);
        printf("Qual e a sua password?\n");
        scanf("%31s", password);
        //Loop par garantir que o dinheiro e positivo
            do {
                printf("Quanto dinheiro deseja depositar na sua conta?\n");
                scanf("%f", &saldo);

            if (saldo <= 0) {
                printf("Erro: o saldo deve ser positivo.\n");
            }
            } while (saldo <= 0);

        printf("Guarde o seu ID para utilizar no inicio da sua proxima sessao: %d\n", id);

        inicio=criarContaCliente(inicio, id++, password, nome, nif, morada, saldo);
        guardarCliente(inicio);
        break;
	    }
        clear_console();
        } while (opcaoCliente != 0);
}


// G E S T O R


void menuGestor(){
    int opcaoGestor = 0;
    gestor* inicio = lerGestores();
    int id = getId();
    int id_received = 0;
    char password[MAX_PASSWORD_LENGTH + 1];
    char nome[MAX_NAME_LENGTH + 1];
    do {
    printf("M E N U   G E S T O R\n\n");
    printf("1 Iniciar Sessao\n");
    printf("2 Criar Conta\n");
    printf("0 Voltar atras\n");
    scanf("%d", &opcaoGestor);

    switch(opcaoGestor){
        case 1:
        printf("Introduza o seu ID:\n");
        scanf("%d", &id_received);
        printf("Introduza a sua password:\n");
        scanf("%s", password);

		if ((id = verifLoginGestor(inicio, id, password)) == 0 ){
            menuGestorLogin();
        }
        break;

        case 2:
        printf("Qual e o teu nome?\n");
        scanf("%63s", nome);
        printf("Qual e a sua password?\n");
        scanf("%31s", password);
        printf("Guarde o seu ID para utilizar no inicio da sua proxima sessao: %d\n", id);

        inicio=criarContaGestor(inicio, id++, password, nome);
        guardarGestor(inicio);

    if (inicio != NULL)
    {
        printf("Conta gestor criada com sucesso!\n");
    }
    else
    {
        printf("Erro ao criar conta gestor.\n");
    }
    break;
    }
    clear_console();
    } while(opcaoGestor!=0);
}

void menuGestorLogin(){
    int opcao=0;
    int id = getId();
    int tipo;
    float bat=0;
    float aut=0;
    transporte* inicioTransporte = NULL;
    cliente* inicioCliente = NULL;

    do {
        printf("M E N U   G E S T O R   L O G I N\n\n");
        printf("1 Adicionar transporte\n");
        printf("2 Listar transportes por ordem crescente de bateria\n");
        printf("3 Listar clientes\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
            printf("Qual e o tipo do transporte?\n");
            printf("Selecione 1 trotinete ou 2 bicicleta\n");
            scanf("%d", &tipo);
            do{
                printf("Qual e a percentagem da bateria do transporte?\n");
                scanf("%f", &bat);
                if (bat < 0 || bat > 100) {
                    printf("Erro: a percentagem de bateria deve estar entre 0 e 100.\n");
                }
            } while (bat < 0 || bat > 100);
            printf("Qual e a autonomia do transporte?\n");
            scanf("%f", &aut);
            
            inicioTransporte=criarTransporte(inicioTransporte, id++, tipo, bat, aut);
            guardarTransporte(inicioTransporte);
            break;

            case 2:
            listarTransportes(inicioTransporte);
            fflush(stdin);
            getchar();
            break;

            case 3:
            listarClientes(inicioCliente);
            fflush(stdin);
            getchar();
            break;
        }
    } while(opcao!=0);
}


// M E N U


void menu(){
	int opcaoMenu = 0;
    do {
        printf("M E N U\n\n");
        printf("1 Seguir como cliente\n");
        printf("2 Seguir como gestor\n");
        printf("0 Sair\n");
        scanf("%d", &opcaoMenu);

        switch(opcaoMenu){
            case 1:
                menuCliente();
                break;
            case 2:
                menuGestor();
                break;
            default:
                opcaoMenu = 0;
        }
    } while (opcaoMenu != 0);
}