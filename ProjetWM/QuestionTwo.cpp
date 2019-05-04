#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <limits>
#include "Graph.hpp"
#include "QuestionTwo.hpp"
#include<bits/stdc++.h>
#include <cstdlib>



Graph QuestionTwo::get_graph(){
return this->graph;
}

int QuestionTwo::get_source(){
return this->source;
}

int QuestionTwo::get_destination(){
return this->destination;
}

int QuestionTwo::get_visits(){
return this->visits;
}

int QuestionTwo::get_max_weight(){
return this->max_weight;
}

int*** QuestionTwo::get_distances(){
return this->distances;
}

int** QuestionTwo::get_predecessors(){
return this->predecessors;
}

std::vector<int> QuestionTwo::get_shortestPath(){
return this->shortestPath;
}

QuestionTwo::QuestionTwo(Graph graph_, int source_, int destination_): graph(graph_), source(source_), destination(destination_), max_weight(graph.get_max_weight()){


  distances = new int**[graph_.get_n()];
  for(int i = 0; i < graph_.get_n(); ++i) {
    distances[i] = new int*[graph_.get_n()];
    for(int j = 0; j < graph_.get_n(); ++j) {
      distances[i][j] = new int[max_weight];
    }
  }

  for (int i = 0; i<graph_.get_n(); i++) {
    for (int j = 0; j<graph_.get_n(); j++) {  //max : n steps
      for (int k = 0; k<max_weight; k++) { //max weight
        distances[i][j][k] = INT_MAX;
      }
    }
  }
  distances[source_][0][0] = 0;

  predecessors = new int*[graph_.get_n()];
  //tentative parents are not found yet
  for (int i = 0; i<graph_.get_n(); i++) {
    predecessors[i] = new int[max_weight];
    for (int j = 0; j<max_weight; j++) {
      predecessors[i][j] = -1;
    }
  }

  for (int k = 0; k<max_weight; k++) {
    predecessors[source_][k] = source_;
  }

}


QuestionTwo::~QuestionTwo(){
delete distances;
delete predecessors;
}

int QuestionTwo::compute(){


  for (int i = 1; i<graph.get_n(); i++){ //nb of steps
    //Initialize the new step :
    for (int j = 0;j<graph.get_n();j++){ //for each vertex
      for (int k = 0; k<max_weight; k++){ //for each weight
        distances[j][i][k] = distances[j][i-1][k];
      }
    }

    //Dynamic Programming
    for (int v=0;v<graph.get_n();v++){ //for each vertex

      for (int e=0; e<graph.successors[v].size();e++){  //manipulating edges

        int succ = graph.successors[v][e].destination;
        int edge_d = graph.successors[v][e].cost;
        int edge_w = graph.successors[v][e].constraint;
        for (int w = 0; w<max_weight-edge_w; w++){ //for each weight when new path doesn't exceed the limit

          if (distances[v][i-1][w] != INT_MAX){ //if a path to v with weight w exists
            if (distances[succ][i][w+edge_w] > distances[v][i-1][w] + edge_d){ //update the path
              distances[succ][i][w+edge_w] = distances[v][i-1][w]+edge_d;
              predecessors[succ][w+edge_w] = v;
            }
          }
        }
      }
    }
  }


  //find the optimal path to reach destination
  int w = 0, optimal_w = 0;
  for (w = 0; w<max_weight; w++){
    if (distances[destination][graph.get_n()-1][w] < distances[destination][graph.get_n()-1][optimal_w])
      optimal_w=w;
  }

  w=optimal_w;

  if (distances[destination][graph.get_n()-1][w] == INT_MAX){
    std::cout << "No path found to respect the constraints" << std::endl;
    exit(EXIT_FAILURE);
  }


  //creation of the path
  int count = destination;
  int final_length = 0;
  while (count != source){
    shortestPath.push_back(count);
    int count2 = count;
    count = predecessors[count][w];
    for (int i = 0; i<graph.get_successors()[count].size(); i++){
      if (graph.get_successors()[count][i].destination==count2){ //find the arc between the two vertices
        w -= graph.get_successors()[count][i].constraint;
        }
        final_length += graph.get_successors()[count][i].cost;
        break;

    }
  }
  return final_length;
}






