#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <QuestionOne.cpp>
#include <QuestionOne.hpp>
#define V 9 // V is the number of vertices in the graph

using namespace std;





int main()
{

    QuestionOne q1= new QuestionOne();
    q1.testSequentialDijkstra();
    q1.~QuestionOne();

    return 0;
}

