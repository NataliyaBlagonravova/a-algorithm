CC = g++
CFLAGS = -pedantic -Wall -Werror -Wno-sign-compare  -Wno-long-long -lm --std=c++11
OBJ =  graph.o opened_nodes.o closed_nodes.o path.o a_star_algorithm.o dijkstra_algorithm.o io.o help_calculations.o main.o
PROG = kp

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ)

graph.o: graph.cpp
	$(CC) $(CFLAGS) -c graph.cpp

opened_nodes.o: opened_nodes.cpp
	$(CC) $(CFLAGS) -c opened_nodes.cpp

closed_nodes.o: closed_nodes.cpp
	$(CC) $(CFLAGS) -c closed_nodes.cpp

path.o: path.cpp
	$(CC) $(CFLAGS) -c path.cpp


a_star_algorithm.o: a_star_algorithm.cpp
	$(CC) $(CFLAGS) -c a_star_algorithm.cpp

dijkstra_algorithm.o: dijkstra_algorithm.cpp
	$(CC) $(CFLAGS) -c dijkstra_algorithm.cpp

io.o: io.cpp
	$(CC) $(CFLAGS) -c io.cpp

help_calculations.o: help_calculations.cpp
	$(CC) $(CFLAGS) -c help_calculations.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(OBJ)

cleanall:
	rm -f $(OBJ) $(PROG)