#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <assert.h>

static struct option longopts[] = {
	{ "show-pids",		0, NULL, 'p' },
	{ "numeric-sort",	0, NULL, 'n' },
	{ "version",		0, NULL, 'V' },
	{ 0,				0, 0,	 0   }
};

int main(int argc, char *argv[]) {
	char opt;
	int option_index;

	while ((opt = getopt_long(argc, argv, "pnV", longopts, &option_index)) != -1) {
		switch (opt) {
		case 'p':
			break;
		case 'n':
			break;
		case 'V':
			break;
		default:
			fprintf(stderr, "Error\n");
			exit(1);
		}
		printf("%c\n", opt);
	}
	printf("Hello\n"); 

	return 0;
}
