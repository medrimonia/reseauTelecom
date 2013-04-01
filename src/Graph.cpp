#include <iostream>
#include <fstream>

#include "Graph.hpp"

namespace graphs{
	Graph::Graph(std::vector<std::string> vertexNames,
							 std::vector<std::vector<int> > vertexLocations){
		for (std::size_t i=0; i < vertexNames.size(); i++){
			Vertex * v = new Vertex();
			v->setName(vertexNames[i]);
			v->setPosition(vertexLocations[i][0], vertexLocations[i][1]);			
			_vertices.push_back(v);
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
		//delete &_vertices;
		//delete &_incidence;
		//delete &_distances;
	}
	
	std::vector<Vertex *> Graph::getVertices() const{
		return _vertices;
	}
	
	
	Graph & graphFromFile(char * path){
		std::ifstream input;
		std::vector<std::string> vertexNames;
		std::vector<std::vector<int> > vertexLocations;
		input.open(path);
		char name[3];
		int x;
		int y;
		while (input >> name >> x >> y){
			vertexNames.push_back(name);
			std::vector<int> vec;
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
		std::vector<Vertex *> vertices = g.getVertices();
		for (std::size_t i = 0; i < vertices.size(); i++)
			out << *vertices[i];
		out << '}';
		return out;
	}
}
