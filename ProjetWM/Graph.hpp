#pragma once
#define GRAPH

#include <vector>

#include <iostream>

#include "Edge.hpp"

class Graph {

  int n; // number of vertices
  int m; // number of edges
  int max_weight;


  public:
  std::vector < std::vector < Edge > > successors; //vectors of pairs of size n
  int get_n();
  int get_m();
  int get_max_weight();
  std::vector < std::vector < Edge >> get_successors();

  Graph();
  Graph(int n, int m);
 ~Graph();

  std::vector < Edge > edgesToAdd; //the list of edges erased from the graph during the algorithm of the k shortest paths
  void printGraph();

  Edge getEdge(int i, int j); //returns the edge between i and j, supposing that this exists
  void addEdge(Edge edge); //adds the edge between vertices i and j, supposing that it does not exist
  void removeEdge(int i, int j); //removes the edge between vertices i and j, if this exists

  void removeNode(int i); //removes the vertex i, and all the related edges
  void addErasedNode(int i); //re-add a node that has been erased = attempt

  int computeCost(std::vector < int > path); //computes the cost of a path represented by a vector
  int computeCost_table(int * path, int size); //computes the cost of a path represented by a table

 // static Graph * createGraph();

};
