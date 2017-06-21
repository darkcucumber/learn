#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <unistd.h>

enum STATES {DEFAULT = 0, FILE_OPEN = 1, FILE_CLOSE = 2};
int CHARS = 0;
FILE * file = NULL;
int CURRENT_STATE = DEFAULT;

void (*stateFn[4])(char*);



void clumsySignal(int signal)
{
	CURRENT_STATE = FILE_OPEN;
}

void defaultState(char * filename)
{
	printf("\nProgram in default state\n");
}

void fileOpen(char * filename)
{
	printf("\nEntering FILE_OPEN\n");
	if ( (file = fopen(filename, "r")) == NULL)
	{
		printf("\nCould not open file %s\n", filename);
		abort();
	}

	char c;
	while (((c = fgetc(file)) != EOF) && (c != '\n'))
		putchar(c);
	printf("\n");
	// set next state
	CURRENT_STATE = FILE_CLOSE;	
}

void fileClose(char * filename)
{
	printf("\nEntering FILE_CLOSE\n");
	if (file)
	{
		fclose(file);
		file = NULL;
		// set next state
		CURRENT_STATE = DEFAULT;
		return;
	}
	printf("Invalid program state. Aborting.\n");
	abort();
}

void runState(char * filename)
{
	// call the function
	(*stateFn[CURRENT_STATE])(filename);
}

int main(int argc, char ** argv)
{
	// assign state handling functions
	stateFn[0] = defaultState;
	stateFn[1] = fileOpen;
	stateFn[2] = fileClose;	

	if (argc == 1)
		abort();

	if (SIG_ERR == signal(SIGINT, clumsySignal))
		abort();
	
	while (1)
	{
		runState(argv[1]);
		sleep(1);
	}

	return 0;
}