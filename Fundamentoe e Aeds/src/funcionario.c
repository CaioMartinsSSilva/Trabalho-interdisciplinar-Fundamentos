#include <stdio.h>
#include "funcionario.h"

static Funcionario funcionarios[MAX_FUNC];

void funcionarios_inicializar(void) {
    for (int i = 0; i < MAX_FUNC; i++) funcionarios[i].active = 0;
}

int carregar_funcionarios_arquivo(void) {
    FILE *f = fopen("data/funcionarios.bin", "rb");
    if (!f) return 0;
    fread(funcionarios, sizeof(Funcionario), MAX_FUNC, f);
    fclose(f);
    return 1;
}

int salvar_funcionarios_arquivo(void) {
    FILE *f = fopen("data/funcionarios.bin", "wb");
    if (!f) return 0;
    fwrite(funcionarios, sizeof(Funcionario), MAX_FUNC, f);
    fclose(f);
    return 1;
}

int buscar_funcionario_por_codigo(int codigo, Funcionario *out) {
    for (int i = 0; i < MAX_FUNC; i++) {
        if (funcionarios[i].active && funcionarios[i].codigo == codigo) {
            if (out) *out = funcionarios[i];
            return 1;
        }
    }
    return 0;
}

int cadastrar_funcionario(Funcionario f) {
    if (buscar_funcionario_por_codigo(f.codigo, NULL)) return -1;
    for (int i = 0; i < MAX_FUNC; i++) {
        if (!funcionarios[i].active) {
            funcionarios[i] = f;
            funcionarios[i].active = 1;
            salvar_funcionarios_arquivo();
            return 0;
        }
    }
    return -2;
}
