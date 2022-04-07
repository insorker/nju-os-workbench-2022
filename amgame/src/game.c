#include <game.h>
#include <stdio.h>

// Operating system is a C program!
int main(const char *args) {
	ioe_init();

	/* puts("mainargs = \""); */
	/* puts(args); // make run mainargs=xxx */
	/* puts("\"\n"); */

	Snake sk;
	/* Direction dir; */
	sk_init(&sk);  
	draw_snake(&sk);

	printf("Press any key to see its key code...\n");
	while (1) {
		print_key();
		/* draw_snake_move(&sk, dir);  */
	}
	return 0;
}
