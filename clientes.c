#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/**
 * @brief id do proximo cliente registado
 * 
 * @param inicio ponteiro para o inicio da lista ligada
 * @return int inteiro do id que representa o proximo cliente
 */
int atribuirIdCliente(cliente * inicio){
    while (inicio != NULL) {
        if (inicio->seguinte == NULL) {
            return inicio->id + 1;
        }

        inicio = inicio->seguinte;
    }

    return 1;
}

/**
 * @brief retorna os dados dos clientes para o ponteiro inicio
 * 
 * @param inicio ponteiro para o inicio da lista ligada
 * @param id inteiro do id que representa o novo cliente
 * @param password string que representa a password da conta cliente
 * @param nome string que representa o nome do cliente
 * @param nif inteiro que representa o nif do cliente
 * @param morada string que representa a morada do cliente
 * @param saldo numero que representa o saldo da conta do cliente
 * @return cliente* ponteiro para o novo nó criado da lista de clientes
 */
cliente* criarContaCliente(cliente * inicio, int id, char password[], char nome[], int nif, char morada[], float saldo){
        cliente * novo = malloc(sizeof(struct cliente));
        if (novo != NULL) {
            novo->id = id;
            strcpy(novo->password, password);
            strcpy(novo->nome, nome);
            novo->nif = nif;
            strcpy(novo->morada, morada);
            novo->saldo = saldo;
            novo->seguinte = inicio;
            return(novo);
        }
    return(inicio);
}

/**
 * @brief percorre a lista de clientes até encontrar um cliente com o mesmo id e senha. se encontrar um cliente correspondente, retorna o seu id, caso contrário, retorna 0
 * 
 * @param inicio ponteiro para o inicio da lista ligada
 * @param id inteiro do id que representa o cliente
 * @param password string que representa a password da conta cliente
 * @return int inteiro que representa o ID do cliente correspondente, se encontrado, caso contrário, 0
 */
int verifLoginCliente(cliente* inicio, int id, char password[]) {
    while (inicio != NULL) {
        if (inicio->id == id && strcmp(inicio->password, password) == 0) {
            return inicio->id;
        }
        inicio = inicio->seguinte;
    }
    return 0;
}

/**
 * @brief recebe o ponteiro para o inicio de uma lista de clientes e abre o ficheiro em modo de edição e percorre a lista para escrever os dados no ficheiro de texto
 * 
 * @param inicio ponteiro para o início de uma lista de clientes a serem salvos no ficheiro de texto
 */
void guardarCliente(cliente* inicio){
    FILE* fp;
    fp = fopen("clientes.txt","a");
    if (fp!=NULL){
        cliente* aux= inicio;
        fprintf(fp,"%d;%s;%s;%d;%s;%.2f\n", aux->id, aux->nome, aux->password, aux->nif, aux->morada, aux->saldo);
        fclose(fp);
    }
}

/**
 * @brief lê as informações sobre os clientes e retorna um ponteiro para o inicio da lista de clientes lidos. depois cria uma nova conta de cliente na lista
 * 
 * @return cliente* ponteiro para o início da lista de clientes criada a partir do ficheiro de texto
 */
cliente* lerClientes() {
    FILE* fp;
    fp = fopen("clientes.txt", "r");
    cliente* inicio = NULL;

    if (fp != NULL) {
        int id, nif;
        char nome[MAX_NAME_LENGTH + 1], password[MAX_PASSWORD_LENGTH + 1], morada[MAX_MORADA_LENGTH + 1];
        float saldo;

        while (fscanf(fp, "%d;%[^;];%[^;];%d;%[^;];%f\n", &id, nome, password, &nif, morada, &saldo) == 6) {
            inicio = criarContaCliente(inicio, id, password, nome, nif, morada, saldo);
        }

        fclose(fp);
    }

    return inicio;
}

/**
 * @brief listar na consola o conteúdo da lista ligada
 * 
 * @param inicio ponteiro para o início da lista encadeada de clientes
 */
void listarClientes(cliente* inicio){
    while (inicio != NULL){
        printf("ID: %d, Nome: %s, Password: %s, NIF: %d, Morada: %s, Saldo: %.2f\n", inicio->id, inicio->nome, inicio->password, inicio->nif, inicio->morada, inicio->saldo);
        inicio = inicio->seguinte;
    }
}

/**
 * @brief permite ao gestor e aos clientes a alteração dos dados dos clientes
 * 
 * @param inicio ponteiro para o início da lista encadeada de clientes
 * @param id id do cliente a ser alterado
 */
