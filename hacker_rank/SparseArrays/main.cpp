#include "SparseArrays.h"

int main() 
{
    int numOfStrings = 0;
    int numOfQueries = 0;
    char tmpString[21];
    StringVec stringVec;
    StringVec queryVec;

    // read the number of strings
    if ( scanf("%d\n", &numOfStrings) < 0 )
    {
        assert(!"failure on scanf");;    
    }
    // printf("Number of strings: %d\n", numOfStrings);
    
    stringVec.reserve(numOfStrings);
    
    // read the strings
    for (int i = 0 ; i < numOfStrings ; i++)
    {
        if ( scanf("%s\n", tmpString) < 0 )
            assert(!"failure on scanf");
        stringVec.emplace_back(tmpString);
    }
    
    if ( scanf("%d\n", &numOfQueries) < 0 )
    {
        assert(!"failure on scanf");
    }
    // printf("Number of queries: %d\n", numOfQueries);

    for (int i = 0 ; i < numOfQueries ; i++)
    {
        if ( scanf("%s\n", tmpString) < 0)
            assert(!"failure on scanf");
        queryVec.emplace_back(tmpString);
        ScanData(stringVec, std::string(tmpString));
    }


    return 0;
}

