#include <kernel.h>
#include <stdio.h>
#include <thread.h>

static void entry(int tid) { pmm->alloc(128); }
static void finish() { printf("End\n"); }

int main() {
	pmm->init();
}
