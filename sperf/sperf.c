#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
	for (int i = 0; argv[i] != NULL; i ++ )
		printf("%d ", i);
	
	/* char *exec_argv[] = { "strace", "ls", NULL, }; */
	/* [> char *exec_envp[] = { "PATH=/bin", NULL, }; <] */
	/* char *exec_envp[] = { "", NULL, }; */
	/* [> execve("strace",          exec_argv, exec_envp); <] */
	/* execve("/bin/strace",     exec_argv, envp); */
	/* [> execve("/usr/bin/strace", exec_argv, exec_envp); <] */
	/* perror(argv[0]); */
	exit(EXIT_FAILURE);
}
