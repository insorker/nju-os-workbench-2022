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
		// 关闭stderr
		close(2);
		// 将stderr接到管道的输入，stderr将输出到管道的输入
		dup(pipefd[1]);
		close(pipefd[1]);
		// 关闭stdout（比如ls，会输出到stdout）
		close(1);
		// 关闭管道输出，用不到
		close(pipefd[0]);

		execve("/bin/strace", strace_argv, envp);
		zassert(0, "execve failed");
	}
	else {
		char buf[1024];
		int len = read(pipefd[0], buf, sizeof(buf));
		write(0, buf, len);
	}
}
