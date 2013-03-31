#include <string>

#include <Vertex.hpp>

namespace graphs{
	class Graph{
	private:
		/**
		 * An array of all the vertices contained in the graph
		 */
		Vertex vertices[];
		/**
		 * Incidence[x][y] = true if an edge exist between vertices[x] and
		 * vertices[y].
		 */
		bool ** incidence;
		/**
		 * Distances[x][y] is the distance between vertices[x] and vertices[y].
		 * it is precalculated in order to spare time.
		 */
		float ** distances;
	public:
		/**
		 * Create a new graph according to the parameters
		 */
		Graph(int nbVertex,
					std::string vertexNames,
					int ** vertexLocations);
	}
}
