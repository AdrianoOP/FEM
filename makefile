HEADERS=/headers
SOURCES=/src
LIBS=/libs
MAIN=main.c

clean:
	rm -rf *~ *#

all:
	gcc $(MAIN) -o main