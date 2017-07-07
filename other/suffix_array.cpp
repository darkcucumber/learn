#include <iostream>
#include <random>
#include <ctime>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

// construct suffix array
constexpr int alphabetLength = 4;
char alphabet[alphabetLength] = {'A', 'D', 'C', 'B'};

void BuildSuffixArray(const std::string & inputString, std::vector<int> & suffixArray)
{
	assert(suffixArray.empty());
	if (inputString.empty())
	{
		return;
	}

	auto inputStringSize = inputString.size();
	for (int i = inputStringSize - 1 ; i >= 0 ; --i)
	{
		suffixArray.emplace_back(i);
	}

	std::sort(	suffixArray.begin(), 
				suffixArray.end(), 
				[inputStringSize, &inputString] (int i, int j) -> bool 
				{
					int res = inputString.substr(i).compare(inputString.substr(j)); 
					return !( res > 0 ? true : false);
				});

	for (const auto offset : suffixArray)
	{
		printf("%d %s\n", offset, inputString.substr(offset).c_str());
	}
}

int main()
{
	int stringLength = 15;
	std::string str;
	str.reserve(stringLength);
	// create a long string that consists of the characters in the alphabet
	for (int i = 0 ; i < stringLength ; ++i)
	{
		str += alphabet[ (rand() % alphabetLength) ];
	}
	// printf("%s\n", str.c_str());
	std::vector<int> suffixArray;
	BuildSuffixArray(str, suffixArray);
	return 0;
}