#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DUMBCOPY for (i = 0 ; i < 65536 ; i++) \
	destination[i] = source[i]

#define SMARTCOPY memcpy(destination, source, 65536)

int main ()
{
	char source[65536];
	char destination[65536];
	int i;
	int j;
	for (j = 0; j < 1000; j++)
SMARTCOPY;
	// DUMBCOPY;
	return 0;
}