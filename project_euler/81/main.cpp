// euler
#include "81.hpp"

// stl
#include <string>
#include <vector>

// lemon
#include <lemon/grid_graph.h>
#include <lemon/maps.h>


int main(int argc, char** argv) {
  if (argc != 4) {
    return 1;
  }
  std::string fn(argv[1]);
  int width = atoi(argv[2]);
  int height = atoi(argv[3]);
  euler::GrGr g(width, height);
  euler::GrGr::NodeMap<int> weight_map(g);
  euler::GrGr::NodeMap<std::vector<euler::GrGr::Node> > neighbor_map(g);
  euler::csv_graph_factory(fn.c_str(), g, weight_map, neighbor_map);
  euler::NodeVector nodes_path;
  int res = euler::get_minimum_weight_path(g, weight_map, neighbor_map);
  std::cout << res << '\n';
  return 0;
}
