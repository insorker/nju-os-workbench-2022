#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
	if (argc < 3) exit(1);
	/* execve(argv[1], argv + 1, envp); */
	if ((argv + 1)[2] == NULL) {
		printf("%d\n", 123);
	}
	printf("%s", (argv + 1)[0]);
	/* execve("strace", argv + 1, envp); */
}
