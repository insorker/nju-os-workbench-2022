#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
	char *exec_argv[] = { "yes", NULL };
	execve("yes", exec_argv, envp);
	perror(argv[0]);
}
