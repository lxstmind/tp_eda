#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void clear_console(){
     system("@cls||clear");
}


// C L I E N T E S


void menuCliente(){
    int opcaoCliente = 0;
    cliente* inicioID = NULL;
    int id = atribuirIdCliente(inicioID);
    cliente* inicio = lerClientes();
    char password[MAX_PASSWORD_LENGTH + 1];
    int id_received = 0;
    char nome[MAX_NAME_LENGTH + 1];
    char morada[MAX_MORADA_LENGTH +1];
    int nif;
    float saldo=0;
    do{
    clear_console();
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

        if (inicio != NULL && verifLoginCliente(inicio, id_received, password) != 0 ){
            menuClienteLogin();
        } else {
            printf("ID ou password incorreto. Tente novamente.\n");
        }
        printf("%d, %s", id_received, password);
        break;
	
        case 2:
        printf("Qual e o teu nome?\n");
        fflush(stdin);
        scanf("%[^\n]", nome);
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
        fflush(stdin);
        printf("Pressione qualquer tecla para continuar.");
        getchar();
        inicio=criarContaCliente(inicio, id++, password, nome, nif, morada, saldo);
        guardarCliente(inicio);
        break;
	    }
        } while (opcaoCliente != 0);
}

void menuClienteLogin(){
    int opcao=0, idLogin;
    cliente *inicioID = NULL;
    int id = atribuirIdCliente(inicioID);
    int tipo;
    float bat=0;
    float aut=0;
    cliente* inicioCliente = lerClientes();
    transporte* inicioTransporte = lerTransportes();

    printf("Confirme o seu ID novamente para mostrar que nao e robo.\n");
    scanf("%d", &idLogin);

    // buscar o cliente correspondente ao ID informado
    cliente* clienteLogado = buscarCliente(inicioCliente, idLogin);

    if (clienteLogado == NULL) {
        printf("Erro: cliente nao encontrado.\n");
        return;
    }

    do{
        clear_console();
        printf("M E N U   C L I E N T E   L O G I N\n\n");
        printf("1 Ver dados da conta\n");
        printf("2 Alterar dados da conta\n");
        printf("3 Listar transportes\n");
        printf("0 Voltar atras\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                imprimirCliente(clienteLogado);
                fflush(stdin);
                getchar();
                break;
            case 2:
                alterarDadosCliente(inicioCliente, idLogin);
                fflush(stdin);
                getchar();
                break;
            case 3:
                printf("Tenha atencao que o tipo 1 e trotinete e o tipo 2 e bicicleta.\n");
                listarPorBateria(inicioTransporte);
                fflush(stdin);
                getchar();
                break;
        }

    } while(opcao!=0);
}



// G E S T O R E S


void menuGestor(){
    int opcaoGestor = 0;
    gestor *inicioID = NULL;
    int id = atribuirIdGestores(inicioID);
    gestor* inicio = lerGestores();
    int id_received = 0;
    char password[MAX_PASSWORD_LENGTH + 1];
    char nome[MAX_NAME_LENGTH + 1];
    do {
        clear_console();
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

		if (inicio != NULL && verifLoginGestor(inicio, id_received, password) != 0 ){
                    id = id_received;
                    menuGestorLogin();
                } else {
                    printf("ID ou password incorreto. Tente novamente.\n");
                }
                break;

        case 2:
        printf("Qual e o teu nome?\n");
        fflush(stdin);
        scanf("%[^\n]", nome);
        printf("Qual e a sua password?\n");
        scanf("%31s", password);
        printf("Guarde o seu ID para utilizar no inicio da sua proxima sessao: %d\n", id);
        fflush(stdin);
        printf("Pressione qualquer tecla para continuar.");
        getchar();
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
    } while(opcaoGestor!=0);
}

void menuGestorLogin(){
    int opcao=0;
    transporte *inicioID = NULL;
    int id = atribuirIdTransportes(inicioID);
    int idCliente, idTransporte, idLogin;
    int tipo;
    char localizacao[MAX_MORADA_LENGTH +1];
    float custo=0;
    float bat=0;
    float aut=0;
    transporte* inicioTransporte = lerTransportes();
    cliente* inicioCliente = lerClientes();
    gestor* inicioGestor = lerGestores();

    do {
        clear_console();
        printf("M E N U   G E S T O R   L O G I N\n\n");
        printf("1 Adicionar transporte\n");
        printf("2 Listar transportes\n");
        printf("3 Alterar dados de transportes\n");
        printf("4 Remover transporte\n");
        printf("5 Listar clientes\n");
        printf("6 Alterar dados de cliente\n");
        printf("7 Remover cliente\n");
        printf("8 Alterar dados de gestor\n");
        printf("9 Remover gestor\n");
        printf("0 Voltar atras\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
            printf("Qual e o tipo do transporte?\n");
            printf("Selecione 1 trotinete ou 2 bicicleta\n");
            scanf("%d", &tipo);
            printf("Qual e a localizacao do transporte?\n");
            scanf("%31s", &localizacao);
            printf("Qual e o custo por hora do transporte?\n");
            scanf("%f", &custo);
            do{
                printf("Qual e a percentagem da bateria do transporte?\n");
                scanf("%f", &bat);
                if (bat < 0 || bat > 100) {
                    printf("Erro: a percentagem de bateria deve estar entre 0 e 100.\n");
                }
            } while (bat < 0 || bat > 100);
            printf("Qual e a autonomia do transporte?\n");
            scanf("%f", &aut);
            
            inicioTransporte=criarTransporte(inicioTransporte, id++, tipo, localizacao, custo, bat, aut);
            guardarTransporte(inicioTransporte);
            break;

            case 2:
            listarPorBateria(inicioTransporte);
            fflush(stdin);
            getchar();
            break;

            case 3:
            printf("Qual e o ID do transporte que pretende alterar os dados?\n");
            scanf("%d", &idLogin);
            alterarDadosTransporte(inicioTransporte, idLogin);
            fflush(stdin);
            getchar();
            break;

            case 4:
            removerTransporte();
            fflush(stdin);
            getchar();
            break;

            case 5:
            listarClientes(inicioCliente);
            fflush(stdin);
            getchar();

            case 6:
            printf("Qual e o ID do cliente que pretende alterar os dados?\n");
            scanf("%d", &idLogin);
            alterarDadosCliente(inicioCliente, idLogin);
            fflush(stdin);
            getchar();
            break;

            case 7:
            removerCliente();
            fflush(stdin);
            getchar();
            break;

            case 8:
            printf("Qual e o ID do gestor que pretende alterar os dados?\n");
            scanf("%d", &idLogin);
            alterarDadosGestor(inicioGestor, idLogin);
            fflush(stdin);
            getchar();
            break;

            case 9:
            removerGestor();
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
        clear_console();
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