#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

static int wrapper_num;
static char *wrapper_func[] = {
	"int ", "__expr_wrapper_", "(){return ", ";}\n",
};
static char wrapper_file[] = "/tmp/crepl_tmp.c";
static FILE *wrapper_fd;
static char *const gcc_argv[] = {
	"-fPIC",
	"-shared",
	wrapper_file,
	"-o /tmp/crepl_tmp.so",
	NULL
};

void compile() {
	if (fork() == 0) {
		execvp("gcc", gcc_argv);
		perror("gcc error");
		exit(-1);
	}
}

int main(int argc, char *argv[]) {
	// empty the file
	wrapper_fd = fopen(wrapper_file, "w");
	fclose(wrapper_fd);

  static char line[4096];
	void *handle;
	int (*wrapper)();
	char wrapper_buf[100];
	
  while (1) {
    printf("crepl> ");
    fflush(stdout);
    if (!fgets(line, sizeof(line), stdin)) {
			// read failed
      break;
    }

		int len = strlen(line);
		if (len >= 3 && !strncmp(line, "int", 3)) {
			// function define
		}
		else {
			// expression
			wrapper_fd = fopen(wrapper_file, "a");
			fprintf(wrapper_fd, "%s%s%d%s%s%s",
					wrapper_func[0], wrapper_func[1], wrapper_num, wrapper_func[2], line, wrapper_func[3]);
			fclose(wrapper_fd);

			compile();
			/* handle = dlopen("./crepl_tmp.so", RTLD_LAZY); */
			/* sscanf(wrapper_buf, "%s%d", wrapper_func[1], &wrapper_num); */
			/* wrapper = (int (*)()) dlsym(handle, wrapper_buf); */
			/* wrapper(); */
			/* wrapper_num++; */
		}
  }
}