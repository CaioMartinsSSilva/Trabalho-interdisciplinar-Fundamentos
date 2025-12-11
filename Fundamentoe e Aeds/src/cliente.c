#include <stdio.h>
#include <string.h>
#include "cliente.h"

static Cliente clientes[MAX_CLIENTES];

void clientes_inicializar(void) {
    for (int i = 0; i < MAX_CLIENTES; i++) clientes[i].active = 0;
}

int carregar_clientes_arquivo(void) {
    FILE *f = fopen("data/clientes.bin", "rb");
    if (!f) return 0;
    fread(clientes, sizeof(Cliente), MAX_CLIENTES, f);
    fclose(f);
    return 1;
}

int salvar_clientes_arquivo(void) {
    FILE *f = fopen("data/clientes.bin", "wb");
    if (!f) return 0;
    fwrite(clientes, sizeof(Cliente), MAX_CLIENTES, f);
    fclose(f);
    return 1;
}

int buscar_cliente_por_codigo(int codigo, Cliente *out) {
    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (clientes[i].active && clientes[i].codigo == codigo) {
            if (out) *out = clientes[i];
            return 1;
        }
    }
    return 0;
}

int cadastrar_cliente(Cliente c) {
    if (buscar_cliente_por_codigo(c.codigo, NULL)) return -1; /* duplicado */
    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (!clientes[i].active) {
            clientes[i] = c;
            clientes[i].active = 1;
            salvar_clientes_arquivo();
            return 0;
        }
    }
    return -2; /* cheio */
}
