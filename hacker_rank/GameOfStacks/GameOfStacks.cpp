#include "GameOfStacks.h"

// Dynamic approach - solve the stacks from bottom to top
// Choose all possible ways, but make a choice every time when solving one 
// search if an optimal solution has already been found in the solutions map
// Return the optimal approach

namespace stacks
{

static std::map<Pair, int> solutionCache;

static int maxScore = 0;

bool SolutionExists(const Pair & inPair, int & score)
{
    auto it = solutionCache.find(inPair);
    if ( solutionCache.cend() != it)
    {
        score = std::get<1> (*it);
        return true;
    }
    else
    {
        return false;
    }    
}

int SolutionLookup(const Pair & inPair)
{
    auto it = solutionCache.find(inPair);
    if ( solutionCache.cend() != it)
    {
        return std::get<1> (*it);
    }
    else
    {
        return -1;
    }
}

bool PlaceSolution(const Pair & inPair, const int score)
{
    MapIter iter;
    if ( (iter = solutionCache.find( inPair )) != solutionCache.cend() )
    {
        if (std::get<1> (*iter) > score)
        {
            solutionCache.emplace( std::make_pair(inPair, score) );
        }
    }
    else
    {
        solutionCache.emplace( std::make_pair(inPair, score) ); 
    }
    
}

int SolveStack( const int * pLS, const int * pRS, 
                const int lSize, const int rSize, 
                int lastLeft, int lastRight, 
                int sum, int score, int maxSum)
{
    int tmpScore = 0;
    // printf("#########\nStarting at %i %i\n", lastLeft, lastRight);
    //printf("sum: %d score: %d\n", sum, score);
    if (maxSum < sum)
    {
        // printf("maxSum %d < sum %d score: %d \n", maxSum, sum, score);
        PlaceSolution(std::make_pair(lastLeft, lastRight), score);
        return 0;
    }


    // iterate through possible solutions
    if ( SolutionExists( std::make_pair(lastLeft, lastRight), tmpScore)  )
    {
        // printf("Solution %d < %d\n", tmpScore, score);
        if ( tmpScore < score )
        {
            // printf("Placing better solution %d < %d\n", tmpScore, score);
            PlaceSolution(std::make_pair(lastLeft, lastRight), score);
        }
        else
        {
            // printf("Solution exists and is better than current %d >= %d\n", tmpScore, score);
            return -1;
        }
    }
    else
    {
        PlaceSolution(std::make_pair(lastLeft, lastRight), score);
    }

    if (lastLeft > 0)
    {
        // printf("Recursive left: %d %d\n", lastLeft, lastRight);
        SolveStack(pLS, pRS, lSize, rSize,  lastLeft - 1, lastRight, sum + pLS[lastLeft], score + 1, maxSum);
    }

    if (lastRight > 0)
    {
        // printf("Recursive right: %d %d\n", lastLeft, lastRight);
        SolveStack(pLS, pRS, lSize, rSize,  lastLeft, lastRight - 1, sum + pRS[lastRight], score + 1, maxSum);
    }
    
    if (lastLeft < 0 && lastRight < 0)
        PlaceSolution(std::make_pair(lastLeft, lastRight), score);

    maxScore = score > maxScore ? score : maxScore;
}

int SolveStacks(const int * pLS, const int * pRS, const int lSize, const int rSize, int maxSum)
{
    SolveStack(pLS, pRS, lSize, rSize, lSize - 1, rSize - 1, 0, 0, maxSum);
    auto it = solutionCache.find(std::make_pair(lSize - 1, rSize - 1));
    assert(solutionCache.cend() != it);
    return std::get<1> (*it);
}


}

int main()
{
    int g; 
    scanf("%d",&g);
    for ( int a0 = 0 ; a0 < g ; a0++)
    {
        int n; 
        int m; 
        int x; 
        scanf( "%d %d %d", &n ,&m ,&x );
        //printf("g: %d, n: %d, m: %d, x: %d\n", g, n, m, x);
        int *a = (int*) malloc( sizeof(int) * n );
        for(int a_i = 0; a_i < n; a_i++)
        {
           scanf( "%d", &a[a_i] );
        }
        int *b = (int*) malloc( sizeof(int) * m );
        for(int b_i = 0 ; b_i < m ; b_i++)
        {
           scanf( "%d", &b[b_i] );
        }

        stacks::SolveStacks(a, b, n, m, x);
        printf("%i\n", stacks::maxScore);
        // your code goes here
        free(a);
        free(b);
        stacks::maxScore = 0;
        stacks::solutionCache.clear();
    }
    return 0;
}
