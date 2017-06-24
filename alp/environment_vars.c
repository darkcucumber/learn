#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <assert.h>

extern char ** environ;
const char * program_name;

void print_usage(FILE * stream, int exit_code)
{
	fprintf(stream, "Usage: %s options\n", program_name);
	fprintf(stream, "	-v --verbose 	Talk stuff during execution.\n"
					"	-h --help 		Display usage information.\n");
}

void parse_options(int argc, char ** argv, int * verbose)
{
	assert(argv && verbose);

	int next_option = 0;

	// read the program's name
	program_name = argv[0];

	// construct short options list
	const char * const short_options = "hv";

	// construct the options list
	const struct option long_options[] = {
		{"help",	0,	NULL, 	'h'},
		{"verbose",	0,	NULL,	'v'},
		{NULL,		0,	NULL,	 0}
	};

	do
	{
		next_option = getopt_long(	argc, 
									argv, 
									short_options, 
									long_options, NULL);

		switch (next_option)
		{
			case 'h':
				print_usage(stdout, 0);
				break;

			case 'v':
				*verbose = 1;
				break;

			case '?':
				print_usage(stderr, 1);
				break;

			case -1:
				break;

			default:
				abort();
		}

	} while(-1 != next_option);
}

int main(int argc, char ** argv)
{
	char ** var;
	int verbose = 0;
	
	parse_options(argc, argv, &verbose);

	for (var = environ ; ((*var) != NULL) && verbose ; ++var)
	{
		printf("%s\n", *var);
	}	

	char * variable = NULL;
	if ( ( (variable = getenv("PATH")) != NULL) && verbose)
		printf("PATH: %s\n", variable);


	if ( getenv("BROWAR_NAME") == NULL)
	{
		setenv("BROWAR_NAME", "BROK", 0);
		if (verbose)
			printf("%s\n", getenv("BROWAR_NAME"));
	}
	return 0;
}