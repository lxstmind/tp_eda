#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//Inserção de um meio de transporte
transporte* criarTransporte(transporte * inicio, int id, int tipo, char localizacao[], float custo, float bat, float aut){
    //if (!existeGestor(inicio, id)){
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
    //} else return(inicio);
    return inicio;
}

void guardarTransporte(transporte* inicio){
    FILE* fp;
    fp = fopen("transportes.txt","a");
    if (fp!=NULL){
        transporte* aux= inicio;
        fprintf(fp,"%d;%d;%s;%.2f;%.2f;%.2f\n", aux->id, aux-> tipo, aux-> localizacao, aux->custo, aux->bat, aux->aut);
        fclose(fp);
    }
}

transporte* lerTransportes(){
    FILE* fp;
    fp = fopen("transportes.txt","r");
    transporte* aux = NULL;

    if (fp!=NULL){
        int id, tipo;
        char localizacao[MAX_MORADA_LENGTH + 1];
        float custo, bat, aut;

        while (!feof(fp)) { 
            fscanf(fp, "%d;%d;%[^;];%f;%f;%f\n", &id, &tipo, &localizacao, &custo, &bat, &aut);
            aux = criarTransporte(aux, id, tipo, localizacao, custo, bat, aut);
        }

        fclose(fp);
    }

    return aux;
}

void ordenarPorBateria(transporte* inicio) {
    int trocado = 1;
    while (trocado) {
        trocado = 0;
        transporte* anterior = NULL;
        transporte* atual = inicio;
        while (atual->seguinte != NULL) {
            if (atual->bat < atual->seguinte->bat) {
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

void listarPorBateria(transporte* inicio) {
    if (inicio == NULL) {
        printf("Nenhum transporte registado.\n");
        return;
    }
    ordenarPorBateria(inicio);
    while (inicio != NULL){
        printf("ID: %d, Tipo: %d, Localizacao: %s, Custo: %.2f, Bateria: %.2f, Autonomia: %.2f\n", inicio->id, inicio->tipo, inicio->localizacao, inicio->custo, inicio->bat, inicio->aut);
        inicio = inicio->seguinte;
    }
}

void alterarDadosTransporte(transporte* inicio, int id) {
    transporte* aux = inicio;
    int opcao;

    while (aux != NULL) {
        if (aux->id == id) {
            printf("Dados atuais:\n");
            printf("ID: %d, Tipo: %d, Localizacao: %s, Custo: %.2f, Bateria: %.2f, Autonomia: %.2f\n", aux->id, aux -> tipo, aux->localizacao, aux->custo, aux->bat, aux->aut);
            printf("\nDigite o número correspondente à opção que deseja alterar:\n");
            printf("1 - Tipo\n2 - Localizacao\n3 - Custo\n4 - Bateria\n5 - Autonomia\n0 - Sair\n");

            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o novo tipo: ");
                    scanf("%d", aux->tipo);
                    printf("Nome alterado com sucesso!\n");
                    break;

                case 2:
                    printf("Digite a nova localizacao: ");
                    scanf("%s", aux->localizacao);
                    printf("Password alterada com sucesso!\n");
                    break;

                case 3:
                    printf("Digite o novo custo: ");
                    scanf("%f", &aux->custo);
                    printf("NIF alterado com sucesso!\n");
                    break;

                case 4:
                    printf("Digite a nova bateria: ");
                    scanf("%f", aux->bat);
                    printf("Morada alterada com sucesso!\n");
                    break;

                case 5:
                    printf("Digite a nova autonomia: ");
                    scanf("%f", &aux->aut);
                    printf("Saldo alterado com sucesso!\n");
                    break;

                case 0:
                    printf("Saindo...\n");
                    return;

                default:
                    printf("Opcaoo invalida.\n");
            }
        break;
        }
        aux = aux->seguinte;
    }

    if (aux == NULL) {
        printf("Transporte nao encontrado.\n");
    }
}

transporte* removerTransporte(transporte* inicio, int id) {
    transporte *anterior=inicio, *atual=inicio, *aux;

    if (atual==NULL) return(NULL);
    else if (atual->id == id){ // remoção do 1º registo
    aux = atual->seguinte;
    free(atual);
    return(aux);
    }
    else
    { while ((atual!=NULL)&&(atual->id!=id)) 
    {anterior = atual;
    atual = atual->seguinte;
    }
    if (atual==NULL) return(inicio);
    else
    {anterior->seguinte = atual->seguinte;
    free(atual);
    return(inicio);
    }
    }
}