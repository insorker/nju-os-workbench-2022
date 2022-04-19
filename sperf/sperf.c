#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
	char *exec_argv[] = { "yes", NULL };
	execve("yes", exec_argv, NULL);
	perror(argv[0]);
	exit(EXIT_FAILURE);
}
