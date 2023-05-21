#ifndef HEADER_H_
#define HEADER_H_
#define MAX_PASSWORD_LENGTH 32
#define MAX_NAME_LENGTH 64
#define MAX_MORADA_LENGTH 64
#define MAX_LOCAL_LENGTH 64
#define TAM 50
#include <time.h>

typedef struct {
    int dia;
    int mes;
    int ano;
}data;

typedef struct cliente{
    int id;
    char password[MAX_PASSWORD_LENGTH + 1]; // +1 para o \n
    char nome[MAX_NAME_LENGTH + 1];
    int nif;
    char morada[MAX_MORADA_LENGTH +1];
    float saldo;
    struct viagem* viagens;
    struct cliente* seguinte;
}cliente;

typedef struct gestor{
    int id;
    char password[MAX_PASSWORD_LENGTH + 1];
    char nome[MAX_NAME_LENGTH + 1];
    struct gestor* seguinte;
}gestor;

typedef struct transporte{
    int id;
    int tipo;
    char localizacao[MAX_MORADA_LENGTH + 1];
    float custo;
    float bat;
    float aut;
    struct transporte* seguinte;
}transporte;

typedef struct viagem {
    int id_transporte;
    float preco;
    struct data {
        int dia;
        int mes;
        int ano;
    } data;
    struct viagem* seguinte;
}viagem;

typedef struct alugar{
    int id_transporte;
    time_t data_inicio;
    time_t data_fim;
}alugar;

void menu();
void clear_console();
void menuCliente();
cliente* criarContaCliente(cliente * inicio, int id, char password[], char nome[], int nif, char morada[], float saldo);
int verifLoginCliente(cliente* inicio, int id, char password[]);
void guardarCliente(cliente* inicio);
cliente* lerClientes();
void listarClientes(cliente* inicio);
void menuGestor();
gestor* criarContaGestor(gestor * inicio, int id, char password[], char nome[]);
int verifLoginGestor(gestor* inicio, int id, char password[]);
void guardarGestor(gestor* inicio);
gestor* lerGestores();
void menuGestorLogin();
transporte* criarTransporte(transporte * inicio, int id, int tipo, char localizacao[], float custo, float bat, float aut);
void guardarTransporte(transporte* inicio);
transporte* lerTransportes();
void ordenarPorAutonomia(transporte* inicio);
void listarPorAutonomia(transporte* inicio);
void ordenarPorLocalizacao(transporte* inicio, char* localizacao);
void listarPorLocalizacao(transporte* inicio, char* localizacao);
void menuClienteLogin(int idLogin);
void alterarDadosCliente(cliente* inicio, int id);
void alterarDadosTransporte(transporte* inicio, int id);
void imprimirCliente(cliente* c);
cliente* buscarCliente(cliente* inicio, int id);
void alterarDadosTransporte(transporte* inicio, int id);
transporte* buscarTransporte(transporte* inicio, int id);
void imprimirTransporte(transporte* t);
void removerTransporte();
void removerCliente();
void alterarDadosGestor(gestor* inicio, int id);
gestor* buscarGestor(gestor* inicio, int id);
void imprimirGestor(gestor* g);
void removerGestor();
void alugarTransporte(transporte* inicioTransporte, cliente* inicioCliente, int id_transporte, cliente* cliente_atual);

// F A S E   2

typedef struct registo3
{ int codigo;
  struct registo3 * seguinte;
} * Meios;

// Representação de um grafo orientado e pesado
typedef struct registo2
{char vertice[TAM]; // geocódigo what3words
 float peso;
 struct registo2 * seguinte;
} * Adjacente;

typedef struct registo1
{char vertice[TAM]; // geocódigo what3words
 Adjacente adjacentes;
 Meios meios; // Lista ligada com os códigos dos meios de transporte existente
	      // neste geocódigo
 struct registo1 * seguinte;
} * Grafo;

// Protótipos

// Criar um novo vértice
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarVertice(Grafo *g, char novoId[]);
// Criar uma nova aresta
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarAresta(Grafo g, char vOrigem[], char vDestino[], float peso);
int existeVertice(Grafo g, char vertice[]);
void listarAdjacentes(Grafo g, char vertice[]);
// Inserir meio de transporte na localização com geocódigo passado por parâmetro
void removerLocalizacao();
void removerAresta();
void listarArestasPorPonto(const char* ponto);

#endif