#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/**
 * @brief função para criar transporte
 * 
 * @param inicio ponteiro para o inicio da lista ligada
 * @param id inteiro do id que representa o novo transporte
 * @param tipo inteiro do tipo que representa o novo transporte
 * @param localizacao string que representa a localização atual do transporte
 * @param custo numero que representa o custo do transporte
 * @param bat numero que representa a bateria do transporte
 * @param aut numero que representa a autonomia do transporte
 * @return transporte* ponteiro para o novo nó criado da lista de transportes
 */
transporte* criarTransporte(transporte * inicio, int id, int tipo, char localizacao[], float custo, float bat, float aut){
        transporte * novo = malloc(sizeof(struct transporte));
        if (novo != NULL) {
            novo->id = id;
            novo->tipo = tipo;
            strcpy(novo->localizacao, localizacao);
            novo->custo = custo;
            novo->bat = bat;
            novo->aut = aut;
            novo->seguinte = inicio;
            return novo;
        }
    return inicio;
}

/**
 * @brief função que guarda os transportes num ficheiro de texto
 * 
 * @param inicio ponteiro para o início de uma lista de transportes a serem salvos no ficheiro de texto
 */
void guardarTransporte(transporte* inicio){
    FILE* fp;
    fp = fopen("transportes.txt","a");
    if (fp!=NULL){
        transporte* aux= inicio;
        fprintf(fp,"%d;%d;%s;%.2f;%.2f;%.2f\n", aux->id, aux-> tipo, aux-> localizacao, aux->custo, aux->bat, aux->aut);
        fclose(fp);
    }
}

/**
 * @brief le os dados de transportes armazenados em um ficheiro de texto e cria uma lista ligada de transportes a partir desses dados
 * 
 * @return transporte* ponteiro para o início da lista de transportes criada a partir do ficheiro de texto
 */
transporte* lerTransportes(){
    FILE* fp;
    fp = fopen("transportes.txt","r");
    transporte* aux = NULL; //aux foi criada e inicializada com valor nulo pois ainda não foram lidos dados do arqficheirouivo

    if (fp!=NULL){
        int id, tipo;
        char localizacao[MAX_MORADA_LENGTH + 1];
        float custo, bat, aut;

        while (!feof(fp)) { //le cada linha do ficheiro com o fscanf e depois a função criarTransporte é usada para criar o novo transporte
            fscanf(fp, "%d;%d;%[^;];%f;%f;%f\n", &id, &tipo, &localizacao, &custo, &bat, &aut);
            aux = criarTransporte(aux, id, tipo, localizacao, custo, bat, aut);
        }

        fclose(fp);
    }

    return aux; //retorna o ponteiro para o início da lista de transportes criada a partir dos dados lidos do ficheiro de texto.
}

/**
 * @brief ordena a lista ligada de transportes em ordem decrescente de autonomia
 * 
 * @param inicio  ponteiro para o início da lista encadeada de transportes a ser ordenada
 */
void ordenarPorAutonomia(transporte* inicio) {
    int trocado = 1;
    while (trocado) {
        trocado = 0;
        transporte* anterior = NULL;
        transporte* atual = inicio;
        while (atual->seguinte != NULL) {
            if (atual->aut < atual->seguinte->aut) { // trocar a ordem se a autonomia for menor
                transporte* proximo = atual->seguinte;
                atual->seguinte = proximo->seguinte;
                proximo->seguinte = atual;
                if (anterior != NULL) {
                    anterior->seguinte = proximo;
                } else {
                    inicio = proximo;
                }
                anterior = proximo;
                trocado = 1;
            } else {
                anterior = atual;
                atual = atual->seguinte;
            }
        }
    }
}


/**
 * @brief listar na consola os veículos por ordem de autonomia
 * 
 * @param inicio ponteiro para o início da lista encadeada de transportes
 */
void listarPorAutonomia(transporte* inicio) {
    if (inicio == NULL) {
        printf("Nenhum transporte registado.\n");
        return;
    }
    ordenarPorAutonomia(inicio); // ordenar por autonomia
    while (inicio != NULL) {
        printf("ID: %d, Tipo: %d, Localizacao: %s, Custo: %.2f, Bateria: %.2f, Autonomia: %.2f\n", inicio->id, inicio->tipo, inicio->localizacao, inicio->custo, inicio->bat, inicio->aut);
        inicio = inicio->seguinte;
    }
}
/**
 * @brief ordena a lista ligada de transportes em ordem de localização dos transportes
 * 
 * @param inicio ponteiro para o inicio da lista ligada de transportes
 * @param localizacao localização a ser verificada para ordenação dos veículos
 */
