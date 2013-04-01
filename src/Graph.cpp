#include <iostream>
#include <fstream>
#include <cmath>

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

  vector<Vertex *> Graph::getVertices() const{
    return _vertices;
  }

  float Graph::getDistance(unsigned int v1, unsigned int v2) const{
    return _distances[v1][v2];
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
