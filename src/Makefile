CC=g++
CFLAGS=

# Targets

testVertex: testVertex.o Vertex.o

# Generic Rules

%.o: %.c
	${CC} ${CFLAGS} -o $@ -c $<

# Specific dependencies

Vertex.o: Vertex.hpp