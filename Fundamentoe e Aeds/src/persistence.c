#include "cliente.h"
#include "funcionario.h"
#include "quarto.h"
#include "estadia.h"

void carregar_tudo(void) {
    clientes_inicializar();
    funcionarios_inicializar();
    quartos_inicializar();
    estadias_inicializar();
    carregar_clientes_arquivo();
    carregar_funcionarios_arquivo();
    carregar_quartos_arquivo();
    carregar_estadias_arquivo();
}
