#include <kernel.h>
#include <klib.h>

void alloc(int sz) {
	void *a = pmm->alloc(sz);
	pmm->free(a);
}

void pmm_test() {
	alloc(1);
	alloc(5);
	alloc(10);
	alloc(32);
	alloc(4096);
	alloc(4096);
	alloc(4096);
}

int main() {
  ioe_init();
	os->init();
	pmm_test();
	/* cte_init(os->trap); */
  /* mpe_init(os->run); */
  return 1;
}
