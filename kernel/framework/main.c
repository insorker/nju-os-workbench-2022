#include <kernel.h>
#include <klib.h>

void alloc(int sz) {
	uintptr_t a = (uintptr_t)pmm->alloc(sz);
	uintptr_t align = a & -a;

	printf("Alloc %d -> %p align = %d\n", sz, a, align);
	assert(a && align >= sz);
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
