#include <ostream>

#include "Graph.hpp"

namespace graphs{
	Graph::Graph(std::vector<std::string> vertexNames,
							 std::vector<std::vector<int> > vertexLocations){
		for (std::size_t i=0; i < vertexNames.size(); i++){
			Vertex * v = new Vertex();
			v->setName(vertexNames[i]);
			v->setPosition(vertexLocations[i][0], vertexLocations[i][1]);			
			_vertices.push_back(*v);
		}
	}
	
	std::vector<Vertex> Graph::getVertices() const{
		return _vertices;
	}

	std::ostream & operator<<(std::ostream & out, const Graph & g){
		out << '{';
		std::vector<Vertex> vertices = g.getVertices();
		for (std::size_t i = 0; i < vertices.size(); i++)
			out << vertices[i];
		out << '}';
		return out;
	}
}
