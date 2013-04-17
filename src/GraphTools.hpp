#ifndef GRAPH_TOOLS_HPP
#define GRAPH_TOOLS_HPP

#include <tuple>
#include <vector>

bool
edgeEqual(std::tuple<unsigned int, unsigned int> e1,
          std::tuple<unsigned int, unsigned int> e2);

bool
containsEdge(std::vector<std::tuple<unsigned int, unsigned int> > & container,
             std::tuple<unsigned int, unsigned int> edge);

void
removeEdge(std::vector<std::tuple<unsigned int, unsigned int> > & container,
           std::tuple<unsigned int, unsigned int> edge);
#endif
