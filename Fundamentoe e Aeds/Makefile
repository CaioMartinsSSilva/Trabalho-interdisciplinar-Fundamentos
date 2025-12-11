CC=gcc
CFLAGS=-Wall -g -Iinclude
SRC=src/cliente.c src/funcionario.c src/quarto.c src/estadia.c src/persistence.c src/main.c
TESTSRC=tests/test_hotel_munit.c
BIN_DIR=bin

all: dirs $(BIN_DIR)/hotel

dirs:
	mkdir -p $(BIN_DIR)
	mkdir -p data

$(BIN_DIR)/hotel: $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC) -lm

test: dirs $(BIN_DIR)/test_hotel

$(BIN_DIR)/test_hotel: $(filter-out src/main.c,$(SRC)) $(TESTSRC)
	$(CC) $(CFLAGS) -o $@ $(filter-out src/main.c,$(SRC)) $(TESTSRC) -lm

clean:
	rm -rf $(BIN_DIR)/*
	rm -f data/*.bin
