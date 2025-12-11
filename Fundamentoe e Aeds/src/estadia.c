#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "estadia.h"
#include "cliente.h"
#include "quarto.h"

static Estadia estadias[MAX_ESTADIAS];

void estadias_inicializar(void) {
    for (int i = 0; i < MAX_ESTADIAS; i++) estadias[i].active = 0;
}

int carregar_estadias_arquivo(void) {
    FILE *f = fopen("data/estadias.bin", "rb");
    if (!f) return 0;
    fread(estadias, sizeof(Estadia), MAX_ESTADIAS, f);
    fclose(f);
    return 1;
}

int salvar_estadias_arquivo(void) {
    FILE *f = fopen("data/estadias.bin", "wb");
    if (!f) return 0;
    fwrite(estadias, sizeof(Estadia), MAX_ESTADIAS, f);
    fclose(f);
    return 1;
}

static int date_valid(const char *d) {
    if (!d) return 0;
    if (strlen(d) != 10) return 0;
    if (d[4] != '-' || d[7] != '-') return 0;
    return 1;
}

static int days_between(const char *a, const char *b) {
    struct tm ta = {0}, tb = {0};
    if (!strptime(a, "%Y-%m-%d", &ta)) return -9999;
    if (!strptime(b, "%Y-%m-%d", &tb)) return -9999;
    time_t ta_t = mktime(&ta);
    time_t tb_t = mktime(&tb);
    double diff = difftime(tb_t, ta_t);
    int days = (int)(diff / (24*3600) + 0.5);
    return days;
}

static int overlap(const char *ent1, const char *sai1, const char *ent2, const char *sai2) {
    if (strcmp(sai1, ent2) <= 0) return 0;
    if (strcmp(ent1, sai2) >= 0) return 0;
    return 1;
}

static int quarto_disponivel_para_periodo(int capacidade, const char *entrada, const char *saida, int *numero_quarto_out) {
    Quarto arr[MAX_QUARTOS]; memset(arr, 0, sizeof(arr));
    FILE *fq = fopen("data/quartos.bin", "rb");
    if (fq) { fread(arr, sizeof(Quarto), MAX_QUARTOS, fq); fclose(fq); }

    Estadia est_arr[MAX_ESTADIAS]; memset(est_arr, 0, sizeof(est_arr));
    FILE *fe = fopen("data/estadias.bin", "rb");
    if (fe) { fread(est_arr, sizeof(Estadia), MAX_ESTADIAS, fe); fclose(fe); }

    for (int i = 0; i < MAX_QUARTOS; i++) {
        if (!arr[i].active) continue;
        if (arr[i].capacidade < capacidade) continue;
        if (arr[i].status == 1) continue;
        int conflito = 0;
        for (int j = 0; j < MAX_ESTADIAS; j++) {
            if (!est_arr[j].active) continue;
            if (est_arr[j].numero_quarto != arr[i].numero) continue;
            if (overlap(entrada, saida, est_arr[j].data_entrada, est_arr[j].data_saida)) {
                conflito = 1; break;
            }
        }
        if (!conflito) {
            if (numero_quarto_out) *numero_quarto_out = arr[i].numero;
            return 1;
        }
    }
    return 0;
}

int cadastrar_estadia(int codigo_cliente, int qtd_hospedes,
                      const char *data_entrada, const char *data_saida,
                      Estadia *saida_estadia) {
    Cliente c;
    if (!buscar_cliente_por_codigo(codigo_cliente, &c)) return -1;
    if (!date_valid(data_entrada) || !date_valid(data_saida)) return -2;
    if (strcmp(data_entrada, data_saida) >= 0) return -2;
    int num_quarto = 0;
    if (!quarto_disponivel_para_periodo(qtd_hospedes, data_entrada, data_saida, &num_quarto)) return -3;
    int dias = days_between(data_entrada, data_saida);
    if (dias <= 0) dias = 1;
    for (int i = 0; i < MAX_ESTADIAS; i++) {
        if (!estadias[i].active) {
            estadias[i].codigo_estadia = i + 1;
            strncpy(estadias[i].data_entrada, data_entrada, DATE_LEN-1);
            strncpy(estadias[i].data_saida, data_saida, DATE_LEN-1);
            estadias[i].qtd_diarias = dias;
            estadias[i].codigo_cliente = codigo_cliente;
            estadias[i].numero_quarto = num_quarto;
            estadias[i].active = 1;
            atualizar_status_quarto(num_quarto, 1);
            salvar_estadias_arquivo();
            if (saida_estadia) *saida_estadia = estadias[i];
            return 0;
        }
    }
    return -4;
}
