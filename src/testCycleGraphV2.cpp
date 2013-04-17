#include <iostream>
#include <vector>
#include <tuple>
#include <limits>

#include "Graph.hpp"
#include "GraphTools.hpp"

#define DEBUG 0

using std::vector;

int main(int argc, char ** argv){

  graphs::Graph & g = graphs::graphFromFile(argv[1]);

  // TODO: Maybe readable from args later
  int cycleMaxSize = 4;

  vector<std::tuple<unsigned int, unsigned int> > coveringTree;
  coveringTree = g.minimalCoveringTree();

  for (unsigned int i = 0; i < coveringTree.size(); i++){
    int v1 = std::get<0>(coveringTree[i]);
    int v2 = std::get<1>(coveringTree[i]);
    g.addEdge(v1, v2);
  }
  vector<std::tuple<unsigned int, unsigned int> > edgeQueue;

  std::vector<std::tuple<unsigned int, unsigned int> > uncoveredEdge;
  for (unsigned int i = 0; i < coveringTree.size(); i++){
    uncoveredEdge.push_back(coveringTree[i]);
  }

  if (DEBUG)
    std::cout << "Generating cycles" << std::endl;

  vector<vector<std::tuple<unsigned int, unsigned int> > > cyclesSet;
  cyclesSet = g.generateCycles(cycleMaxSize);

  if (DEBUG){
    for (unsigned int cycleIndex = 0;
         cycleIndex < cyclesSet.size();
         cycleIndex++)
    {
      std:: cout << cycleIndex << " : ";
      for (unsigned int edgeIndex = 0;
           edgeIndex < cyclesSet[cycleIndex].size();
           edgeIndex++)
      {
        std::tuple<unsigned int, unsigned int> edge;
        edge = cyclesSet[cycleIndex][edgeIndex];
        std::cout << '{' << std::get<0>(edge)
                  << ',' << std::get<1>(edge) << '}';
      }
      std:: cout << std::endl;
    }
  }

  if (DEBUG)
    std::cout << "Adding Cycles to graph" << std::endl;
  
  // Adding cycle in order to cover all the edges
  while(uncoveredEdge.size() != 0){
    if (DEBUG){
      std::cout << uncoveredEdge.size() << " uncovered edges remaining"
                << std::endl;
    }
    float bestScore = std::numeric_limits<float>::max();
    unsigned int bestIndex = 0;
    for (unsigned int cycleIndex = 0;
         cycleIndex < cyclesSet.size();
         cycleIndex++){
      // Choosing best Cycle
      float score = 0;
      int nbEdgeCovered = 0;
      if (DEBUG >= 2)
        std::cout << cyclesSet[cycleIndex].size() << " edges in the cycle"
                  << std::endl;
      for (unsigned int edgeIndex = 0;
           edgeIndex < cyclesSet[cycleIndex].size();
           edgeIndex++)
      {
        unsigned int u = std::get<0>(cyclesSet[cycleIndex][edgeIndex]);
        unsigned int v = std::get<1>(cyclesSet[cycleIndex][edgeIndex]);
        if (containsEdge(uncoveredEdge, cyclesSet[cycleIndex][edgeIndex])){
          nbEdgeCovered++;
        }
        else
          score += g.getDistance(u,v);
      }
      // Finalisation of score
      if (nbEdgeCovered == 0)
        score = std::numeric_limits<float>::max();
      else
        score = score / nbEdgeCovered;
      if (DEBUG >= 2)
        std::cout << "\tScore : " << score << std::endl;
      if (score < bestScore){
        bestScore = score;
        bestIndex = cycleIndex;
      }
      //
    }
    if (DEBUG)
      std::cout << "Choosed Index : " << bestIndex << std::endl;
    // Now we can add the unused edge and remove edges from uncoveredEdge
    vector<std::tuple<unsigned int, unsigned int> > cycle;
    cycle = cyclesSet[bestIndex]; 
    for (unsigned int edgeIndex = 0; edgeIndex < cycle.size(); edgeIndex++){
      std::tuple<unsigned int, unsigned int> edge = cycle[edgeIndex];
      unsigned int u = std::get<0>(edge);
      unsigned int v = std::get<1>(edge);
      if (! g.edgeExists(u, v))
        g.addEdge(u,v);
      removeEdge(uncoveredEdge, edge);
    }
  }

  // We can now safely remove edges which aren't needed
  std::vector<std::tuple<unsigned int, unsigned int> > edges = g.getEdges();
  for (unsigned int i = 0; i < edges.size(); i++){
    unsigned int u = std::get<0>(edges[i]);
    unsigned int v = std::get<1>(edges[i]);
    g.removeEdge(u, v);
    if (DEBUG >= 2){
      std::cout << "Trying to remove edge {" << u << ',' << v  << "}";
      std::cout << std::endl;
    }
    bool invalidRemoval = false;
    for (unsigned int j = 0; j < edges.size(); j++){
      unsigned int u2 = std::get<0>(edges[j]);
      unsigned int v2 = std::get<1>(edges[j]);
      // Edge might have already been removed
      if (!g.edgeExists(u2,v2))
        continue;
      if (!g.isEdgeInBornedCycle(u2, v2, cycleMaxSize)){
        invalidRemoval = true;
        if (DEBUG >= 2){
          std::cout << "\tCan't remove the edge because of ";
          std::cout << "{" << u2 << "," << v2 << "}" << std::endl;
        }
        break;
      }
    }
    if (invalidRemoval)
      g.addEdge(u,v);
  }

  g.edgeSwitchImprovement(cycleMaxSize);

  // Refreshing edges
  edges = g.getEdges();

  for (unsigned int i = 0; i < edges.size(); i++){
    int v1 = std::get<0>(edges[i]);
    int v2 = std::get<1>(edges[i]);
    std::cout << g.getVertex(v1).getName() << "   ";
    std::cout << g.getVertex(v2).getName() << std::endl;
  }
  
  std::cout << "#Total cost : " << g.cost() << std::endl;
  
  // Cleaning
  delete &g;
}
