#include <string>
#include <vector>

#include "Vertex.hpp"

namespace graphs{
	class Graph{
	private:
		/**
		 * An array of all the vertices contained in the graph
		 */
		std::vector<Vertex> _vertices;
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
		std::vector<Vertex> getVertices() const;
	};

	std::ostream & operator<<(std::ostream & out, const Graph & g);
}
