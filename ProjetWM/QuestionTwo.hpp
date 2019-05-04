#pragma once

#include <iostream>
#include <vector>
#include <list>
#include "Graph.hpp"

class QuestionTwo {


  Graph graph;
  int source;
  int destination;
  int visits; //number of vertices that have been visited
  int max_weight;

  int*** distances; //table of distances d[v][j][w] -> distance to reach the vertex v via j arcs with a weight = w
               //is = infinity if no feasible path
  int** predecessors; //table of the precessors of each vertex i in the computation of the shortest path between s and i
                //second dimension : with a weight =w
              //prec[i][w] = -1 if no path has been found between s and i



  std::vector<int> shortestPath; //the shortest path between source and destination

public:


  Graph get_graph();
  int get_source();
  int get_destination();
  int get_visits();
  int get_max_weight();
  int*** get_distances();
  int** get_predecessors();
  std::vector<int> get_shortestPath();

  QuestionTwo(Graph graph, int source, int destination);
 ~QuestionTwo();
  int compute();

 // void testConstrainedSP();
};

