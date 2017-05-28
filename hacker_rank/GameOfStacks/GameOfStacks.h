#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>

namespace stacks
{

using Pair = std::pair<int, int>;
using MapIter = std::map<Pair, int>::iterator;

bool SolutionLookup(const Pair & inPair, int & score);

bool PlaceSolution(const Pair & inPair, const int score);

int SolveStack(const int * pLS, const int * pRS, const int lSize, const int rSize, int maxSum);

int GreedyStack(const int * pLS, const int * pRS, const size_t lssize, const size_t rssize, const long int maxval);

}