HEADERS=headers
SOURCES=src
LIBS=libs
MAIN=main.c

clean:
	rm -rf *~ *# headers/*~  headers/*#  src/*~  src/*#  docs/*~ docs/*# *.out *.o

cans: clean
	rm -rf *.ans

all:  global elements_nodes import solver export matrix_operations
	gcc $(MAIN) import.o global.o elements_nodes.o solver.o matrix_operations.o export.o -o main

import: $(HEADERS)/import.h $(SOURCES)/import.c
	gcc $(SOURCES)/import.c -c -o import.o

elements_nodes: $(HEADERS)/elements_nodes.h $(SOURCES)/elements_nodes.c
	gcc $(SOURCES)/elements_nodes.c -c -o elements_nodes.o

global: $(HEADERS)/global.h $(SOURCES)/global.c
	gcc $(SOURCES)/global.c -c -o global.o

matrix_operations: $(HEADERS)/matrix_operations.h $(SOURCES)/matrix_operations.c
	gcc $(SOURCES)/matrix_operations.c -c -o matrix_operations.o

solver: $(HEADERS)/solver.h $(SOURCES)/solver.c
	gcc $(SOURCES)/solver.c -c -o solver.o

export: $(HEADERS)/export.h $(SOURCES)/export.c
	gcc $(SOURCES)/export.c -c -o export.o

