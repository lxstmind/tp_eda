#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//retorna os dados dos clientes para o ponteiro inicio
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

//percorre a lista de clientes até encontrar um cliente com o mesmo id e senha. se encontrar um cliente correspondente, retorna o seu id, caso contrário, retorna 0.
int verifLoginCliente(cliente* inicio, int id, char password[]) {
    while (inicio != NULL) {
        if (inicio->id == id && strcmp(inicio->password, password) == 0) {
            return inicio->id;
        }
        inicio = inicio->seguinte;
    }
    return 0;
}

//recebe o ponteiro para o inicio de uma lista de clientes e abre o ficheiro em modo de edição e percorre a lista para escrever os dados no txt
void guardarCliente(cliente* inicio){
    FILE* fp;
    fp = fopen("clientes.txt","a");
    if (fp!=NULL){
        cliente* aux= inicio;
        fprintf(fp,"%d;%s;%s;%d;%s;%.2f\n", aux->id, aux->nome, aux->password, aux->nif, aux->morada, aux->saldo);
        fclose(fp);
    }
}

//lê as informações sobre os clientes e retorna um ponteiro para o inicio da lista de clientes lidos. depois cria uma nova conta de cliente na lista.
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

// listar na consola o conteúdo da lista ligada
void listarClientes(cliente* inicio){
    while (inicio != NULL){
        printf("ID: %d, Nome: %s, Password: %s, NIF: %d, Morada: %s, Saldo: %.2f\n", inicio->id, inicio->nome, inicio->password, inicio->nif, inicio->morada, inicio->saldo);
        inicio = inicio->seguinte;
    }
}

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

void imprimirCliente(cliente* c) {
    printf("ID: %d, Nome: %s, Password: %s, NIF: %d, Morada: %s, Saldo: %.2f\n", c->id, c->nome, c->password, c->nif, c->morada, c->saldo);
}

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


void removerCliente(int idCliente) {
    FILE *arquivo, *arquivoTemporario;
    cliente clienteAtual;
    long tamanhoCliente = sizeof(clienteAtual);

    arquivo = fopen("clientes.txt", "rb");
    arquivoTemporario = fopen("clientesTemp.txt", "wb");

    if (arquivo == NULL || arquivoTemporario == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    while (fread(&clienteAtual, tamanhoCliente, 1, arquivo)) {
        if (clienteAtual.id != idCliente) {
            fwrite(&clienteAtual, tamanhoCliente, 1, arquivoTemporario);
        }
    }

    fclose(arquivo);
    fclose(arquivoTemporario);

    if (remove("clientes.txt") != 0) {
        printf("Erro ao remover o arquivo original!\n");
        return;
    }

    if (rename("clientesTemp.txt", "clientes.txt") != 0) {
        printf("Erro ao renomear o arquivo temporario!\n");
        return;
    }

    printf("Cliente com ID %d removido do arquivo!\n", idCliente);
}