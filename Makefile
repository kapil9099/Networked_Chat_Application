# Compiler and flags
CC = g++
CFLAGS = -Wall -std=c++11 -Iinclude

# Detect platform for linking Windows libraries if needed
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LDFLAGS = 
else ifeq ($(UNAME_S),Darwin)
    LDFLAGS = 
else
    LDFLAGS = -lws2_32
endif

# Targets
all: server client

# Server target
server: main_server.o src/server.o src/network_utils.o
	$(CC) $(CFLAGS) -o server main_server.o src/server.o src/network_utils.o $(LDFLAGS)

# Client target
client: main_client.o src/client.o src/network_utils.o
	$(CC) $(CFLAGS) -o client main_client.o src/client.o src/network_utils.o $(LDFLAGS)

# Object files for the main files
main_server.o: main_server.cpp include/server.h include/network_utils.h
	$(CC) $(CFLAGS) -c main_server.cpp

main_client.o: main_client.cpp include/client.h include/network_utils.h
	$(CC) $(CFLAGS) -c main_client.cpp

# Object files for source files in the src directory
src/server.o: src/server.cpp include/server.h include/network_utils.h
	$(CC) $(CFLAGS) -c src/server.cpp -o src/server.o

src/client.o: src/client.cpp include/client.h include/network_utils.h
	$(CC) $(CFLAGS) -c src/client.cpp -o src/client.o

src/network_utils.o: src/network_utils.cpp include/network_utils.h
	$(CC) $(CFLAGS) -c src/network_utils.cpp -o src/network_utils.o

# Clean up
clean:
	rm -f *.o src/*.o server client
