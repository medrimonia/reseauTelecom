#include <string>
#include <vector>

#include "Vertex.hpp"

namespace graphs{
  class Graph{
  private:
    /**
     * An array of all the vertices contained in the graph
     */
    std::vector<Vertex *> _vertices;
    /**
     * Incidence[x][y] = true if an edge exist between vertices[x] and
     * vertices[y].
     */
    std::vector<std::vector<bool> > _incidence;
    /**
     * Distances[x][y] is the distance between vertices[x] and vertices[y].
     * it is precalculated in order to spare time.
     */
    std::vector<std::vector<float> > _distances;
  public:
    /**
     * Create a new graph according to the parameters
     */
    Graph(std::vector<std::string> vertexNames,
          std::vector<std::vector<int> > vertexLocations);
    Graph(const Graph & g);
    ~Graph();

    std::vector<Vertex *> getVertices() const;

    float getDistance(unsigned int v1, unsigned int v2) const;
  };

  Graph & graphFromFile(char * fileName);

  std::ostream & operator<<(std::ostream & out, const Graph & g);
}
