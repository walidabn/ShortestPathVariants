#pragma once

#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <climits>
#include <queue>
#include <algorithm>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

class QuestionOnePar {
public :
QuestionOnePar();
~QuestionOnePar();
void testParallelDijkstra();

};
