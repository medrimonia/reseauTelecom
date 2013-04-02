#include <iostream>
#include <vector>
#include <tuple>
#include <set>


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

  std::cout << "Distance : " << g2.getDistance(0,2) << std::endl;

  std::vector<std::tuple<unsigned int, unsigned int> > coveringTree;
  coveringTree = g2.minimalCoveringTree();

  for (unsigned int i = 0; i < coveringTree.size(); i++){
    int v1 = std::get<0>(coveringTree[i]);
    int v2 = std::get<1>(coveringTree[i]);
    g2.addEdge(v1,v2);
    std::cout << g2.getVertex(v1).getName() << "   ";
    std::cout << g2.getVertex(v2).getName() << std::endl;
  }

  std::cout << "Computing neighborhood" << std::endl;
  std::set<unsigned int> neighborhood = g2.verticesInRange(2,2);

  for (std::set<unsigned int>::iterator it = neighborhood.begin();
       it != neighborhood.end();
       ++it){
    std::cout << g2.getVertex(*it) << std::endl;
  }
  

  delete &g2;
}