void ordenarPorLocalizacao(transporte* inicio, char* localizacao) {
    int trocado = 1;
    while (trocado) {
        trocado = 0;
        transporte* anterior = NULL;
        transporte* atual = inicio;
        while (atual->seguinte != NULL) {
            if (strcmp(atual->localizacao, localizacao) == 0 && atual->aut < atual->seguinte->aut) {
                transporte* proximo = atual->seguinte;
                if (strcmp(proximo->localizacao, localizacao) == 0) {
                    atual->seguinte = proximo->seguinte;
                    proximo->seguinte = atual;
                    if (anterior != NULL) {
                        anterior->seguinte = proximo;
                    } else {
                        inicio = proximo;
                    }
                    anterior = proximo;
                    trocado = 1;
                } else {
                    anterior = atual;
                    atual = atual->seguinte;
                }
            } else {
                anterior = atual;
                atual = atual->seguinte;
            }
        }
    }
}

/**
 * @brief listar na consola os veículos por ordem de localização
 * 
 * @param inicio ponteiro para o incio da lista ligada de transportes
 * @param localizacao localização a ser verificada para ordenação dos veículos
 */
void listarPorLocalizacao(transporte* inicio, char* localizacao) {
    if (inicio == NULL) {
        printf("Nenhum transporte registado.\n");
        return;
    }
    ordenarPorLocalizacao(inicio, localizacao);
    transporte* atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->localizacao, localizacao) == 0) {
            printf("ID: %d, Tipo: %d, Localizacao: %s, Custo: %.2f, Bateria: %.2f, Autonomia: %.2f\n", atual->id, atual->tipo, atual->localizacao, atual->custo, atual->bat, atual->aut);
        }
        atual = atual->seguinte;
    }
}

/**
 * @brief permite ao gestor a alteração dos dados dos transportes
 * 
 * @param inicio ponteiro para o início da lista encadeada de transportes
 * @param id id do transporte a ser alterado
 */
void alterarDadosTransporte(transporte* inicio, int id) { //a função recebe como parâmetros um ponteiro para o início da lista de transportes e o ID do transporte a ser alterado
    transporte* transporteAtual = buscarTransporte(inicio, id);
    if (transporteAtual == NULL) {//se não encontrar o ID para alterar os dados, printa mensagem de erro
        printf("Erro: transporte nao encontrado.\n");
        return;
    }

    int opcao;
    do {
        printf("Escolha o que deseja alterar:\n");
        printf("1 - Tipo: %d\n", transporteAtual->tipo);
        printf("2 - Localizacao: %s\n", transporteAtual->localizacao);
        printf("3 - Custo: %.2f\n", transporteAtual->custo);
        printf("4 - Bateria: %.2f\n", transporteAtual->bat);
        printf("5 - Autonomia: %.2f\n", transporteAtual->aut);
        printf("0 - Confirmar alteracao de dados e sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Qual o novo tipo de transporte?\n");
                scanf("%d", &transporteAtual->tipo);
                break;
            case 2:
                printf("Qual a nova localizacao do transporte?\n");
                scanf("%s", transporteAtual->localizacao);
                break;
            case 3:
                do {
                    printf("Qual o novo custo do transporte?\n");
                    scanf("%f", &transporteAtual->custo);

                    if (transporteAtual->custo < 0) {
                        printf("Erro: o custo deve ser positivo.\n");
                    }
                } while (transporteAtual->custo < 0);
                break;
            case 4:
                do {
                    printf("Qual a nova bateria do transporte?\n");
                    scanf("%f", &transporteAtual->bat);

                    if (transporteAtual->bat < 0) {
                        printf("Erro: a bateria deve ser positiva.\n");
                    }
                } while (transporteAtual->bat < 0);
                break;
            case 5:
                do {
                    printf("Qual a nova autonomia do transporte?\n");
                    scanf("%f", &transporteAtual->aut);

                    if (transporteAtual->aut < 0) {
                        printf("Erro: a autonomia deve ser positiva.\n");
                    }
                } while (transporteAtual->aut < 0);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);

    // atualiza os dados do ficheiro
    FILE* fp = fopen("transportes.txt", "w+");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    // escreve todos os transportes atualizados no ficheiro
    while (inicio != NULL) {
        fprintf(fp, "%d;%d;%s;%.2f;%.2f;%.2f\n", inicio->id, inicio->tipo, inicio->localizacao, inicio->custo, inicio->bat, inicio->aut);
        inicio = inicio->seguinte;
    }

    fclose(fp);

    printf("Dados do transporte atualizados com sucesso!\n");
}

