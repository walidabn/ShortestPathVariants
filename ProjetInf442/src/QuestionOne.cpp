#include "QuestionOne.hpp"
#include <iostream>
#include <stdio.h>
#include <limits.h>
#define V 9 // V is the number of vertices in the graph

using namespace std;

QuestionOne::QuestionOne()
{
    //ctor
}

QuestionOne::~QuestionOne()
{
    //dtor
}



// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path set
int minDistance(int dist[], bool shortestPathSet[])
{
   // Initialize min value
   int min = INT_MAX;
   int min_index = -1;

   for (int v = 0; v < V; v++){
     if (shortestPathSet[v] == false && dist[v] <= min) {
         min = dist[v];
         min_index = v;
}
}
   return min_index;
}

// A utility method to print the constructed distance array :
// Takes as an argument n if we ever want to print the shortest path to the n first elements of dist (the n "first vertices" of the graph)
// To print the solution from a source to all targets, we simply set n = V
void printSolution(int dist[], int n)
{
   cout<<"Vertex   Distance from Source"<<endl;
   for (int i = 0; i < V; i++) {
   cout << i << "              " << dist[i]<< endl;
      }
}

//Method for a sequential implementation of the Dijkstra algorithm
void sequentialDijkstra(int graph[V][V], int source)
{
     int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i

     bool shortestPathSet[V]; // shortestPathSet[i] will be true if vertex i is included in shortest
                     // path Set or shortest distance from source to i is finalized

     // Initialize all distances as INFINITE and shortestPathSet[] as false
     for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        shortestPathSet[i] = false;
        }

     // Distance of source vertex from itself is always 0
     dist[source] = 0;

     // Find shortest path for all vertices
     for (int count = 0; count < V-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in the first iteration.
       int u = minDistance(dist, shortestPathSet);

       // Mark the picked vertex as processed
       shortestPathSet[u] = true;

       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < V; v++)

         // Update dist[v] only if is not in sptSet, there is an edge from
         // u to v, and total weight of path from src to  v through u is
         // smaller than current value of dist[v]
         if (!shortestPathSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v]) {
            dist[v] = dist[u] + graph[u][v];
            }
     }

     // print the constructed distance array
     printSolution(dist, V);
}

void QuestionOne::testSequentialDijkstra(){

 int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                      {4, 0, 8, 0, 0, 0, 0, 11, 0},
                      {0, 8, 0, 7, 0, 4, 0, 0, 2},
                      {0, 0, 7, 0, 9, 14, 0, 0, 0},
                      {0, 0, 0, 9, 0, 10, 0, 0, 0},
                      {0, 0, 4, 14, 10, 0, 2, 0, 0},
                      {0, 0, 0, 0, 0, 2, 0, 1, 6},
                      {8, 11, 0, 0, 0, 0, 1, 0, 7},
                      {0, 0, 2, 0, 0, 0, 6, 7, 0}
                     };

    sequentialDijkstra(graph, 0);
}

