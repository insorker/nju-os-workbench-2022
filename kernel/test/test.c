#include <kernel.h>
#include <stdio.h>
#include <thread.h>

static void entry(int tid) { }
static void finish() { printf("End\n"); }

int main() {
	pmm_init();
	entry(1);
	finish();
}