/**
 * @brief buscar um transporte com um determinado ID em uma lista encadeada de transportes
 * 
 * @param inicio ponteiro para o início da lista encadeada de transportes
 * @param id ID do transporte a ser buscado
 * @return transporte* ponteiro para o transporte com o ID correspondente, caso ele seja encontrado na lista
 */
transporte* buscarTransporte(transporte* inicio, int id) { //percorre a lista até encontrar um transporte com o ID correspondente, retorna um ponteiro para esse transporte.
    transporte* aux = inicio;

    while (aux != NULL) {
        if (aux->id == id) {
            return aux;
        }
        aux = aux->seguinte;
    }

    // se chegou aqui, o cliente não foi encontrado
    return NULL;
}

/**
 * @brief recebe um ponteiro para uma estrutura transporte e imprime as informações desse transporte na consola
 * 
 * @param t ponteiro que aponta para um único transporte que será impresso na função
 */
void imprimirTransporte(transporte* t) {
    printf("ID: %d, Tipo: %d, Custo: %.2f, Bateria: %.2f, Autonomia: %.2f", t->id, t->tipo, t->custo, t->bat, t->aut);
}

/**
 * @brief recebe um ID do gestor para remover o transporte de um ficheiro de texto
 * 
 */
void removerTransporte(){
    int idRemover;
    printf("Informe o ID do transporte a ser removido: ");
    scanf("%d", &idRemover);

    // Abre o ficheiro para leitura
    FILE* fp = fopen("transportes.txt", "r");
    if(fp == NULL){
        printf("Erro ao abrir o ficheiro de transportes!\n");
        return;
    }

    // Abre um ficheiro temporário para escrita
    FILE* fpTemp = fopen("temp.txt", "w");
    if(fpTemp == NULL){
        printf("Erro ao criar ficheiro temporário!\n");
        fclose(fp);
        return;
    }

    // Percorre o ficheiro de transportes linha por linha
    char linha[MAX_LOCAL_LENGTH];
    int encontrou = 0;
    while(fgets(linha, MAX_LOCAL_LENGTH, fp)){
        // Lê o ID da linha atual
        int id;
        sscanf(linha, "%d;", &id);

        // Se o ID for diferente do ID a ser removido, escreve a linha no ficheiro temporário
        if(id != idRemover){
            fputs(linha, fpTemp);
        } else {
            encontrou = 1;
        }
    }

    // Fecha os ficheiros
    fclose(fp);
    fclose(fpTemp);

    // Remove o ficheiro antigo
    remove("transportes.txt");

    // Renomeia o ficheiro temporário para o nome original
    rename("temp.txt", "transportes.txt");

    if(encontrou){
        printf("Transporte removido com sucesso!\n");
    } else {
        printf("Transporte não encontrado!\n");
    }
}

/**
 * @brief função que permite aos clientes alugar os transportes
 * 
 * @param inicioTransporte apontador para o inicio da lista de transportes
 * @param inicioCliente apontador para o inicio da lista de clientes
 * @param id_transporte  id correspondente ao transporte alugado
 * @param cliente_atual id correspondente ao cliente atual
 */
