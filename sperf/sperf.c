#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#define zassert(x, s) \
	do { if ((x) == 0) { printf("%s\n", s); assert((x)); } } while (0)

char buf[BUFSIZ];

int main(int argc, char *argv[], char *envp[]) {
	zassert(argc >= 2, "need at least one argument");

	char *strace_argv[] = { "strace", "-r", argv[1], NULL };
	int pipefd[2];
	int pid;

	zassert(pipe(pipefd) == 0, "create pipe failed");
	
	pid = fork();
	if (pid == 0) {
		// 关闭stderr
		close(2);
		// 将stderr接到管道的输入，stderr将输出到管道的输入
		dup2(pipefd[1], 2);
		close(pipefd[1]);
		// 关闭stdout（比如ls，会输出到stdout）
		close(1);
		// 关闭管道输出，用不到
		close(pipefd[0]);

		execve("/bin/strace", strace_argv, envp);
		zassert(0, "execve failed");
	}
	else {
		// 关掉父进程的管道输入，不然管道输出会阻塞
		close(pipefd[1]);
		double time;
		char name[100];

		while (fgets(buf, sizeof(buf), fdopen(pipefd[0], "r"))) {
			sscanf(buf, "%lf %s", &time, name);
			for (int i = 0; name[i]; i ++ ) {
				if (name[i] == '(') {
					name[i] = '\0';
					break;
				}
			}
			printf("%lf %s\n", time, name);
		}

		exit(0);
	}
}
