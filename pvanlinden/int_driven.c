#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

// system stuff
#include <sys/ioctl.h>
#include <stropts.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

// signal handling
#include <signal.h>

#define TRUE 1
#define FALSE 0

int CHARS = 0;
/*
*  Shouldn't really call standard routines inside signal handlers...
*/
void Handler(int signal)
{
	printf("Calling handler for %d characters\n", CHARS);
 	char c;
 	while ((c = getchar()) != EOF && c != '\n')
 		printf("%c");
 	printf("\n");

}

void IntHandler(int signal)
{
	printf("\nReceived interrupt signal. Shutting down...\n");
	exit(0);
}

int main()
{
	// struct sigaction new_action;
	// new_action.sa_handler = Handler;
	// sigemptyset(&new_action.sa_mask);
	// new_action.sa_flags = 0;
	// sigaction(SIGIO, &new_action, NULL);
	// set signal handler
	if ( SIG_ERR == signal(SIGIO, Handler))
	{
		abort();
	}
	// system("stty raw");
	// if ( SIG_ERR == signal(SIGINT, IntHandler))
	// {
	// 	abort();
	// }

	// errno = 0;
	// if ( ioctl(0, I_SETSIG, S_RDNORM) == -1)
	// {
	// 	printf("dupa\n");
	// }
	if (fcntl(0, F_SETSIG, 0) == -1)
	{
		printf("kutes\n");
		abort();
	}

	while( TRUE )
	{
		CHARS = 0;
		ioctl(0, FIONREAD, &CHARS);
		if (CHARS > 0)
			raise(SIGIO);
		// printf("\nReady to read %d characters\n", i);
		// sleep(1);
	}
	// system("stty cooked echo");
	return 0;
}