#include "GameOfStacks.h"

// Dynamic approach - solve the stacks from bottom to top
// Choose all possible ways, but make a choice every time when solving one 
// search if an optimal solution has already been found in the solutions map
// Return the optimal approach

namespace stacks
{

static std::map<Pair, int> solutionCache;

bool SolutionExists(const Pair & inPair)
{
    auto it = solutionCache.find(inPair);
    return (solutionCache.cend() != it);
}

int SolutionLookup(const Pair & inPair, int & score)
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

int SolveStack(const int * pLS, const int * pRS, const int lSize, const int rSize, int maxSum)
{
    assert(!"not implemented");
    int lastLeft = lSize;
    int lastRight = rSize;
    int currentSum = 0;
    int score = 0;
    printf("Starting at %i %i\n", lastLeft, lastRight);
    if (lastLeft < 0 || lastRight < 0)
        return -1;

    // iterate through possible solutions
    for (int i = 0 ; i < lSize ; i++)
    {
        for (int j = 0 ; j < rSize ; j++)
        {

        }
    }
}

int SolveStacks(const int * pLS, const int * pRS, const int lSize, const int rSize, int maxSum)
{

}

int GreedyStack(const int * pLS, const int * pRS, const size_t lssize, const size_t rssize, const long int maxval)
{
    int scoreTrack = 0;
    long int sum = 0;
    int lPos = 0;
    int rPos = 0;
    while (lPos < lssize && rPos < rssize)
    {
        if ( pLS[lPos] < pRS[rPos] )
        {
            sum += pLS[lPos++];
        }
        else
        {
            sum += pRS[rPos++];
        }

        if (sum <= maxval)
            scoreTrack++;
        else
            break;
    }

    while (lPos < lssize)
    {
        sum += pLS[lPos++];

        if (sum <= maxval)
            scoreTrack++;
        else
            break;
    }   

    while (rPos < rssize)
    {
        sum += pRS[rPos++];

        if (sum <= maxval)
            scoreTrack++;
        else
            break;
    } 
    return scoreTrack;
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

        printf("%i\n", stacks::GreedyStack(a, b, n, m, x));
        // your code goes here
        free(a);
        free(b);
    }
    return 0;
}
