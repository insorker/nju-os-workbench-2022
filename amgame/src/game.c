#include <game.h>
#include <stdio.h>

#define FPS 30

// Operating system is a C program!
int main(const char *args) {
	ioe_init();

	/* puts("mainargs = \""); */
	/* puts(args); // make run mainargs=xxx */
	/* puts("\"\n"); */

	int next_frame = 0;
	int curr_frame = 0;
	Snake sk;
	sk_init(&sk);

	draw_snake(&sk);

	printf("Press any key to see its key code...\n");
	while (1) {
		while (curr_frame < next_frame) {
			get_key(&sk);
			curr_frame = io_read(AM_TIMER_UPTIME).us / (1000000 / FPS);
			/* printf("%d\n", curr_frame); */
		}
		if (curr_frame % 15 == 0) {
			draw_snake_move(&sk);
		}

		next_frame += 1;
	}
	return 0;
}
