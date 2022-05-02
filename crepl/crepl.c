#include <stdio.h>
#include <string.h>

static int wrapper_num;
static char *wrapper[] = {
	"int __expr_wrapper_", "(){return ", ";}\n",
};
static char *file_path = "/tmp/crepl_tmp";

/* #define wrapper_assemble() \ */
/*   (wrapper[0] #wrapper_num) */
#define wrapper_assemble(a, b) \
	b

int main(int argc, char *argv[]) {
	FILE *fp = fopen(file_path, "w");
	fclose(fp);
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
			// function define
		}
		else {
			// expression
			fp = fopen(file_path, "a");
			fprintf(fp, "%s%d%s%s%s", wrapper[0], wrapper_num, wrapper[1], line, wrapper[2]);
			fclose(fp);
			wrapper_num++;
		}

    printf("Got %zu chars.\n", strlen(line)); // ??
  }

}