void alterarDadosCliente(cliente* inicio, int id) {
    cliente* clienteAtual = buscarCliente(inicio, id);
    if (clienteAtual == NULL) {
        printf("Erro: cliente nao encontrado.\n");
        return;
    }

    int opcao;
    do {
        printf("Escolha o que deseja alterar:\n");
        printf("1 - Nome: %s\n", clienteAtual->nome);
        printf("2 - NIF: %d\n", clienteAtual->nif);
        printf("3 - Morada: %s\n", clienteAtual->morada);
        printf("4 - Senha\n");
        printf("5 - Saldo: %.2f\n", clienteAtual->saldo);
        printf("0 - Confirmar alteracao de dados e sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Qual o seu novo nome?\n");
                scanf("%s", clienteAtual->nome);
                break;
            case 2:
                do {
                    printf("Qual o seu novo NIF?\n");
                    scanf("%d", &clienteAtual->nif);

                    if (clienteAtual->nif <= 0 || clienteAtual->nif < 100000000 || clienteAtual->nif > 999999999) {
                        printf("Erro: o NIF deve ser um numero positivo e ter 9 digitos.\n");
                    }
                } while (clienteAtual->nif <= 0 || clienteAtual->nif < 100000000 || clienteAtual->nif > 999999999);
                break;
            case 3:
                printf("Qual a sua nova morada?\n");
                scanf("%s", clienteAtual->morada);
                break;
            case 4:
                printf("Qual a sua nova senha?\n");
                scanf("%s", clienteAtual->password);
                break;
            case 5:
                do {
                    printf("Qual o seu novo saldo?\n");
                    scanf("%f", &clienteAtual->saldo);

                    if (clienteAtual->saldo < 0) {
                        printf("Erro: o saldo deve ser positivo.\n");
                    }
                } while (clienteAtual->saldo < 0);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);

    // atualiza os dados do arquivo
    FILE* fp = fopen("clientes.txt", "w+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // escreve todos os clientes atualizados no arquivo
    while (inicio != NULL) {
        fprintf(fp, "%d;%s;%s;%d;%s;%.2f\n", inicio->id, inicio->nome, inicio->password, inicio->nif, inicio->morada, inicio->saldo);
        inicio = inicio->seguinte;
    }

    fclose(fp);

    printf("Dados do cliente atualizados com sucesso!\n");
}

/**
 * @brief buscar um cliente com um determinado ID em uma lista encadeada de clientes
 * 
 * @param inicio ponteiro para o início da lista encadeada de clientes
 * @param id ID do cliente a ser buscado
 * @return cliente* ponteiro para o cliente com o ID correspondente, caso ele seja encontrado na lista
 */
cliente* buscarCliente(cliente* inicio, int id) {
    cliente* aux = inicio;

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
 * @brief recebe um ponteiro para uma estrutura cliente e imprime as informações desse cliente na consola
 * 
 * @param c ponteiro que aponta para um único cliente que será impresso na função
 */
void imprimirCliente(cliente* c) {
    printf("ID: %d, Nome: %s, Password: %s, NIF: %d, Morada: %s, Saldo: %.2f\n", c->id, c->nome, c->password, c->nif, c->morada, c->saldo);
}

/**
 * @brief recebe um ID do gestor para remover o cliente de um ficheiro de texto
 * 
 */
void removerCliente(){
    int idRemover;
    printf("Informe o ID do cliente a ser removido: ");
    scanf("%d", &idRemover);

    // Abre o arquivo para leitura
    FILE* fp = fopen("clientes.txt", "r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo de clientes!\n");
        return;
    }

    // Abre um arquivo temporário para escrita
    FILE* fpTemp = fopen("temp.txt", "w");
    if(fpTemp == NULL){
        printf("Erro ao criar arquivo temporário!\n");
        fclose(fp);
        return;
    }

    // Percorre o arquivo de clientes linha por linha
    char linha[200];
    int encontrou = 0;
    while(fgets(linha, 200, fp)){
        // Cria um novo cliente a partir da linha atual
        cliente* cli = malloc(sizeof(cliente));
        sscanf(linha, "%d;%[^;];%[^;];%d;%[^;];%f", &cli->id, cli->password, cli->nome, &cli->nif, cli->morada, &cli->saldo);

        // Se o ID for diferente do ID a ser removido, escreve a linha no arquivo temporário
        if(cli->id != idRemover){
            fputs(linha, fpTemp);
        } else {
            encontrou = 1;
            free(cli);
        }
    }

    // Fecha os arquivos
    fclose(fp);
    fclose(fpTemp);

    // Remove o arquivo antigo
    remove("clientes.txt");

    // Renomeia o arquivo temporário para o nome original
    rename("temp.txt", "clientes.txt");

    if(encontrou){
        printf("Cliente removido com sucesso!\n");
    } else {
        printf("Cliente não encontrado!\n");
    }
}