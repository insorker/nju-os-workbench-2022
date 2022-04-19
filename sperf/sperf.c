#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#define zassert(x, s) \
	do { if ((x) == 0) { printf("%s\n", s); assert((x)); } } while (0)

int main(int argc, char *argv[], char *envp[]) {
	zassert(argc >= 2, "need at least one argument");

	char *strace_argv[] = { "strace", argv[1], NULL };
	int pipefd[2];
	int pid;

	zassert(pipe(pipefd) == 0, "create pipe failed");
	
	pid = fork();
	if (pid == 0) {
		printf("%d ", pipefd[1]);
		close(0);
		dup(pipefd[1]);

		/* execve("/bin/strace", strace_argv, envp); */
		/* zassert(0, "execve failed"); */
	}
	else {
	}
}
