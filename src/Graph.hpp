#include <string>
#include <vector>
#include <set>

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

    // scoringMethod :
    // 0 : distanceAdded
    // 1 : distanceAdded / nbEdgeCovered
    void generateCycle(
      int scoringMethod,
      std::set<unsigned int> vertexUsed,
      unsigned int actual,
      unsigned int v,
      unsigned int k,
      std::vector<std::tuple<unsigned int, unsigned int> > & best,
      float * bestScore,
      unsigned int * nbCovered,
      std::vector<std::tuple<unsigned int, unsigned int> > & current,
      float * currentScore);
  public:
    /**
     * Create a new graph according to the parameters
     */
    Graph(std::vector<std::string> vertexNames,
          std::vector<std::vector<int> > vertexLocations);
    Graph(const Graph & g);
    ~Graph();

    unsigned int nbVertex() const;

    const Vertex & getVertex(int index) const;
    std::vector<Vertex *> getVertices() const;
    std::vector<std::tuple<unsigned int, unsigned int> > getEdges() const;

    bool edgeExists(unsigned int v1, unsigned int v2) const;
    float getDistance(unsigned int v1, unsigned int v2) const;

    void addEdge(unsigned int v1, unsigned int v2);
    void removeEdge(unsigned int v1, unsigned int v2);

    /**
     * Return the sum of all the edges activated (total cost of the graph)es
     */
    float cost() const;

    /**
     * Return a list of all the vertices which can be reached from v by
     * using k or less edges.
     */
    std::set<unsigned int> verticesInRange(unsigned int v,
                                           unsigned int k);

    /**
     * This function return a cycle that could be built in this graph between
     * the vertex u and the vertex v. The maximal length of the cycle is k
     */
    std::vector<std::tuple<unsigned int, unsigned int> >
    generateCycle(unsigned int u,
                  unsigned int v,
                  unsigned int k,
                  int scoringMethod);

    /**
     * This function return a vector of cycles such as the union of all the
     * edges contained in the different cycles contains all the edges
     * of the graph.
     * Every cycle is of length k or less
     */
    std::vector<std::vector<std::tuple<unsigned int, unsigned int> > >
    generateCycles(unsigned int k);

    /**
     * Return a vector of edge (tuple of their indice) which forms a minimal
     * covering tree for the graph.
     */
    std::vector<std::tuple<unsigned int, unsigned int> >
    minimalCoveringTree();
    /**
     * Return true if the edge between v1 and v2 is in a cycle of size k or less
     */
    bool isEdgeInBornedCycle(unsigned int v1,
                             unsigned int v2,
                             unsigned int k);

    bool areEdgeInCycle(unsigned int k);

    /**
     * Try to switch every edge to another vertices closer and verify if it
     * still matches the rules
     */
    void edgeSwitchImprovement(unsigned int k);
  };

  Graph & graphFromFile(char * fileName);

  std::ostream & operator<<(std::ostream & out, const Graph & g);
}
