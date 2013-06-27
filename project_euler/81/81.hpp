#ifndef EULER_81_HPP
#define EULER_81_HPP

// stl
#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>

// boost
#include <boost/smart_ptr.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

// lemon
#include <lemon/grid_graph.h>
#include <lemon/maps.h>


namespace euler {
  typedef lemon::GridGraph GrGr;
  typedef boost::shared_ptr<GrGr> GraphPtr;
  typedef boost::tokenizer<boost::escaped_list_separator<char> > CsvTokenizer;
  typedef std::vector<GrGr::Node> NodeVector;

  
  template <typename T>
  T str_to(std::string s);

  
  template <typename T>
  void csv_graph_factory(const char* filename,
                         GrGr& g,
                         GrGr::NodeMap<T>& weight_map,
                         GrGr::NodeMap<std::vector<GrGr::Node> >& neighbor_map);


  template <typename T>
  void print_graph(GrGr& g,
                   const GrGr::NodeMap<T>& weight_map);


  template <typename T>
  T get_minimum_weight_path(GrGr& g,
                            GrGr::NodeMap<T>& weight_map,
                            GrGr::NodeMap<NodeVector >& neighbor_map);


  template <typename T>
  void recalculate_weight(GrGr::NodeMap<T>& weight_map,
                          GrGr::NodeMap<NodeVector >& neighbor_map,
                          GrGr::Node& n);
                   


  template <>
  int str_to<int>(std::string s) {
    return std::stoi(s);
  }
  

  template <typename T>
  void csv_graph_factory(const char* filename,
                         GrGr& g,
                         GrGr::NodeMap<T>& weight_map,
                         GrGr::NodeMap<NodeVector >& neighbor_map) {
    boost::char_separator<char> sep(",");
    std::ifstream csv_file(filename);
    std::string line;
    int row_index = 0;
    while (getline(csv_file, line)) {
      int col_index = 0;
      CsvTokenizer tokens(line);
      CsvTokenizer::iterator it = tokens.begin();
      
      for (; it != tokens.end(); ++it, ++col_index) {
        if (row_index < g.height()-1) {
          neighbor_map[g(col_index, row_index)]
            .push_back(g(col_index, row_index+1));
        }
        if (col_index < g.width()-1) {
          neighbor_map[g(col_index, row_index)]
            .push_back(g(col_index+1, row_index));
        }
        weight_map[g(col_index, row_index)] = str_to<T>(*it);
      }
      ++row_index;
    }
  }


  template <typename T>
  void print_graph(GrGr& g,
                   const GrGr::NodeMap<T>& weight_map) {
    for (int y = 0; y < g.height(); ++y) {
      for (int x = 0; x < g.width(); ++x) {
        std::cout << weight_map[g(x,y)] << ',';
      }
      std::cout << "\b \n";
    }
  }

  
  template <typename T>
  T get_minimum_weight_path(GrGr& g,
                            GrGr::NodeMap<T>& weight_map,
                            GrGr::NodeMap<NodeVector >& neighbor_map) {
    for (int i = g.width(); i >= 0; --i) {
      for (int j = g.height(); j >= 0; --j) {
        GrGr::Node n = g(i,j);
        recalculate_weight(weight_map, neighbor_map, n);
      }
    }
    return weight_map[g(0,0)];
  }


  template <typename T>
  void recalculate_weight(GrGr::NodeMap<T>& weight_map,
                          GrGr::NodeMap<NodeVector >& neighbor_map,
                          GrGr::Node& n) {
    const NodeVector& node_vec = neighbor_map[n];
    if (node_vec.size() == 0) {
    }
    else {
      NodeVector::const_iterator it = node_vec.begin();
      T min_val = weight_map[*it];
      T curr_val;
      for (; it != node_vec.end(); ++it) {
        curr_val = weight_map[*it];
        if (curr_val < min_val) {
          min_val = curr_val;
        }
      }
      weight_map[n] += min_val;
    }
  }
    
}
#endif
