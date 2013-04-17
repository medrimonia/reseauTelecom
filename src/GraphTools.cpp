#include "GraphTools.hpp"

bool
edgeEqual(std::tuple<unsigned int, unsigned int> e1,
          std::tuple<unsigned int, unsigned int> e2){
  unsigned int u1 = std::get<0>(e1);
  unsigned int v1 = std::get<1>(e1);
  unsigned int u2 = std::get<0>(e2);
  unsigned int v2 = std::get<1>(e2);
  return ((u1 == u2 && v1 == v2) || (u1 == v2 && u2 == v1));
}

bool
containsEdge(std::vector<std::tuple<unsigned int, unsigned int> > & container,
             std::tuple<unsigned int, unsigned int> edge){
  for (unsigned int i = 0; i < container.size(); i++){
    if (edgeEqual(container[i], edge))
      return true;
  }
  return false;
}

void
removeEdge(std::vector<std::tuple<unsigned int, unsigned int> > & container,
           std::tuple<unsigned int, unsigned int> edge){
  std::vector<std::tuple<unsigned int, unsigned int> >::iterator it;
  it = container.begin();
  while (it != container.end()){
    if (edgeEqual(*it, edge))
      it = container.erase(it);
    else
      ++it;
  }
}
  
