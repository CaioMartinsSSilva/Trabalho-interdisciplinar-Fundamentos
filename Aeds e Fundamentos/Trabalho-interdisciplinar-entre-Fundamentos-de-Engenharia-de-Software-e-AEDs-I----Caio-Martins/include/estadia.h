#ifndef ESTADIA_H
#define ESTADIA_H
#define DATE_LEN 11
#define MAX_ESTADIAS 1000
typedef struct {
    int codigo_estadia;
    char data_entrada[DATE_LEN];
    char data_saida[DATE_LEN];
    int qtd_diarias;
    int codigo_cliente;
    int numero_quarto;
    int active;
} Estadia;
void estadias_inicializar(void);
int carregar_estadias_arquivo(void);
int salvar_estadias_arquivo(void);
int cadastrar_estadia(int codigo_cliente, int qtd_hospedes,
                      const char *data_entrada, const char *data_saida,
                      Estadia *saida_estadia);
#endif
