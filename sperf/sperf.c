#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
	if (argc < 2) exit(1);
	char *strace_argv[] = { "strace", argv[1], NULL };
	execve("/bin/strace", strace_argv, envp);
}
