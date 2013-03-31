#include <iostream>

#include "Vertex.hpp"

int main(int argc, char ** argv){
	graphs::Vertex v;
	std::cout << "Initial : " << v.getName();
	std::cout << " at : [" << v.getX() << ',' << v.getY() << "]\n";
	v.setName("TOTO");
	v.setPosition(32,42);
	std::cout << "Final : " << v.getName();
	std::cout << " at : [" << v.getX() << ',' << v.getY() << "]\n";	
}
