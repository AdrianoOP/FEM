HEADERS=headers
SOURCES=src
LIBS=libs
MAIN=main.c

clean:
	rm -rf *~ *# headers/*~  headers/*#  src/*~  src/*#  docs/*~ docs/*# *.out *.o

all:  global elements_nodes import solver export
	gcc $(MAIN) import.o global.o elements_nodes.o solver.o export.o -o main

import: $(HEADERS)/import.h $(SOURCES)/import.c global elements_nodes
	gcc $(SOURCES)/import.c -c -o import.o

elements_nodes: $(HEADERS)/elements_nodes.h $(SOURCES)/elements_nodes.c global
	gcc $(SOURCES)/elements_nodes.c -c -o elements_nodes.o

global: $(HEADERS)/global.h $(SOURCES)/global.c
	gcc $(SOURCES)/global.c -c -o global.o

solver: $(HEADERS)/solver.h $(SOURCES)/solver.c global elements_nodes
	gcc $(SOURCES)/solver.c -c -o solver.o

export: $(HEADERS)/export.h $(SOURCES)/export.c elements_nodes
	gcc $(SOURCES)/export.c -c -o export.o

