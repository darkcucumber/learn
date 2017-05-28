#include <stdio.h>

/*
* Running "$ size a.out" yields segment sizes for different scenarios.
* If arr is not initialized, it is kept inside BSS. If it is initialized 
* (upon definition), it is moved to the DATA segment.
* TEXT segment is significantly affected by optimizations. 
*/

int arr[1000] = {1};

int main()
{
  printf("%s", "Hello World");
  char bigarray[1000];
  return 0;
}
