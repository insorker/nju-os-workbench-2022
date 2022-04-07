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
	Direction dir;
	sk_init(&sk);
	dir = sk.body[0].dir;

	draw_snake(&sk);

	printf("Press any key to see its key code...\n");
	while (1) {
		while (curr_frame < next_frame) {
			get_key(&dir);
			curr_frame = io_read(AM_TIMER_UPTIME).us / (1000000 / FPS);
		}
		draw_snake_move(&sk, dir);

		next_frame += 1000000 / FPS;
	}
	return 0;
}
