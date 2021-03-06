CC=g++
CFLAGS=-std=c++17 -O2
CLIBS=-lX11 -lGL -lpthread -lpng -lstdc++fs -levdev

Example: olcExampleProgram.cpp olcPixelGameEngine.h
	$(CC) -o Example olcExampleProgram.cpp $(CLIBS) $(CFLAGS)

clean:
	@echo Making clean...
	@rm Example
	@echo Done...