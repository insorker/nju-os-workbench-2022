#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
	execve("yes", { "yes", NULL }, envp);
	perror(argv[0]);
}
