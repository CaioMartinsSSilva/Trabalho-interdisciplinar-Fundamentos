#include <stdio.h>
#include <string.h>
#include "quarto.h"

static Quarto quartos[MAX_QUARTOS];

void quartos_inicializar(void) {
    for (int i = 0; i < MAX_QUARTOS; i++) { quartos[i].active = 0; quartos[i].status = 0; }
}

int carregar_quartos_arquivo(void) {
    FILE *f = fopen("data/quartos.bin", "rb");
    if (!f) return 0;
    fread(quartos, sizeof(Quarto), MAX_QUARTOS, f);
    fclose(f);
    return 1;
}

int salvar_quartos_arquivo(void) {
    FILE *f = fopen("data/quartos.bin", "wb");
    if (!f) return 0;
    fwrite(quartos, sizeof(Quarto), MAX_QUARTOS, f);
    fclose(f);
    return 1;
}

int buscar_quarto_por_numero(int numero, Quarto *out) {
    for (int i = 0; i < MAX_QUARTOS; i++) {
        if (quartos[i].active && quartos[i].numero == numero) {
            if (out) *out = quartos[i];
            return 1;
        }
    }
    return 0;
}

int cadastrar_quarto(Quarto q) {
    if (buscar_quarto_por_numero(q.numero, NULL)) return -1; /* duplicado */
    for (int i = 0; i < MAX_QUARTOS; i++) {
        if (!quartos[i].active) {
            quartos[i] = q;
            quartos[i].active = 1;
            quartos[i].status = 0;
            salvar_quartos_arquivo();
            return 0;
        }
    }
    return -2;
}

int atualizar_status_quarto(int numero, int status) {
    for (int i = 0; i < MAX_QUARTOS; i++) {
        if (quartos[i].active && quartos[i].numero == numero) {
            quartos[i].status = status;
            salvar_quartos_arquivo();
            return 1;
        }
    }
    return 0;
}
