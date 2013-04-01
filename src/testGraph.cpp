#include <iostream>

#include "Graph.hpp"

int main(int argc, char ** argv){
	std::vector<std::string> names(1,"toto");
	std::vector<std::vector<int> > locations(1, std::vector<int>(2,3));
	std::cout << "location size : " << locations.size() << '\n';
	graphs::Graph & g = *new graphs::Graph(names, locations);
	std::cout << g << std::endl;
	delete &g;

	graphs::Graph & g2 = graphs::graphFromFile(argv[1]);
	std::cout << g2 << std::endl;
	delete &g2;
}
