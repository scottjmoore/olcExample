CC=g++
CFLAGS=-std=c++17 -O2
CLIBS=-lX11 -lGL -lpthread -lpng -lstdc++fs -levdev

Example: olcExampleProgram.cpp
	$(CC) -o Example olcExampleProgram.cpp $(CLIBS) $(CFLAGS)