#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/**
 * @brief id do proximo gestor registado
 * 
 * @param inicio ponteiro para o inicio da lista ligada
 * @return int inteiro do id que representa o proximo gestor
 */
int atribuirIdGestores(gestor * inicio){
    while (inicio != NULL) {
        if (inicio->seguinte == NULL) {
            return inicio->id + 1;
        }

        inicio = inicio->seguinte;
    }

    return 1;
}

/**
 * @brief retorna os dados dos gestores para o ponteiro inicio
 * 
 * @param inicio ponteiro para o inicio da lista ligada
 * @param id inteiro que representa o id do gestor
 * @param password string que representa a password da conta gestor
 * @param nome string que representa o nome do gestor
 * @return gestor* ponteiro para o novo nó criado da lista de gestores
 */
gestor* criarContaGestor(gestor * inicio, int id, char password[], char nome[]){
        gestor * novo = malloc(sizeof(struct gestor));
        if (novo != NULL) {
            novo->id = id;
            strcpy(novo->password, password);
            strcpy(novo->nome, nome);
            novo->seguinte = inicio;
            return novo;
        }
    return inicio;
}

/**
 * @brief percorre a lista de gestores até encontrar um gestor com o mesmo id e senha. se encontrar um gestor correspondente, retorna o seu id, caso contrário, retorna 0
 * 
 * @param inicio ponteiro para o inicio da lista ligada
 * @param id inteiro do id que representa o gestor
 * @param password string que representa a password da conta de gestor
 * @return int inteiro que representa o ID do gestor correspondente, se encontrado, caso contrário, 0
 */
int verifLoginGestor(gestor* inicio, int id, char password[]) {
    while (inicio != NULL) {
        if (inicio->id == id && strcmp(inicio->password, password) == 0) {
            return inicio->id;
        }
        inicio = inicio->seguinte;
    }
    return 0;
}

/**
 * @brief recebe o ponteiro para o inicio de uma lista de gestores e abre o ficheiro em modo de edição e percorre a lista para escrever os dados no ficheiro de texto
 * 
 * @param inicio ponteiro para o início de uma lista de gestores a serem salvos no ficheiro de texto
 */
void guardarGestor(gestor* inicio){
    FILE* fp;
    fp = fopen("gestores.txt","a");
    if (fp!=NULL){
        gestor* aux = inicio;
        fprintf(fp, "%d;%s;%s\n", aux->id, aux->nome, aux->password);
        fclose(fp);
    }
}

/**
 * @brief lê as informações sobre os gestores e retorna um ponteiro para o inicio da lista de gestores lidos. depois cria uma nova conta de gestor na lista
 * 
 * @return gestor* ponteiro para o início da lista de gestores criada a partir do ficheiro de texto
 */
gestor* lerGestores(){
    FILE* fp;
    fp = fopen("gestores.txt","r");
    gestor* aux = NULL;

    if (fp!=NULL){
        int id;
        char nome[MAX_NAME_LENGTH + 1], password[MAX_PASSWORD_LENGTH + 1];

        while (!feof(fp)) { 
            fscanf(fp, "%d;%[^;];%[^\n]\n", &id, &nome, &password);
            aux = criarContaGestor(aux, id, password, nome);
        }

        fclose(fp);
    }

    return aux;
}

/**
 * @brief permite ao gestor a alteração dos dados dos gestores
 * 
 * @param inicio ponteiro para o início da lista encadeada de gestores
 * @param id id do gestor a ser alterado
 */
void alterarDadosGestor(gestor* inicio, int id) {
    gestor* gestorAtual = buscarGestor(inicio, id);
    if (gestorAtual == NULL) {
        printf("Erro: gestor nao encontrado.\n");
        return;
    }

    int opcao;
    do {
        printf("Escolha o que deseja alterar:\n");
        printf("1 - Nome: %s\n", gestorAtual->nome);
        printf("2 - Senha\n");
        printf("0 - Confirmar alteracao de dados e sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Qual o seu novo nome?\n");
                scanf("%s", gestorAtual->nome);
                break;
            case 2:
                printf("Qual a sua nova senha?\n");
                scanf("%s", gestorAtual->password);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);

    // atualiza os dados do arquivo
    FILE* fp = fopen("gestores.txt", "w+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // escreve todos os gestores atualizados no arquivo
    while (inicio != NULL) {
        fprintf(fp, "%d;%s;%s\n", inicio->id, inicio->nome, inicio->password);
        inicio = inicio->seguinte;
    }

    fclose(fp);

    printf("Dados do gestor atualizados com sucesso!\n");
}

/**
 * @brief buscar um gestor com um determinado ID em uma lista encadeada de gestores
 * 
 * @param inicio ponteiro para o início da lista encadeada de gestores
 * @param id ID do gestor a ser buscado
 * @return gestor* ponteiro para o gestor com o ID correspondente, caso ele seja encontrado na lista
 */
gestor* buscarGestor(gestor* inicio, int id) {
    gestor* aux = inicio;

    while (aux != NULL) {
        if (aux->id == id) {
            return aux;
        }
        aux = aux->seguinte;
    }

    // se chegou aqui, o gestor não foi encontrado
    return NULL;
}

/**
 * @brief recebe um ponteiro para uma estrutura gestor e imprime as informações desse gestor na consola
 * 
 * @param g ponteiro que aponta para um único gestor que será impresso na função
 */
void imprimirGestor(gestor* g) {
    printf("ID: %d, Nome: %s, Password: %s\n", g->id, g->nome, g->password);
}

/**
 * @brief recebe um ID para remover o gestor de um ficheiro de texto
 * 
 */
void removerGestor(){
    int idRemover;
    printf("Informe o ID do gestor a ser removido: ");
    scanf("%d", &idRemover);

    // Abre o arquivo para leitura
    FILE* fp = fopen("gestores.txt", "r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo de gestores!\n");
        return;
    }

    // Abre um arquivo temporário para escrita
    FILE* fpTemp = fopen("temp.txt", "w");
    if(fpTemp == NULL){
        printf("Erro ao criar arquivo temporário!\n");
        fclose(fp);
        return;
    }

    // Percorre o arquivo de gestores linha por linha
    char linha[200];
    int encontrou = 0;
    while(fgets(linha, 200, fp)){
        // Cria um novo gestor a partir da linha atual
        gestor* gest = malloc(sizeof(gestor));
        sscanf(linha, "%d;%[^;];%[^;]", &gest->id, gest->password, gest->nome);

        // Se o ID for diferente do ID a ser removido, escreve a linha no arquivo temporário
        if(gest->id != idRemover){
            fputs(linha, fpTemp);
        } else {
            encontrou = 1;
            free(gest);
        }
    }

    // Fecha os arquivos
    fclose(fp);
    fclose(fpTemp);

    // Remove o arquivo antigo
    remove("gestores.txt");

    // Renomeia o arquivo temporário para o nome original
    rename("temp.txt", "gestores.txt");

    if(encontrou){
        printf("Gestor removido com sucesso!\n");
    } else {
        printf("Gestor não encontrado!\n");
    }
}