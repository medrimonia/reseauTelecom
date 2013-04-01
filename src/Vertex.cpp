#include <ostream>
#include "Vertex.hpp"

namespace graphs{

  Vertex::Vertex(){
    _name = "???";
    _x = 0;
    _y = 0;
  }

  Vertex::Vertex(const Vertex & v){
    _name = v._name;
    _x = v._x;
    _y = v._y;
  }

  Vertex::~Vertex(){
  }

  std::string Vertex::getName() const{
    return _name;
  }

  int Vertex::getX() const{
    return _x;
  }

  int Vertex::getY() const{
    return _y;
  }

  void Vertex::setName(std::string newName){
    _name = newName;
  }

  void Vertex::setPosition(int x, int y){
    _x = x;
    _y = y;
  }

  std::ostream & operator<<(std::ostream &out, const Vertex & v){
    out << "(";
    out << v.getName();
    out << ',';
    out << v.getX();
    out << ',';
    out << v.getY();
    out << ")";
    return out;
  }
}
