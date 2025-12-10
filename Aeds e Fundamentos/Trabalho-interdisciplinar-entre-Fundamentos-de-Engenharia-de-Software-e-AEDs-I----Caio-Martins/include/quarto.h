#ifndef QUARTO_H
#define QUARTO_H
#define MAX_QUARTOS 500
typedef struct {
    int numero;
    int capacidade;
    float valor_diaria;
    int status;
    int active;
} Quarto;
void quartos_inicializar(void);
int carregar_quartos_arquivo(void);
int salvar_quartos_arquivo(void);
int cadastrar_quarto(Quarto q);
int buscar_quarto_por_numero(int numero, Quarto *out);
int atualizar_status_quarto(int numero, int status);
#endif
