#include <stdlib.h>
#include <stdio.h>

void PrintArray(char ca[])
{
	printf("&ca %p | &(ca[0]) %p | &(ca[1]) %p\n", &ca, &(ca[0]), &(ca[1]));
}

void PrintPtr(char * pa)
{
	printf("&pa %p | &(pa[0]) %p | &(pa[1]) %p\n", &pa, &(pa[0]),  &(pa[1]));
}

char a[] = {'a', 'b', 'c', 'd'};

int main()
{
	/*
		This exercise program shows that the compiler treats 
		an array passed to a function as a pointer.
		Thus &arg, &(arg[0]) and &(arg[1]) have the same addresses. 

		Array is treated differently when it's not passed to a function but printed explicitly.
		Thus &arg does not match with the values seen in the functions. 
		&(arg[0]) and &(arg[1]) are the same as the ones inside the functions.
	*/
	
	PrintArray(a);
	PrintPtr(a);
	printf("&a %p | &(a[0]) %p | &(a[1]) %p\n", &a, &(a[0]), &(a[1]));
	return 0;
}