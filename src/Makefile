CC=g++
CFLAGS= -ggdb -Wall -Wextra

# Targets

all: testVertex testGraph

testGraph: testGraph.o Graph.o Vertex.o

testVertex: testVertex.o Vertex.o

# Generic Rules

%.o: %.cpp
	${CC} ${CFLAGS} -o $@ -c $<

# Specific dependencies

Vertex.o: Vertex.hpp

Graph.o: Graph.hpp

testGraph.o: Graph.hpp

# clean

clean:
	rm -rf *.o *~

mrproper: clean
	rm -rf testVertex testGraph