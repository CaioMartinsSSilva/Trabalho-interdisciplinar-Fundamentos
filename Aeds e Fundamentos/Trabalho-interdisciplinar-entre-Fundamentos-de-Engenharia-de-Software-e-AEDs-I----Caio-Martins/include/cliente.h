#ifndef CLIENTE_H
#define CLIENTE_H
#define NOME_LEN 100
#define END_LEN 120
#define TEL_LEN 20
#define MAX_CLIENTES 500
typedef struct {
    int codigo;
    char nome[NOME_LEN];
    char endereco[END_LEN];
    char telefone[TEL_LEN];
    int active;
} Cliente;
void clientes_inicializar(void);
int carregar_clientes_arquivo(void);
int salvar_clientes_arquivo(void);
int cadastrar_cliente(Cliente c);
int buscar_cliente_por_codigo(int codigo, Cliente *out);
#endif
