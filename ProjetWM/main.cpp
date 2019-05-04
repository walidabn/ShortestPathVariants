#include <iostream>
#include <stdio.h>
#include <limits.h>
#include "QuestionOne.hpp"
#include "QuestionOnePar.hpp"
#include "QuestionTwo.hpp"
#include "QuestionTwo.cpp"
#include "Graph.cpp"
#include "Edge.hpp"
#include "Edge.cpp"


#define V 9 // V is the number of vertices in the graph



Graph * createGraph(){
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

  graph -> successors.push_back(v0);
  graph -> successors.push_back(v1);
  graph -> successors.push_back(v2);
  graph -> successors.push_back(v3);
return graph;
}





int main()
{
    /*
    QuestionOne * q1= new QuestionOne();
    q1->testSequentialDijkstra();
    delete q1;
    */

    /*
    QuestionOnePar * q12 = new QuestionOnePar();
    q12-> testParallelDijkstra();
    delete q12;
    */

    Graph * graph = createGraph();
  QuestionTwo * q2= new QuestionTwo(*(graph), 0, graph->get_n()-1);

  int length = q2->compute();

  std::cout << "length of the path :" << length << std::endl;
  std::cout << "The path is : ";
  std::cout <<  "1 ";
  for (int i = 0; i< q2->get_shortestPath().size(); i++){
 std::cout << q2->get_shortestPath()[q2->get_shortestPath().size()-1-i]+1 << " ";
}
std::cout << "" << std::endl;
delete q2;



    return 0;
}
