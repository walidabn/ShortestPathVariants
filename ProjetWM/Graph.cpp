#include <vector>

#include <iostream>

#include <string>

#include "Edge.hpp"

#include "Graph.hpp"

#include <fstream>

#include <cstdlib>


Graph::Graph(): n(0), m(0) {}

Graph::Graph(int n_, int m_): n(n_), m(m_) {}


Graph::~Graph(){}

int Graph::get_n() {
  return this -> n;
}

int Graph::get_m() {
  return this -> m;
}

int Graph::get_max_weight() {
  return this -> max_weight;
}

std::vector<std::vector<Edge>> Graph::get_successors() {
  return this -> successors;
}

void Graph::printGraph() {
  std::cout << "There are " << get_n() << " vertices in the graph" << std::endl;
  std::cout << "There are " << get_m() << "edges in the graph" << std::endl;

  for (int i = 0; i < successors.size(); ++i) {
    std::cout << "Neighbours of " << i << " : ";
    if (successors[i].size() == 0) {
      std::cout << "None";
    } else {
      for (int j = 0; j < successors[i].size(); j++) {
        std::cout << successors[i][j].destination << " ";
      }
    }
    std::cout << std::endl;
  }
}

Edge Graph::getEdge(int i, int j) {
  for (int a = 0; a < successors[i].size(); a++) {
    if (successors[i][a].destination == j) {
      return successors[i][a];
    }
  }
}

void Graph::addEdge(Edge edge) {
  successors[edge.source].push_back(edge);
  m++;
}

void Graph::removeEdge(int i, int j) {
  for (int a = 0; a < successors[i].size(); a++) {
    if (successors[i][a].destination == j) {
      edgesToAdd.push_back(successors[i][a]);
      successors[i].erase(successors[i].begin() + a);
      m--;
    }
  }
}

void Graph::removeNode(int i) {
  for (int a = 0; a < successors.size(); a++) {
    removeEdge(a, i);
  }
  m = m - successors[i].size();
  for (int a = 0; a < successors[i].size(); a++) {
    edgesToAdd.push_back(successors[i][a]);
  }
  successors[i].clear();
}

void Graph::addErasedNode(int i) {
  std::vector < Edge > prevSuccessors = successors[successors.size() - 1];
  for (int a = successors.size() - 1; a > i; a--)
    successors[a] = successors[a - 1];
  successors[i].clear();
  successors.push_back(prevSuccessors);
  n++;
}

int Graph::computeCost(std::vector < int > path) {
  int cost = 0;
  for (int a = 0; a < path.size() - 1; a++)
    cost += getEdge(path[a], path[a + 1]).cost;
  return cost;
}

int Graph::computeCost_table(int * path, int size) {
  int cost = 0;
  for (int a = 0; a < size - 1; a++)
    cost += getEdge(path[a], path[a + 1]).cost;
  return cost;
}

/*
Graph * Graph::createGraph() {
  Graph * graph = new Graph(4, 5);
  std::vector < Edge > v0 = std::vector < Edge > ();
  v0.push_back(Edge(0, 1, 1, 4));
  v0.push_back(Edge(0, 2, 50, 1));

  std::vector < Edge > v1 = std::vector < Edge > ();
  v1.push_back(Edge(1, 2, 100, 5));
  v1.push_back(Edge(1, 3, 50, 1));

  std::vector < Edge > v2 = std::vector < Edge > ();
  v2.push_back(Edge(2, 3, 1, 2));

  std::vector < Edge > v3 = std::vector < Edge > ();

  graph -> get_successors().push_back(v0);
  graph -> get_successors().push_back(v1);
  graph -> get_successors().push_back(v2);
  graph -> get_successors().push_back(v3);

  return graph;

}
*/
