#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>

jmp_buf buf;
jmp_buf sigsegv;

void banana()
{
	printf("in banana()\n");
	longjmp(buf, 1);
	printf("not reaching this part of code");
}

void SigSegvHandler(int signal)
{
	printf("Peaceful segfault.\n");
	longjmp(sigsegv, 1);
}

int main()
{
	if (setjmp(buf))
		printf("back in main\n");
	else
	{
		printf("first time through\n");
		banana();
	}

	// assign our signal handler to SIGSEGV
	if ( signal(SIGSEGV, SigSegvHandler) == SIG_ERR )
	{
		fprintf(stderr, "Could not set signal handler.\n");
		abort();
	}

	char * pointur = NULL;

	// lets play with pointers
	switch( setjmp(sigsegv) )
	{
		case 0:
			printf("Segfault time!\n");
			*pointur = 1;
			break;
		case 1:
			printf("Aborting program peacefully\n");
			break;
		default:
			abort();
	}
	return 0;
}