#include <game.h>
#include <stdio.h>
#include <snake.h>

#define KEYNAME(key) \
  [AM_KEY_##key] = #key,
static const char *key_names[] = {
  AM_KEYS(KEYNAME)
};

void get_key(Snake *sk) {
  AM_INPUT_KEYBRD_T event = { .keycode = AM_KEY_NONE };
  ioe_read(AM_INPUT_KEYBRD, &event);
  if (event.keycode != AM_KEY_NONE && event.keydown) {
    printf("Key pressed: ");
	switch (*key_names[event.keycode]) {
	case 'W': sk->dir.x = NONE, sk->dir.y = UP;    break;
	case 'S': sk->dir.x = NONE, sk->dir.y = DOWN;  break;
	case 'A': sk->dir.x = LEFT, sk->dir.y = NONE;  break;
	case 'D': sk->dir.x = RIGHT, sk->dir.y = NONE; break;
	default: break;
	}
	printf(key_names[event.keycode]);
    printf("\n");
  }
}
