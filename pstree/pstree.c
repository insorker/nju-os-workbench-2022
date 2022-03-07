#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#include <assert.h>

#define VERSION "Version: 0.0.1\n"

struct process_state {
	int pid;
	int ppid;
	char *name;
};

static struct option longopts[] = {
	{ "show-pids",		0, NULL, 'p' },
	{ "numeric-sort",	0, NULL, 'n' },
	{ "version",		0, NULL, 'V' },
	{ 0,				0, 0,	 0   }
};

void getProcessState();
void printVersion();

int main(int argc, char *argv[]) {
	char opt;
	int option_index;

	if (argc == 1) {
		getProcessState();
	}

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

	return 0;
}

void getProcessState() {
	DIR *d;
	struct dirent *dir;

	d = opendir("/proc");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
}

void printVersion() {
	fprintf(stdout, VERSION);
}
