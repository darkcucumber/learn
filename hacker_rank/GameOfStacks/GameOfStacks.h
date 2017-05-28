#include <iostream>
#include <map>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <utility>

namespace stacks
{

using Pair = std::pair<int, int>;
using MapIter = std::map<Pair, int>::iterator;

bool SolutionExists(const Pair & inPair, int & score);

int SolutionLookup(const Pair & inPair);

bool PlaceSolution(const Pair & inPair, const int score);

int SolveStack(const int * pLS, const int * pRS, const int lSize, const int rSize, int sum, int score, int maxSum);

int SolveStacks(const int * pLS, const int * pRS, const int lSize, const int rSize, int maxSum);

}