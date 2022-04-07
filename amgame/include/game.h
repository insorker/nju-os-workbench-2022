#include <am.h>
#include <amdev.h>
#include <klib.h>
#include <klib-macros.h>
#include <snake.h>

// void splash();
void print_key();

void draw_snake(Snake *sk);
void draw_snake_move(Snake *sk, Direction dir);
