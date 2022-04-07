#include <game.h>
#include <stdio.h>
#include <snake.h>

#define KEYNAME(key) \
  [AM_KEY_##key] = #key,
static const char *key_names[] = {
  AM_KEYS(KEYNAME)
};

void get_key(Direction *dir) {
  AM_INPUT_KEYBRD_T event = { .keycode = AM_KEY_NONE };
  ioe_read(AM_INPUT_KEYBRD, &event);
  if (event.keycode != AM_KEY_NONE && event.keydown) {
    printf("Key pressed: ");
	switch (*key_names[event.keycode]) {
	case 'W': dir->x = NONE, dir->y = UP;    break;
	case 'S': dir->x = NONE, dir->y = DOWN;  break;
	case 'A': dir->x = LEFT, dir->y = DOWN;  break;
	case 'D': dir->x = RIGHT, dir->y = DOWN; break;
	default: break;
	}
	printf(key_names[event.keycode]);
    printf("\n");
  }
}
