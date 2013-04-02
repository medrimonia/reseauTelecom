#include <iostream>
#include <fstream>
#include <cmath>
#include <tuple>
#include <set>
#include <limits>

#include <assert.h>

#include "Graph.hpp"

using std::vector;

namespace graphs{
  Graph::Graph(vector<std::string> vertexNames,
               vector<vector<int> > vertexLocations){
    unsigned int nbVertex = vertexNames.size();
    for (std::size_t i=0; i < nbVertex; i++){
      Vertex * v = new Vertex();
      v->setName(vertexNames[i]);
      v->setPosition(vertexLocations[i][0], vertexLocations[i][1]);
      _vertices.push_back(v);
    }
    _incidence = *(new vector<vector<bool> >(nbVertex,
                                             vector<bool>(nbVertex, false)));
    _distances = *(new vector<vector<float> >(nbVertex,
                                              vector<float>(nbVertex, 0)));
    for (unsigned int i = 0; i < nbVertex; i++){
      Vertex * v1 = _vertices[i];
      for (unsigned int j = 0; j < nbVertex; j++){
        Vertex * v2 = _vertices[j];
        _distances[i][j] = sqrt(pow(v1->getX() - v2->getX(), 2)
                                + pow(v1->getY() - v2->getY(), 2));
      }
    }
  }

  Graph::Graph(const Graph & g) : _vertices(g._vertices.size()){
    for (std::size_t i=0; i < g._vertices.size(); i++)
      _vertices[i] = g._vertices[i];
    _incidence = g._incidence;
    _distances = g._distances;
  }

  Graph::~Graph(){
    while(!_vertices.empty()){
      delete _vertices.back();
      _vertices.pop_back();
    }
  }

  unsigned int Graph::nbVertex() const{
    return _vertices.size();
  }

  const Vertex & Graph::getVertex(int index) const{
    return *_vertices[index];
  }

  vector<Vertex *> Graph::getVertices() const{
    return _vertices;
  }
  
  vector<std::tuple<unsigned int, unsigned int> > Graph::getEdges() const{
    vector<std::tuple<unsigned int, unsigned int> > edges;
    for (unsigned int i = 0; i < _incidence.size(); i++){
      for (unsigned int j = i + 1; j < _incidence[i].size(); j++){
        if (edgeExists(i, j)){
          std::tuple<unsigned int, unsigned int> edge(i,j);
          edges.push_back(edge);
        }
      }
    }
    return edges;
  }

  void Graph::removeEdge(unsigned int v1, unsigned int v2){
    _incidence[v1][v2] = false;
    _incidence[v2][v1] = false;
  }

  void Graph::addEdge(unsigned int v1, unsigned int v2){
    _incidence[v1][v2] = true;
    _incidence[v2][v1] = true;
  }

  bool Graph::edgeExists(unsigned int v1, unsigned int v2) const{
    return _incidence[v1][v2];
  }

  float Graph::getDistance(unsigned int v1, unsigned int v2) const{
    return _distances[v1][v2];
  }

  std::set<unsigned int> Graph::verticesInRange(unsigned int v,
                                                unsigned int k){
    std::set<unsigned int> inRange;
    // End recursion condition
    if (k == 0)
      return inRange;
    for (unsigned int n = 0; n < nbVertex(); n++){
      if (edgeExists(v, n)){
        inRange.insert(n);
        // We avoid to use the same edge twice
        removeEdge(v,n);
        std::set<unsigned int> reachable = verticesInRange(n, k-1);
        for (std::set<unsigned int>::iterator it = reachable.begin();
             it != reachable.end();
             ++it){
          inRange.insert(*it);
        }
        addEdge(v, n);
      }
    }
    return inRange;
  }

  /**
   * This function uses the Prim algorithm to determine a minimal covering
   * tree. The result is given as a vector of tuple<int,int>, each one
   * representing an edge.
   */
  vector<std::tuple<unsigned int, unsigned int> >
  Graph::minimalCoveringTree(){
    vector<std::tuple<unsigned int, unsigned int> > result;
    // Initializing situation
    std::set<int> inTree;
    std::set<int> outTree;
    inTree.insert(0);
    for (unsigned int i = 1; i < _vertices.size(); i++)
      outTree.insert(i);
    // Adding Edges to the set
    while (outTree.size() > 0){
      // Before finding a new edge
      float minDist = std::numeric_limits<float>::max();
      // best[0] is in tree
      // best[1] is out of tree
      std::tuple<unsigned int, unsigned int> best(0,0);
      // Finding a new edge
      for (std::set<int>::iterator inTreeIt = inTree.begin();
           inTreeIt != inTree.end();
           ++inTreeIt)
      {
        int v1 = *inTreeIt;
        for (std::set<int>::iterator outTreeIt = outTree.begin();
             outTreeIt != outTree.end();
             ++outTreeIt)
        {
          int v2 = *outTreeIt;
          if (getDistance(v1, v2) < minDist){
            minDist = getDistance(v1, v2);
            std::get<0>(best) = v1;
            std::get<1>(best) = v2;
          }
        }
      }// Edge found
      // Adding Edge and updating
      result.push_back(best);
      inTree.insert(std::get<1>(best));
      outTree.erase(std::get<1>(best));
    }
    return result;
  }

  bool Graph::isEdgeInBornedCycle(unsigned int v1,
                                  unsigned int v2,
                                  unsigned int k){
    assert(edgeExists(v1,v2));
    removeEdge(v1,v2);
    // If a Path of length k-1 from v1 to v2 exists, {v1,v2} is in a cycle of
    // length equal or inferior to k
    std::set<unsigned int> nearbyVertex = verticesInRange(v1, k-1);
    // depth first search (removing edges) from v1 to v2
    addEdge(v1,v2);
    return (nearbyVertex.count(v2) == 1);
  }

  float Graph::cost() const{
    float sum = 0;
    for (unsigned int i = 0; i < _vertices.size(); i++){
      for (unsigned int j = i + 1; j < _vertices.size(); j++){
        if (edgeExists(i,j))
          sum += getDistance(i,j);
      }
    }
    return sum;
  }


  Graph & graphFromFile(char * path){
    std::ifstream input;
    vector<std::string> vertexNames;
    vector<vector<int> > vertexLocations;
    input.open(path);
    char name[3];
    int x;
    int y;
    while (input >> name >> x >> y){
      vertexNames.push_back(name);
      vector<int> vec;
      vec.push_back(x);
      vec.push_back(y);
      vertexLocations.push_back(vec);
      //std::cout << name << ' ' << x << ' ' << y << std::endl;
    }
    Graph * g = new Graph(vertexNames, vertexLocations);
    return *g;
  }

  std::ostream & operator<<(std::ostream & out, const Graph & g){
    out << '{';
    vector<Vertex *> vertices = g.getVertices();
    for (std::size_t i = 0; i < vertices.size(); i++)
      out << *vertices[i];
    out << '}';
    return out;
  }
}
