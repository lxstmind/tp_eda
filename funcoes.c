#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/**
 * @brief função que retorna um id disponivel para atribuir a um conta ou transporte criado com base no conteudo do ficheiro
 * 
 * @param file_name nome do ficheiro a ser verificado   
 * @return int 
 */
int getId(char * file_name) {
    char buffer[MAX_LOCAL_LENGTH + MAX_MORADA_LENGTH + MAX_NAME_LENGTH + MAX_PASSWORD_LENGTH + 1]; //tamanho todo da minha linha
    FILE *fp = fopen(file_name, "r");
    int id = 1;
    if (fp) { //verificar se o ficheiro existe
    //abre o ficheiro de clientes e verifica linha a linha no tamanho dos caracteretes
        while (fgets(buffer, MAX_LOCAL_LENGTH + MAX_MORADA_LENGTH + MAX_NAME_LENGTH + MAX_PASSWORD_LENGTH + 1, fp) != NULL) { //fgets pega na string e o atoi converte a string num int
            int current_id = atoi(strtok(buffer, ";")); //pega no id atual que é até ao primeiro ";" só até ao primeiro ; (atoi converte de string para o inteiro)
            if (current_id > id) { //verificar os casos das linhas duplicadas
                id = current_id;
            }
        }
        fclose(fp);
    }
    return id;
}

/**
 * @brief função que limpa a consola
 * 
 */
void clear_console(){
    system("@cls||clear");
}


// C L I E N T E S

/**
 * @brief menu para os clientes iniciarem sessão ou criarem um nova conta
 * 
 */
void menuCliente(){
    int opcaoCliente = 0;
    int id = getId("clientes.txt");
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
                menuClienteLogin(id);
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

/**
 * @brief menu para os clientes depois de iniciarem sessão
 * 
 * @param idLogin inteiro que guarda o id do cliente logado
 */
void menuClienteLogin(int idLogin){
    int opcao=0;
    int id = getId("clientes.txt");
    int tipo, tipoTransporte;
    float bat=0;
    float aut=0;
    float saldo=0;
    char localizacao[MAX_MORADA_LENGTH +1];
    char idLocal[MAX_LOCAL_LENGTH];
    char ponto[MAX_LOCAL_LENGTH];
    cliente* inicioCliente = lerClientes();
    transporte* inicioTransporte = lerTransportes();

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
        printf("2 Alterar dados e/ou carregar saldo na conta\n");
        printf("3 Listar por ID as localizacoes\n");
        printf("4 Listar todos os transportes disponiveis\n");
        printf("5 Listar os transportes disponiveis por localizacao\n");
        printf("6 Listar os transportes mais proximos disponiveis\n");
        printf("7 Alugar transporte\n");
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
                printf("Digite o ID: ");
                scanf("%s", idLocal);
                imprimirLocalizacao(idLocal);
                fflush(stdin);
                getchar();
                break;
                
            case 4:
                printf("Tenha atencao que o tipo 1 e trotinete e o tipo 2 e bicicleta.\n");
                listarPorAutonomia(inicioTransporte);
                fflush(stdin);
                getchar();
                break;

            case 5:
                printf("Qual e a localizacao que deseja ver os transportes disponiveis?\n");
                scanf("%31s", localizacao);
                listarPorLocalizacao(inicioTransporte, localizacao);
                fflush(stdin);
                getchar();
                break;
            
            case 6:
                printf("Qual e a sua localizacao atual?\n");
                scanf("%s", ponto);
                printf("Digite o tipo de transporte (1 - Trotinete, 2 - Bicicleta)\n");
                scanf("%d", &tipoTransporte);
        
                listarTransportesMaisPerto(ponto, tipoTransporte);
                fflush(stdin);
                getchar();
                break;

            case 7:
                printf("Digite o ID do transporte que deseja alugar: ");
                int id_transporte;
                scanf("%d", &id_transporte);
                alugarTransporte(inicioTransporte, inicioCliente, id_transporte, clienteLogado);
                fflush(stdin);
                getchar();
                break;
        }
    } while(opcao!=0);
}


// G E S T O R E S

/**
 * @brief menu para os gestores iniciarem sessão ou criarem um nova conta
 * 
 */
