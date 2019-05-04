#include <iostream>
#include "Edge.hpp"

Edge::Edge(int i, int j, int c):source(i),destination(j),cost(c),constraint(0){}

Edge::Edge(int i, int j, int c, int c2):source(i),destination(j),cost(c),constraint(c2){}

Edge::~Edge(){}
