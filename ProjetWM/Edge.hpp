#pragma once

#define EDGE_S

#include <iostream>

class Edge {



public :
int source;
int destination;
int cost;
int constraint;

Edge(int i, int j, int c);
Edge(int i, int j, int c, int c2);
~Edge();
};




