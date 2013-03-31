#include "Vertex.hpp"

namespace graphs{
	
	Vertex::Vertex(){
		_name = "???";
		_x = 0;
		_y = 0;
	}

	std::string Vertex::getName(){
		return _name;
	}

	int Vertex::getX(){
		return _x;
	}

	int Vertex::getY(){
		return _y;
	}

	void Vertex::setName(std::string newName){
		_name = newName;
	}
	
	void Vertex::setPosition(int x, int y){
		_x = x;
		_y = y;
	}
}
