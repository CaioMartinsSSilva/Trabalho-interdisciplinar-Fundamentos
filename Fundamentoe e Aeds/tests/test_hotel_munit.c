#include "munit.h"
#include "cliente.h"
#include "quarto.h"
#include "estadia.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void setup(void) {
    remove("data/clientes.bin");
    remove("data/quartos.bin");
    remove("data/estadias.bin");
    clientes_inicializar();
    quartos_inicializar();
    estadias_inicializar();
}

static MunitResult test_cadastrar_cliente_sucesso(const MunitParameter params[], void* data) {
    setup();
    Cliente c = { .codigo = 10, .nome = "Teste", .endereco = "R", .telefone = "119" };
    int r = cadastrar_cliente(c);
    munit_assert_int(r, ==, 0);
    return MUNIT_OK;
}

static MunitResult test_cadastrar_cliente_duplicado(const MunitParameter params[], void* data) {
    setup();
    Cliente c = { .codigo = 11, .nome = "A", .endereco = "R", .telefone = "119" };
    munit_assert_int(cadastrar_cliente(c), ==, 0);
    munit_assert_int(cadastrar_cliente(c), ==, -1);
    return MUNIT_OK;
}

static MunitResult test_cadastrar_quarto_e_estadia(const MunitParameter params[], void* data) {
    setup();
    Cliente c = { .codigo = 20, .nome = "C", .endereco = "R", .telefone = "119" };
    munit_assert_int(cadastrar_cliente(c), ==, 0);
    Quarto q = { .numero = 101, .capacidade = 2, .valor_diaria = 150.0f, .status = 0, .active = 1 };
    munit_assert_int(cadastrar_quarto(q), ==, 0);
    Estadia e;
    int r = cadastrar_estadia(20, 2, "2025-12-10", "2025-12-12", &e);
    munit_assert_int(r, ==, 0);
    munit_assert_int(e.qtd_diarias, ==, 2);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/cliente/sucesso", test_cadastrar_cliente_sucesso, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/cliente/duplicado", test_cadastrar_cliente_duplicado, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/estadia/full", test_cadastrar_quarto_e_estadia, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/hotel", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
