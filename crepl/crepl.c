#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  static char line[4096];
  while (1) {
    printf("crepl> ");
    fflush(stdout);
    if (!fgets(line, sizeof(line), stdin)) {
			// error
      break;
    }
		int len = strlen(line);
		if (len >= 3 && !strncmp(line, "int", 3)) {
			printf("%s\n", line);
		}

    printf("Got %zu chars.\n", strlen(line)); // ??
  }
}
