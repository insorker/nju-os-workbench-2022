#include <game.h>
#include <stdio.h>

#define FPS 30
static int game_state = 0;

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
	dir = sk.dir;

	draw_snake(&sk);

	while (1) {
		if (game_state != 0) {
			game_state = 0;
			sk_init(&sk);
		}

		while (curr_frame < next_frame) {
			get_key(&dir);
			curr_frame = io_read(AM_TIMER_UPTIME).us / (1000000 / FPS);
		}
		if (curr_frame % 15 == 0) {
			draw_snake_move(&sk, dir, &game_state);
		}

		next_frame += 1;
	}
	return 0;
}
