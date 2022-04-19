#include <kernel.h>
#include <stdio.h>
#include <thread.h>
#include <common.h>

Area heap = {};

static void entry(int tid) { }
static void finish() { printf("End\n"); }

int main() {
	pmm_init();
	entry(1);
	finish();
}
