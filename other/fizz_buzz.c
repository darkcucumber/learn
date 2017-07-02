#include <stdio.h>

void Talk(int i)
{
	if (0 == (i % 3) )
		printf("Fizz");

	if (0 == (i % 5))
		printf("Buzz");

	if ((i % 3 ) == 0 || (i % 5 ) == 0)
		printf("\n");
}

int main()
{
	int i;
	for (i = 1 ; i < 100 ; i++)
		Talk(i);
	return 0;
}