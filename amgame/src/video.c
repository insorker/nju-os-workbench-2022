#include <game.h>
#include <snake.h>
#include <com.h>

static void draw_rect(int x, int y, int w, int h, uint32_t color) {
  uint32_t pixels[w * h]; // WARNING: large stack-allocated memory
  AM_GPU_FBDRAW_T event = {
    .x = x, .y = y, .w = w, .h = h, .sync = 1,
    .pixels = pixels,
  };
  for (int i = 0; i < w * h; i++) {
    pixels[i] = color;
  }
  ioe_write(AM_GPU_FBDRAW, &event);
}

static void draw_snake_body(int x, int y, uint32_t color) {
	x = x * GRID_SIZE + GRID_PADDING, y = y * GRID_SIZE + GRID_PADDING;
	draw_rect(x, y, SNAKE_SIZE, SNAKE_SIZE, color);
}

void draw_snake(Snake *sk) {
	for (int i = 0; i < sk->size; i ++ ) {
		draw_snake_body(
			sk->body[i].pos.x,
			sk->body[i].pos.y,
			SNAKE_COLOR
		);
	}
}

void draw_snake_move(Snake *sk, Direction dir) {
	draw_snake_body(
		sk->body[0].pos.x,
		sk->body[0].pos.y,
		GRID_COLOR
	);
	sk_move(sk, dir);
	draw_snake_body(
		sk->body[sk->size - 1].pos.x,
		sk->body[sk->size - 1].pos.y,
		SNAKE_COLOR
	);
}

/* static void draw_tile(int x, int y, int w, int h, uint32_t color) { */
/*   uint32_t pixels[w * h]; // WARNING: large stack-allocated memory */
/*   AM_GPU_FBDRAW_T event = { */
/*     .x = x, .y = y, .w = w, .h = h, .sync = 1, */
/*     .pixels = pixels, */
/*   }; */
/*   for (int i = 0; i < w * h; i++) { */
/*     pixels[i] = color; */
/*   } */
/*   ioe_write(AM_GPU_FBDRAW, &event); */
/* } */
/*  */
/* void splash() { */
/*   init(); */
/*   for (int x = 0; x * SIDE <= w; x ++) { */
/*     for (int y = 0; y * SIDE <= h; y++) { */
/*       if ((x & 1) ^ (y & 1)) { */
/*         draw_tile(x * SIDE, y * SIDE, SIDE, SIDE, 0xffffff); // white */
/*       } */
/*     } */
/*   } */
/* } */
