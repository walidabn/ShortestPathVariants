#include "QuestionOnePar.hpp"
#include <unistd.h>
#include <iostream>
#include <climits>
#include <pthread.h>
#include <queue>
#include <algorithm>
#include <memory>
#include <thread>
#include <time.h>
#include <mutex>
#include <condition_variable>
#include <chrono>


QuestionOnePar::QuestionOnePar(){
 // Empty Constructor
}

QuestionOnePar::~QuestionOnePar()
{
    //Empty Destructor
}

// Number of nodes in the graph G
const int VERTICES = 8;
const int Inf = INT_MAX;
const int NaN = INT_MAX;




// Adjacency matrix of the graph

int G[VERTICES][VERTICES] = {
	//A,   B,   C,   D,   E,   F,   G,   H
	{ Inf, 1,   4,   Inf, Inf, Inf, Inf, Inf }, // A
	{ 1,   Inf, 2,   Inf, Inf, Inf, 4,   2   }, // B
	{ 4,   2,   Inf, 1,   3,   Inf, Inf, Inf }, // C
	{ Inf, Inf, 1,   Inf, 1,   3,   1,   Inf }, // D
	{ Inf, Inf, 3,   1,   Inf, 1,   Inf, Inf }, // E
	{ Inf, Inf, Inf, 3,   1,   Inf, 6,   Inf }, // F
	{ Inf, 4,   Inf, 1,   Inf, 6,   Inf, 14  }, // G
	{ Inf, 2,   Inf, Inf, Inf, Inf, 14,  Inf }  // H
};




/** Messages sent among nodes. */
struct Message {
	int sender; // Sender identifier (from 0 to V-1)
	int dist;   // Distance of the sender
};


// State vectors (each position is a different node)
std::vector<std::thread> threads(VERTICES); // Threads
std::vector<std::mutex> mutexes(VERTICES); // Mutexes for accessing thread data
std::vector<std::condition_variable> event(VERTICES); // Condition variables to wait for events
std::vector< std::queue<Message> > messages(VERTICES); // Each node has a queue of messages


// Whether or not the algorithm should finish
bool shouldFinish = false;

void printDist(int dist[VERTICES]){
    for (int i =0; i<VERTICES;++i){
    std::cout <<"distance from source to vertex " ;
    std::cout <<  i  ;
    std::cout << " :  " ;
    std::cout << dist[i] << std::endl;
    }

}

/**
* Given a graph G, this function computes the minimum distance
* from the passed source node to all the other nodes of the graph.
* @param id [IN] Id of the node to compute the distances
* @param dist [OUT] Distance from src to each node
* @param pre[OUT] For each node, the previous node in the shortest path
*/


void parallel_dijkstra(int id, int dist[VERTICES], int prev[VERTICES])
{
	int u = id; // To keep similarity with standard dijkstra

	while (true)
	{
		// When a message is received, this will be set to true if
		// the current path distance is better than the previous one
		bool distance_improved = false;

		// Wait for incoming events (from other nodes) and receive them
		{
			// - TODO 6-a: lock this thread mutex to protect access to global data
			std::unique_lock<std::mutex> lock(mutexes[u]);

			if (messages[u].empty())
			{
				// TODO 6-b: wait for a message from another node
				event[u].wait(lock);
			}

			// TODO 6-c: check if 'shouldFinish' is true to finish this thread
			if (shouldFinish) {
				break;
			}

			// Get the incoming message
			Message msg(messages[u].front());
			messages[u].pop();

			// Update the cost to reach here
			if (msg.sender == NaN)
			{
				dist[u] = 0;
				prev[u] = NaN;
				distance_improved = true;
			}
			else
			{
				int edge_cost = G[u][msg.sender];
				if (msg.dist + edge_cost < dist[u]) {
					dist[u] = msg.dist + edge_cost;
					prev[u] = msg.sender;
					distance_improved = true;
				}
			}
		}

		// If the distance didn't change, skip the rest of the
		// loop and continue to the next iteration
		if (!distance_improved)
		{
			continue;
		}

		// TODO 7: Create a message for the neigbouring nodes
		// - the message needs to contain the information about this thread's node
		Message outmsg;
		outmsg.dist = dist[u];
		outmsg.sender = u;
		// Send messages to neighbour nodes to update their state
		for (int v = 0; v < VERTICES; ++v)
		{
			int edge_dist = G[u][v];
			if (edge_dist != Inf)
			{
				// TODO 8: Send the message to the neighbor
				// - lock the neighbor's mutex
				std::unique_lock<std::mutex> lock(mutexes[v]);
				// - enqueue the message into its queue
				messages[v].push(outmsg);
				// - notify the neighbor about this event (use notify_one)
				event[v].notify_one();
			}
		}
	}
}

/**
* For each node in prev, it prints the computed shortest path from src.
* @param prev Array of previous nodes in the shortest path.
*/
void printPaths(int prev[VERTICES])
{
	for (auto i = 0; i < VERTICES; ++i)
	{
		int n = i;
		while (prev[n] != NaN) {
			std::cout << (char)('A' + n) << " <- " << std::flush;
			n = prev[n];
		}
		std::cout << (char)('A' + n) << std::endl;
	}
}



void QuestionOnePar::testParallelDijkstra(){
    int dist[VERTICES];
	int prev[VERTICES];


	// TODO 1: Using a loop...
	for (int i = 0; i < VERTICES; ++i)
	{
		// - initialize 'dist' and 'prev' array elements to Inf and NaN respectively
		dist[i] = Inf;
		prev[i] = NaN;
	}


	// TODO 2: Using a loop...
	for (int i = 0; i < VERTICES; ++i)
	{
		// - create a thread for each node store them in the global array 'threads'
		// - make them execute the 'parallel_dijkstra' function
		// - pass each thread their id, and the two arrays 'dist' and 'prev'
		threads[i] = std::thread (parallel_dijkstra, i, dist, prev);
	}


	// TODO 3: Look at this code (you don't have to write anything)
	// - it starts the algorithm (notifies the source node to start)
	// - creation of the initial message
	Message msg;
	msg.dist = Inf;
	msg.sender = NaN;
	{
		std::unique_lock<std::mutex> lck(mutexes[0]); // - protects the message queue of the thread 0
		messages[0].push(msg);                        // - pushes the message into the queue of messages for the thread 0
		event[0].notify_one();                        // - notifies the thread 0 that it has a message
	}


	// wait a tenth of a second
	const unsigned int hundred_millis = 100;
    sleep(hundred_millis);


	// TODO 4: Using a loop... notify all threads to finish
	for (int i = 0; i < VERTICES; ++i)
	{
		// - protect each node critical section (locking their mutex)
		std::unique_lock<std::mutex> lock(mutexes[i]);
		// - set the global 'shouldFinish' to true
		shouldFinish = true;
		// - notify the thread that an event occurred
		event[i].notify_one();

	}


	// TODO 5: Using a loop...
	for (int i = 0; i < VERTICES; ++i)
	{
		// - wait for all threads to finish using thread::join()
		threads[i].join();
	}


	// print results
	printPaths(prev);
	printDist(dist);

system("pause");
}
