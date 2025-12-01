CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -D_DEFAULT_SOURCE
INCLUDEDIR = .

EXEC1 = parte1
DIR1 = parte_I
SRC1 := $(wildcard $(DIR1)/*.c)
INC1 = -I$(INCLUDEDIR) -I$(DIR1)

EXEC2 = sim
DIR2 = parte_II
SRC2 := $(wildcard $(DIR2)/*.c)
INC2 = -I$(INCLUDEDIR) -I$(DIR2)


all: $(EXEC1) $(EXEC2)

# Para crear el ejecutable 'parte1'
$(EXEC1): $(SRC1)
	@echo "Compilando Parte I..."
	$(CC) $(CFLAGS) $(SRC1) $(INC1) -o $(EXEC1)

# Para crear el ejecutable 'sim'
$(EXEC2): $(SRC2)
	@echo "Compilando Simulador (Parte II)..."
	$(CC) $(CFLAGS) $(SRC2) $(INC2) -o $(EXEC2)

clean:
	@echo "Limpiando ejecutables..."
	rm -f $(EXEC1) $(EXEC2)

# Ejecutar sim
test_sim: $(EXEC2)
	./$(EXEC2) 8 4096 traza.txt

# Ejecutar sim con --verbose
test_sim_verbose: $(EXEC2)
	./$(EXEC2) 8 4096 --verbose traza.txt

.PHONY: all clean sim parte1