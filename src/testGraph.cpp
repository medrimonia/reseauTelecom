#include <iostream>

#include "Graph.hpp"

int main(int argc, char ** argv){
	std::vector<std::string> names(1,"toto");
	std::vector<std::vector<int> > locations(1, std::vector<int>(2,3));
	std::cout << "location size : " << locations.size() << '\n';
	graphs::Graph g(names, locations);
	std::cout << g << std::endl;
}
