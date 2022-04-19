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
		// 关闭pipe输入
		close(pipefd[1]);
		// 重定向stderr到pipefd[1]，关闭stderr
		dup(2);
		close(2);
		// 关闭stdout（比如ls，会输出到stdout）
		close(1);
		// 关闭pipefd[0]，用不到
		close(pipefd[0]);

		execve("/bin/strace", strace_argv, envp);
		zassert(0, "execve failed");
	}
	else {
	}
}
