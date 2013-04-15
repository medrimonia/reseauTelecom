#include <iostream>
#include <vector>
#include <tuple>


#include "Graph.hpp"

int main(int argc, char ** argv){

  graphs::Graph & g = graphs::graphFromFile(argv[1]);

  std::vector<std::tuple<unsigned int, unsigned int> > coveringTree;
  coveringTree = g.minimalCoveringTree();

  for (unsigned int i = 0; i < coveringTree.size(); i++){
    int v1 = std::get<0>(coveringTree[i]);
    int v2 = std::get<1>(coveringTree[i]);
    g.addEdge(v1,v2);
    std::cout << g.getVertex(v1).getName() << "   ";
    std::cout << g.getVertex(v2).getName() << std::endl;
  }

  std::cout << "#Total cost : " << g.cost() << std::endl;

  delete &g;
}
