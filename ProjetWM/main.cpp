#include <iostream>
#include <stdio.h>
#include <limits.h>
#include "QuestionOne.cpp"
#include "QuestionOnePar.cpp"
#define V 9 // V is the number of vertices in the graph






int main()
{
    /*
    QuestionOne * q1= new QuestionOne();
    q1->testSequentialDijkstra();
    delete q1;
*/


    QuestionOnePar * q12 = new QuestionOnePar();
    q12-> testParallelDijkstra();
    delete q12;

    return 0;
}