void alugarTransporte(transporte* inicioTransporte, cliente* inicioCliente, int id_transporte, cliente* cliente_atual) {
    // Procura o transporte com o ID indicado na lista de transportes
    transporte* transporte_alugado = NULL;
    transporte* transporte_atual = inicioTransporte;
    char linha_aresta[MAX_LOCAL_LENGTH];
    char ponto_partida[MAX_LOCAL_LENGTH];
    char ponto_chegada[MAX_LOCAL_LENGTH];
    char nova_localizacao[MAX_LOCAL_LENGTH];
    char str_data_inicio[TAM];
    float distancia;

    while (transporte_atual != NULL) {
        if (transporte_atual->id == id_transporte) {
            transporte_alugado = transporte_atual;
            break;
        }
        transporte_atual = transporte_atual->seguinte;
    }

    // Se não encontrar o transporte, retorna
    if (transporte_alugado == NULL) {
        printf("Transporte com ID %d nao encontrado.\n", id_transporte);
        return;
    }

    // Inicia a viagem do transporte
    printf("Transporte %d alugado com sucesso!\n", id_transporte);
    printf("Localizacao atual: %s\n", transporte_alugado->localizacao);
    time_t data_inicio = time(NULL);
    strftime(str_data_inicio, TAM, "%d/%m/%Y %H:%M:%S", localtime(&data_inicio));
    printf("Data de inicio da viagem: %s\n", str_data_inicio);

    // Aguarda o usuário indicar o fim da viagem
    printf("Pressione enter para indicar o fim da viagem.");
    fflush(stdin);
    getchar();

    // Final da viagem
    time_t data_fim = time(NULL);
    printf("Transporte %d devolvido com sucesso!\n", id_transporte);
    printf("Data do final da viagem: %s", ctime(&data_fim));

    // Solicita a localizacao no final da viagem
    printf("Digite a localizacao no final da viagem: ");
    fgets(nova_localizacao, MAX_LOCAL_LENGTH, stdin);

    // Remove o caractere de nova linha do final da string
    nova_localizacao[strcspn(nova_localizacao, "\n")] = '\0';

    // Calcula a distância percorrida
    float distancia_percorrida = 0.0;

    // Lê as informações de distância do arquivo "arestas.txt"
    FILE* fp_arestas = fopen("arestas.txt", "r");
    if (fp_arestas == NULL) {
        printf("Erro ao abrir o arquivo de arestas.\n");
        return;
    }

    while (fgets(linha_aresta, sizeof(linha_aresta), fp_arestas)) {
        if (sscanf(linha_aresta, "%[^;];%[^;];%f", ponto_partida, ponto_chegada, &distancia) == 3) {
            if (strcmp(ponto_partida, transporte_alugado->localizacao) == 0 &&
                strcmp(ponto_chegada, nova_localizacao) == 0) {
                distancia_percorrida += distancia;
                break;
            }
        }
    }

    fclose(fp_arestas);

    // Atualiza a localizacao e a bateria do transporte no arquivo "transportes.txt"
    FILE* fp_transporte = fopen("transportes.txt", "r");
    FILE* fp_temp = fopen("temp.txt", "w");
    if (fp_transporte == NULL || fp_temp == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    char linha_transporte[MAX_LOCAL_LENGTH];
    while (fgets(linha_transporte, sizeof(linha_transporte), fp_transporte)) {
        int id, tipo;
        char localizacao[MAX_LOCAL_LENGTH + 1];
        float custo, bateria, autonomia;

        if (sscanf(linha_transporte, "%d;%d;%[^;];%f;%f;%f", &id, &tipo, localizacao, &custo, &bateria, &autonomia) == 6) {
            if (id == id_transporte) {
                strncpy(localizacao, nova_localizacao, MAX_LOCAL_LENGTH);

                // Calcula a diferença de tempo em horas
                double diferenca_tempo = difftime(data_fim, data_inicio);
                double horas_viagem = diferenca_tempo / 3600.0;

                // Reduz a bateria em 50% a cada hora de viagem
                bateria -= (horas_viagem * 0.5);
                if (bateria < 0) {
                    bateria = 0;
                }

                // Reduz a autonomia com base na distância percorrida
                autonomia -= distancia_percorrida;
                if (autonomia < 0) {
                    autonomia = 0;
                }
            }
            fprintf(fp_temp, "%d;%d;%s;%.2f;%.2f;%.2f\n", id, tipo, localizacao, custo, bateria, autonomia);
        }
    }

    fclose(fp_transporte);
    fclose(fp_temp);

    // Substitui o arquivo original pelo arquivo temporário
    remove("transportes.txt");
    rename("temp.txt", "transportes.txt");

    // Calcula o custo total da viagem
    float custo_total = transporte_alugado->custo;

    // Verifica o saldo do cliente atual
    if (cliente_atual == NULL) {
        printf("Cliente nao valido.\n");
        return;
    }

    if (cliente_atual->saldo < custo_total) {
        printf("Saldo insuficiente. Custo total da viagem: %.2f\n", custo_total);
        return;
    }

    // Subtrai o custo total da viagem do saldo do cliente
    float novo_saldo = cliente_atual->saldo - custo_total;
    cliente_atual->saldo = novo_saldo;
    printf("Custo da viagem debitado da conta. Saldo restante: %.2f\n", novo_saldo);

    printf("Viagem concluida com sucesso!\n");
}