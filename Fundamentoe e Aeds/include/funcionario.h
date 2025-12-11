#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#define CARGO_LEN 30
#define MAX_FUNC 300

typedef struct {
    int codigo;
    char nome[100];
    char telefone[20];
    char cargo[CARGO_LEN];
    float salario;
    int active;
} Funcionario;

void funcionarios_inicializar(void);
int carregar_funcionarios_arquivo(void);
int salvar_funcionarios_arquivo(void);
int cadastrar_funcionario(Funcionario f);
int buscar_funcionario_por_codigo(int codigo, Funcionario *out);

#endif