void menuGestor(){
    int opcaoGestor = 0;
    gestor* inicio = lerGestores();
    int id = getId("gestores.txt");
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

/**
 * @brief menu para gestores depois de efetuar o login
 * 
 */
void menuGestorLogin(){
    int opcao=0;
    int id = getId("transportes.txt");
    int idCliente, idTransporte, idLogin;
    int tipo;
    char localizacao[MAX_MORADA_LENGTH +1];
    float custo=0;
    float bat=0;
    float aut=0;
    char novoId[MAX_LOCAL_LENGTH];
    char nomeLugar[MAX_LOCAL_LENGTH];
    char vOrigem[MAX_LOCAL_LENGTH];
    char vDestino[MAX_LOCAL_LENGTH];
    float peso;
    char ponto[MAX_LOCAL_LENGTH];
    transporte* inicioTransporte = lerTransportes();
    cliente* inicioCliente = lerClientes();
    gestor* inicioGestor = lerGestores();
    Grafo g = NULL;

    do {
        clear_console();
        printf("M E N U   G E S T O R   L O G I N\n\n");
        printf("1 Adicionar transporte\n");
        printf("2 Listar todos os transportes\n");
        printf("3 Listar transportes por localizacao especifica\n");
        printf("4 Alterar dados de transportes\n");
        printf("5 Remover transporte\n");
        printf("6 Listar clientes\n");
        printf("7 Alterar dados de cliente\n");
        printf("8 Remover cliente\n");
        printf("9 Alterar dados de gestor\n");
        printf("10 Remover gestor\n");
        printf("11 Adicionar localizacao\n");
        printf("12 Adicionar caminho\n");
        printf("13 Remover localizacao\n");
        printf("14 Remover caminho\n");
        printf("15 Listar vertices adjacentes\n");
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
                listarPorAutonomia(inicioTransporte);
                fflush(stdin);
                getchar();
                break;

            case 3:
                printf("Qual e a localizacao que deseja ver os transportes disponiveis?\n");
                scanf("%31s", &localizacao);
                listarPorLocalizacao(inicioTransporte, localizacao);
                fflush(stdin);
                getchar();
                break;

            case 4:
                printf("Qual e o ID do transporte que pretende alterar os dados?\n");
                scanf("%d", &idLogin);
                alterarDadosTransporte(inicioTransporte, idLogin);
                fflush(stdin);
                getchar();
                break;

            case 5:
                removerTransporte();
                fflush(stdin);
                getchar();
                break;

            case 6:
                listarClientes(inicioCliente);
                fflush(stdin);
                getchar();
                break;

            case 7:
                printf("Qual e o ID do cliente que pretende alterar os dados?\n");
                scanf("%d", &idLogin);
                alterarDadosCliente(inicioCliente, idLogin);
                fflush(stdin);
                getchar();
                break;

            case 8:
                removerCliente();
                fflush(stdin);
                getchar();
                break;

            case 9:
                printf("Qual e o ID do gestor que pretende alterar os dados?\n");
                scanf("%d", &idLogin);
                alterarDadosGestor(inicioGestor, idLogin);
                fflush(stdin);
                getchar();
                break;

            case 10:
                removerGestor();
                fflush(stdin);
                getchar();
                break;
            
            case 11: {
                printf("Digite o novo identificador do vertice: ");
                scanf("%s", novoId);
                
                printf("Digite o nome do lugar: ");
                scanf(" %[^\n]", nomeLugar);
                
                int resultado = criarVertice(&g, novoId);
                if (resultado == 1) {
                    printf("Vertice criado com sucesso!\n");

                    // Abre o arquivo "localizacoes.txt" em modo de escrita (cria o arquivo se não existir)
                    FILE *arquivo = fopen("localizacoes.txt", "w");
                    if (arquivo == NULL) {
                        printf("Falha ao abrir o arquivo.\n");
                        break;
                    }

                    // Escreve as informações do vértice no arquivo
                    fprintf(arquivo, "%s;%s\n", novoId, nomeLugar);

                    // Fecha o arquivo
                    fclose(arquivo);
                } else {
                    printf("Falha ao criar vertice.\n");
                }
                break;
            }

            case 12: {
                printf("Digite o vertice de origem: ");
                scanf("%s", vOrigem);

                printf("Digite o vertice de destino: ");
                scanf("%s", vDestino);

                printf("Digite o peso da aresta: ");
                scanf("%f", &peso);

                int resultado = criarAresta(g, vOrigem, vDestino, peso);
                if (resultado == 1) {
                    printf("Aresta criada com sucesso!\n");
                } else {
                    printf("Falha ao criar aresta.\n");
                }

                FILE *arquivo = fopen("arestas.txt", "w");
                if (arquivo == NULL) {
                    printf("Falha ao abrir o arquivo.\n");
                    break;
                }

                // Escreve as informações da aresta no arquivo
                fprintf(arquivo, "%s;%s;%.3f\n", vOrigem, vDestino, peso);

                // Fecha o arquivo
                fclose(arquivo);

                printf("Aresta criada com sucesso!\n");
                fflush(stdin);
                getchar();
                break;
            }

            case 13:
                removerLocalizacao();
                fflush(stdin);
                getchar();
            break;

            case 14:
                removerAresta();
                fflush(stdin);
                getchar();
            break;

            case 15:
                printf("Informe o ponto: ");
                scanf("%s", ponto);
                listarArestasPorPonto(ponto);
                fflush(stdin);
                getchar();
            break;
        }
    } while(opcao!=0);
}


// M E N U

/**
 * @brief menu inicial
 * 
 */
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