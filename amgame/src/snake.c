#include <snake.h>
#include <am.h>
#include <com.h>
#include <stdio.h>

static int w, h;

static void init() {
	AM_GPU_CONFIG_T info = {0};
	ioe_read(AM_GPU_CONFIG, &info);
	w = info.width;
	h = info.height;
}

void sk_init(Snake *sk) { 
	init();

	sk->size = SNAKE_INIT_SIZE;
	for (int i = 0; i < sk->size; i++) {
		sk->body[i].pos = (Position){ 0, i };
		sk->body[i].dir = (Direction){ NONE, DOWN };
	}
}

static int sk_conflict(Snake *sk, int id) {
	if (id == 0)
		return 0;
	int x = sk->body[id].pos.x + sk->body[id].dir.x;
	int y = sk->body[id].pos.y + sk->body[id].dir.y;

	// conflict with bound
	if (x < 0 || x * GRID_SIZE >= w - SNAKE_SIZE ||
		y < 0 || y * GRID_SIZE >= w - SNAKE_SIZE)
		return 2;

	// conflict with body
	if (x == sk->body[id - 1].pos.x &&
		y == sk->body[id - 1].pos.y)
		return 1;
	return 0;
}

void sk_move(Snake *sk, Direction dir) {
	sk->body[sk->size].dir = dir;

	switch (sk_conflict(sk, sk->size - 1)) {
	case 1:
		return;
	case 2:
		printf("You Failed\n");
		halt(0);
		return;
		// game failed
	default:
		break;
	}

	for (int i = sk->size - 1; i >= 0; i--) {
		sk->body[i].pos.x = sk->body[i + 1].dir.x;
		sk->body[i].pos.y = sk->body[i + 1].dir.y;
		sk->body[i].dir.x = sk->body[i + 1].dir.x;
		sk->body[i].dir.y = sk->body[i + 1].dir.y;
	}
}
