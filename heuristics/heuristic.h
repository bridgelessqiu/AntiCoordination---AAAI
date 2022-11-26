#ifndef HEURISTIC_H_06191147
#define HEURISTIC_H_06191147 

#include<string>
#include<unordered_map>
#include<vector>
#include "syds.h"

// Synchronous Update for memoryful games
std::vector<int> SynchronousUpdateMemoryful(const std::vector<std::vector<int>>&, const std::vector<int>, std::vector<int>);
NN SynchronousUpdateMemoryful2(const std::vector<std::vector<int>>&, const std::vector<int>, std::vector<int>);

// Synchronous Update for memoryless games
NN SynchronousUpdateMemoryless(std::vector<std::vector<int>>&, const std::vector<int>, std::vector<int>);

#endif
