# Plano de Testes (resumido)
TC01: cadastrar_cliente -> espera 0  
TC02: cadastrar_cliente duplicado -> espera -1  
TC03: cadastrar_quarto -> espera 0  
TC04: cadastrar_estadia -> espera 0 e qtd_diarias = diferença de datas
TC05: estadia com cliente inexistente -> espera -1
TC06: estadia com datas inválidas -> espera -2
TC07: sem quarto disponível -> espera -3
