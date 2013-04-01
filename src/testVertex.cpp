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
	std::cout << "Final : " << v << std::endl;
	graphs::Vertex v2(v);
	std::cout << "Copy : " << v2 << std::endl;
	graphs::Vertex * v3 = new graphs::Vertex(v2);
	std::cout << "Copy : " << *v3 << std::endl;
	delete v3;
}
