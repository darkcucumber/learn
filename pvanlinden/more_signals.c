#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf jumper;
jmp_buf segvJump;
jmp_buf busJump;

short int looping = 1;

void handleSIGINT(int singal)
{
	longjmp(jumper, 0);
}

void handleSIGSEGV(int signal)
{
	printf("\nExitting the main function after hitting potezny segmentation fault.\n");
	longjmp(segvJump, 1);
}

void handleSIGBUS(int signal)
{
	printf("\nExitting the main function after hitting potezny bus error.\n");
	longjmp(busJump, 1);
}

union 
{
	char a[10];
	int i;
} badBus;

int main()
{
	signal(SIGINT, handleSIGINT);
	signal(SIGSEGV, handleSIGSEGV);
	signal(SIGBUS, handleSIGBUS);
	looping = setjmp(jumper);

	while(!looping)
		;
	printf("\nExitting the main function peacefully after encountering SIGINT.\n");
	int * pSEGV = NULL;
	long int i = 0;
	looping = setjmp(segvJump);
	if ( !looping )
	{
		pSEGV = (int*) malloc(100 * sizeof(int));
		for (i = 0 ; i < 10000000 ; i++)
			*(pSEGV + i) = 1;
	}
	printf("Causing bus error.\n");
	int * decha;
	char * kicha;
	if (!setjmp(busJump))
	{
		decha = (int*) &(badBus.a[8]);
		*decha = 15;
	}
	return 0;
}