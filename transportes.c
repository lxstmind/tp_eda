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
 * @brief ordena a lista ligada de transportes em ordem decrescente de bateria
 * 
 * @param inicio  ponteiro para o início da lista encadeada de transportes a ser ordenada
 */
void ordenarPorBateria(transporte* inicio) { //utilizo o bubble sort para percorrer a lista ligada trocando a ordem. 
    int trocado = 1;
    while (trocado) {
        trocado = 0;
        transporte* anterior = NULL;
        transporte* atual = inicio;
        while (atual->seguinte != NULL) {
            if (atual->bat < atual->seguinte->bat) { //se isto for verdadeira, troca a ordem
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
 * @brief listar na consola os veículos por ordem de bateria
 * 
 * @param inicio ponteiro para o início da lista encadeada de transportes
 */
void listarPorBateria(transporte* inicio) {
    if (inicio == NULL) {//verificação se a lista está vazia
        printf("Nenhum transporte registado.\n");
        return;
    }
    ordenarPorBateria(inicio);//percorre a lista de transportes e imprime os dados de cada veículo
    while (inicio != NULL){
        printf("ID: %d, Tipo: %d, Localizacao: %s, Custo: %.2f, Bateria: %.2f, Autonomia: %.2f\n", inicio->id, inicio->tipo, inicio->localizacao, inicio->custo, inicio->bat, inicio->aut);
        inicio = inicio->seguinte;
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
    char linha[100];
    int encontrou = 0;
    while(fgets(linha, 100, fp)){
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