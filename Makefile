CC = g++
CFLAGS = -Wall -g 
CLIBS = 
BIN = tremgen

$(BIN): textures.o meshes.o altimap.o entity.o envgen.o main.o
	$(CC) $(CFLAGS) main.o textures.o meshes.o altimap.o entity.o envgen.o -o $(BIN) $(CLIBS)

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

clean: 
	rm -f *.o *.core $(BIN)
