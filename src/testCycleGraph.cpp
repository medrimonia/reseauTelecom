#include <iostream>
#include <vector>
#include <tuple>
#include <limits>

#include "Graph.hpp"

#define DEBUG 0

int main(int argc, char ** argv){

  graphs::Graph & g = graphs::graphFromFile(argv[1]);

  // TODO: Maybe readable from args later
  int cycleMaxSize = 4;

  std::vector<std::tuple<unsigned int, unsigned int> > coveringTree;
  coveringTree = g.minimalCoveringTree();

  for (unsigned int i = 0; i < coveringTree.size(); i++){
    int v1 = std::get<0>(coveringTree[i]);
    int v2 = std::get<1>(coveringTree[i]);
    g.addEdge(v1, v2);
  }
  std::vector<std::tuple<unsigned int, unsigned int> > edgeQueue;
  edgeQueue = coveringTree;
  // While there's still edge in the queue check if they're in cycle
  while (edgeQueue.size() != 0){
    std::tuple<unsigned int, unsigned int> edge = edgeQueue.back();
    int v1 = std::get<0>(edge);
    int v2 = std::get<1>(edge);
    // If edge is not in a cycle, we must add an edge
    if (!g.isEdgeInBornedCycle(v1, v2, cycleMaxSize)){
      // Edge must be removed before searching
      g.removeEdge(v1,v2);
      if (DEBUG){
        std::cout << "Edge {" << v1 << ',' << v2 << "} is not in a cycle";
        std::cout << std::endl;
      }
      // Since we had an edge and one was already present, maximal dist is
      // cycleMaxSize-2
      std::set<unsigned int> v1Neighbors = g.verticesInRange(v1,
                                                             cycleMaxSize - 2);
      std::set<unsigned int> v2Neighbors = g.verticesInRange(v2,
                                                             cycleMaxSize - 2);
      // Finding the best edge
      std::tuple<unsigned int, unsigned int> bestEdge;
      float minDist = std::numeric_limits<float>::max();
      //TODO avoid code duplication here
      // Searching an edge with v1
      unsigned int src = v2;
      for (std::set<unsigned int>::iterator it = v1Neighbors.begin();
           it != v1Neighbors.end();
           ++it){
        unsigned int dst = *it;
        if (!g.edgeExists(src, dst) && g.getDistance(src, dst) < minDist){
          minDist = g.getDistance(src, dst);
          std::get<0>(bestEdge) = src;
          std::get<1>(bestEdge) = dst;
        }
      }
      // Searching an edge with v2
      src = v1;
      for (std::set<unsigned int>::iterator it = v2Neighbors.begin();
           it != v2Neighbors.end();
           ++it){
        unsigned int dst = *it;
        if (!g.edgeExists(src, dst) && g.getDistance(src, dst) < minDist){
          minDist = g.getDistance(src, dst);
          std::get<0>(bestEdge) = src;
          std::get<1>(bestEdge) = dst;
        }
      }
      if (DEBUG){
        std::cout << "Best edge replacing : {" << std::get<0>(bestEdge) << ",";
        std::cout << std::get<1>(bestEdge) << "}" << std::endl;
      }
      // bestEdge has now been found
      g.addEdge(std::get<0>(bestEdge), std::get<1>(bestEdge));
      edgeQueue.insert(edgeQueue.begin(), bestEdge);
      // Inserting removed edge again
      g.addEdge(v1, v2);
    }
    edgeQueue.pop_back();
  }

  std::vector<std::tuple<unsigned int, unsigned int> > edges;
  edges = g.getEdges();
  for (unsigned int i = 0; i < edges.size(); i++){
    int v1 = std::get<0>(edges[i]);
    int v2 = std::get<1>(edges[i]);
    std::cout << g.getVertex(v1).getName() << "   ";
    std::cout << g.getVertex(v2).getName() << std::endl;
  }
  
  if (DEBUG){
    std::cout << "Is (4,5) in a cycle of len 4? ";
    std::cout << g.isEdgeInBornedCycle(4,5,4) << std::endl;
    std::cout << "Is (7,8) in a cycle of len 4? ";
    std::cout << g.isEdgeInBornedCycle(7,8,4) << std::endl;
  }
  // Cleaning
  delete &g;
}
