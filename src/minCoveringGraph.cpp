#include <iostream>
#include <vector>
#include <tuple>


#include "Graph.hpp"

int main(int argc, char ** argv){

  graphs::Graph & g2 = graphs::graphFromFile(argv[1]);

  std::vector<std::tuple<unsigned int, unsigned int> > coveringTree;
  coveringTree = g2.minimalCoveringTree();

  for (unsigned int i = 0; i < coveringTree.size(); i++){
    int v1 = std::get<0>(coveringTree[i]);
    int v2 = std::get<1>(coveringTree[i]);
    std::cout << g2.getVertex(v1).getName() << "   ";
    std::cout << g2.getVertex(v2).getName() << std::endl;
  }

  delete &g2;
}
