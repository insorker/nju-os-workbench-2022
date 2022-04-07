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
	case 'W': dir->x = UP,   dir->y = NONE;  break;
	case 'S': dir->x = DOWN, dir->y = NONE;  break;
	case 'A': dir->x = NONE, dir->y = LEFT;  break;
	case 'D': dir->x = NONE, dir->y = RIGHT; break;
	default: break;
	}
	printf(key_names[event.keycode]);
    printf("\n");
  }
}
