#include <kernel.h>
#include <stdio.h>
#include <thread.h>

static void entry(int tid) {
	void *addr = pmm->alloc(128);
	pmm->free(addr);
	addr = pmm->alloc(128);
	pmm->free(addr);
}
static void finish() { printf("End\n"); }

int main() {
	pmm->init();
	for (int i = 0; i < 1; i++) {
		create(entry);
	}
	
	join(finish);
}
