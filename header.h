#ifndef HEADER_H_
#define HEADER_H_
#define MAX_PASSWORD_LENGTH 32
#define MAX_NAME_LENGTH 64
#define MAX_MORADA_LENGTH 64
#define MAX_LOCAL_LENGTH 64

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
void menuClienteLogin();
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
void alugar_transporte(transporte* lista_transportes, int id_transporte, float *saldo);

#endif