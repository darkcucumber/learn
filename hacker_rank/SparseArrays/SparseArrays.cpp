#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <cstring>
#include "SparseArrays.h"

void ScanData(const StringVec & strings, const std::string & pattern)
{
    int occurred = 0;
    for (int i = 0 ; i < strings.size() ; i++)
    {
        const std::string & currentString = strings[i];
        occurred = currentString.compare(pattern) == 0 ? occurred + 1 : occurred;
    }
    printf("%d\n", occurred);
}
