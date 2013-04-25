CC=g++
CFLAGS= -ggdb -Wall -Wextra -std=c++0x
LDFLAGS= -lrt

# Targets

all: testVertex testGraph minCoveringTree testCycleGraph testCycleGraphV2

minCoveringTree: minCoveringTree.o Graph.o Vertex.o

testGraph: testGraph.o Graph.o Vertex.o
	$(CC) $^ -o $@ $(LDFLAGS)

testVertex: testVertex.o Vertex.o
	$(CC) $^ -o $@ $(LDFLAGS)

testCycleGraph: testCycleGraph.o Graph.o Vertex.o
	$(CC) $^ -o $@ $(LDFLAGS)

testCycleGraphV2: testCycleGraphV2.o Graph.o Vertex.o GraphTools.o
	$(CC) $^ -o $@ $(LDFLAGS)

# Generic Rules

%.o: %.cpp
	${CC} ${CFLAGS} -o $@ -c $<

# Specific dependencies

testCycleGraphV2.cpp: Graph.hpp GraphTools.hpp

Graph.hpp: Vertex.hpp

Vertex.o: Vertex.hpp

Graph.o: Graph.hpp

testGraph.o: Graph.hpp

minCoveringTree.o : Graph.hpp

# clean

clean:
	rm -rf *.o *~

mrproper: clean
	rm -rf testVertex testGraph minCoveringTree testCycleGraph