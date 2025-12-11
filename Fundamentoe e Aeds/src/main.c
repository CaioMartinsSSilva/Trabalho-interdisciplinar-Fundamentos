#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cliente.h"
#include "funcionario.h"
#include "quarto.h"
#include "estadia.h"

void carregar_tudo(void);

static int ler_int(const char *prompt) {
    char buf[64];
    printf("%s", prompt);
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    return atoi(buf);
}

static void leitura_string(const char *prompt, char *out, int maxlen) {
    printf("%s", prompt);
    if (fgets(out, maxlen, stdin)) {
        out[strcspn(out, "\n")] = '\0';
    } else {
        out[0] = '\0';
    }
}

static void cmd_cadastrar_cliente() {
    Cliente c;
    printf("Codigo: "); scanf("%d", &c.codigo); getchar();
    leitura_string("Nome: ", c.nome, sizeof(c.nome));
    leitura_string("Endereco: ", c.endereco, sizeof(c.endereco));
    leitura_string("Telefone: ", c.telefone, sizeof(c.telefone));
    int r = cadastrar_cliente(c);
    if (r==0) printf("Cliente cadastrado com sucesso\n");
    else if (r==-1) printf("Codigo ja existente\n");
    else printf("Erro ao cadastrar cliente\n");
}

static void cmd_cadastrar_funcionario() {
    Funcionario f;
    printf("Codigo: "); scanf("%d", &f.codigo); getchar();
    leitura_string("Nome: ", f.nome, sizeof(f.nome));
    leitura_string("Telefone: ", f.telefone, sizeof(f.telefone));
    leitura_string("Cargo: ", f.cargo, sizeof(f.cargo));
    printf("Salario: "); scanf("%f", &f.salario); getchar();
    int r = cadastrar_funcionario(f);
    if (r==0) printf("Funcionario cadastrado com sucesso\n");
    else if (r==-1) printf("Codigo ja existente\n");
    else printf("Erro ao cadastrar funcionario\n");
}

static void cmd_cadastrar_quarto() {
    Quarto q;
    printf("Numero do quarto: "); scanf("%d", &q.numero); getchar();
    printf("Capacidade: "); scanf("%d", &q.capacidade); getchar();
    printf("Valor diaria: "); scanf("%f", &q.valor_diaria); getchar();
    q.active = 1; q.status = 0;
    int r = cadastrar_quarto(q);
    if (r==0) printf("Quarto cadastrado com sucesso\n");
    else if (r==-1) printf("Numero ja existe\n");
    else printf("Erro ao cadastrar quarto\n");
}

static void cmd_cadastrar_estadia() {
    int cod_cliente = ler_int("Codigo do cliente: ");
    int qtd_hospedes = ler_int("Quantidade de hospedes: ");
    char entrada[11], saida[11];
    printf("Data entrada (YYYY-MM-DD): "); scanf("%10s", entrada);
    printf("Data saida (YYYY-MM-DD): "); scanf("%10s", saida);
    Estadia e;
    int r = cadastrar_estadia(cod_cliente, qtd_hospedes, entrada, saida, &e);
    if (r==0) {
        printf("Estadia criada: codigo=%d quarto=%d diarias=%d\n", e.codigo_estadia, e.numero_quarto, e.qtd_diarias);
    } else {
        printf("Erro ao criar estadia: codigo %d\n", r);
    }
}

int main(void) {
    carregar_tudo();
    int opt = 0;
    do {
        printf("\n--- Hotel Descanso Garantido ---\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Cadastrar Funcionario\n");
        printf("3 - Cadastrar Quarto\n");
        printf("4 - Cadastrar Estadia\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opt) != 1) break;
        getchar();
        if (opt==1) cmd_cadastrar_cliente();
        else if (opt==2) cmd_cadastrar_funcionario();
        else if (opt==3) cmd_cadastrar_quarto();
        else if (opt==4) cmd_cadastrar_estadia();
    } while (opt != 0);
    printf("Saindo...\n");
    return 0;
}
