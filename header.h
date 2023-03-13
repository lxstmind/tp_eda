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

typedef struct veiculo{
    int id;
    int tipo;
    float custo;
    float bateria;
    float distancia;
    char local[MAX_LOCAL_LENGTH +1];
    struct veiculo* seguinte; 
}veiculo;

typedef struct cliente{
    int id;
    char password[MAX_PASSWORD_LENGTH + 1]; // +1 para o caractere nulo
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
    float bat;
    float aut;
    struct transporte* seguinte;
}transporte;

void menu();
void clear_console();
int getId();

void menuCliente();
cliente* criarContaCliente(cliente * inicio, int id, char password[], char nome[], int nif, char morada[], float saldo); // Inserção de um novo registo de um cliente
void existeCliente(cliente* inicio, int id);
int verifLoginCliente(cliente* inicio, int id, char password[]);
void guardarCliente(cliente* inicio);
cliente* lerClientes();
void listarClientes(cliente* inicio);

void menuGestor();
gestor* criarContaGestor(gestor * inicio, int id, char password[], char nome[]); // Inserção de um novo registo de um gestor
void existeGestor(gestor* inicio, int id);
int verifLoginGestor(gestor* inicio, int id, char password[]);
void guardarGestor(gestor* inicio);
gestor* lerGestores();

void menuGestorLogin();
transporte* criarTransporte(transporte * inicio, int id, int tipo, float bat, float aut);
void guardarTransporte(transporte* inicio);
void listarTransportes(transporte* inicio);
transporte* lerTransportes();

#endif