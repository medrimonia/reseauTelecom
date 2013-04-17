CC=g++
CFLAGS= -ggdb -Wall -Wextra -std=c++0x

# Targets

all: testVertex testGraph minCoveringTree testCycleGraph

minCoveringTree: minCoveringTree.o Graph.o Vertex.o

testGraph: testGraph.o Graph.o Vertex.o

testVertex: testVertex.o Vertex.o

testCycleGraph: testCycleGraph.o Graph.o Vertex.o

testCycleGraphV2: testCycleGraphV2.o Graph.o Vertex.o GraphTools.o

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