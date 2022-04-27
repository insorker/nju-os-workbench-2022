#include <common.h>

static void os_init() {
  pmm->init();
}

static void os_run() {
  for (const char *s = "Hello World from CPU #*\n"; *s; s++) {
#ifndef TEST
    putch(*s == '*' ? '0' + cpu_current() : *s);
#else
		/* putchar(*s == '*' ? '0' + cpu_current() : *s); */
#endif
  }
  while (1) ;
}

MODULE_DEF(os) = {
  .init = os_init,
  .run  = os_run,
};
