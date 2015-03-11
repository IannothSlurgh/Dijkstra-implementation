# Makefile

all: dijkstra
unix: u_dijkstra

dijkstra:
	g++-4.6 GraphTest.cpp Graph.cpp Edge.cpp Vertex.cpp dijkstra.cpp -std=c++0x -g -o dijkstra.exe

u_dijkstra:
	g++ GraphTest.cpp Graph.cpp Edge.cpp Vertex.cpp dijkstra.cpp -g -o dijkstra.exe

.PHONY: clean

clean:
	/bin/rm -f *.o dijkstra u_dijkstra