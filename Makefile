.PHONY: all clean uncrustify
.DEFAULT_GOAL := all

CC = g++
CFLAGS = -Wall -Werror -pedantic -g 
CLIBS = 
BIN = tremgen

CIMGFLAGS = -O2 -lm -lpthread $(shell pkg-config --libs x11)

all: $(BIN) minimap

$(BIN): textures.o meshes.o altimap.o entity.o envgen.o main.o
	$(CC) $(CFLAGS) main.o textures.o meshes.o altimap.o entity.o envgen.o -o $(BIN) $(CLIBS)

minimap: altimap.o minimap.o 
	$(CC) $(CFLAGS) altimap.o minimap.o $(CIMGFLAGS) -o minimap

main.o: main.cpp
	$(CC) $(CFLAGS) -o main.o -c main.cpp

textures.o: textures.cpp
	$(CC) $(CFLAGS) -o textures.o -c textures.cpp 

meshes.o: meshes.cpp
	$(CC) $(CFLAGS) -o meshes.o -c meshes.cpp 

altimap.o: altimap.cpp
	$(CC) $(CFLAGS) -o altimap.o -c altimap.cpp 

entity.o: entity.cpp
	$(CC) $(CFLAGS) -o entity.o -c entity.cpp 

envgen.o: envgen.cpp
	$(CC) $(CFLAGS) -o envgen.o -c envgen.cpp 

minimap.o: minimap.cpp
	$(CC) $(CFLAGS) -o minimap.o -c minimap.cpp -I libs/CImg/

clean: 
	rm -f *.o *.core $(BIN) minimap

uncrustify:
	uncrustify -c uncrustify.cfg --replace --no-backup -l CPP *.cpp *.h
