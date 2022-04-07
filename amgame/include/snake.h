#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_INIT_SIZE 1
#define SNAKE_MAX_SIZE  10

typedef enum { NONE=0, UP=-1, DOWN=1, LEFT=-1, RIGHT=1 } STEP;
typedef struct Direction {
	STEP x, y;
} Direction;
typedef struct Position {
	int x, y;
} Position;

typedef struct SnakeBody {
	Direction dir;
	Position  pos;
} SnakeBody;

typedef struct Snake {
	int size;
	SnakeBody body[SNAKE_MAX_SIZE + 1];
} Snake;

void sk_init(Snake *sk);
void sk_move(Snake *sk, Direction dir);

#endif
