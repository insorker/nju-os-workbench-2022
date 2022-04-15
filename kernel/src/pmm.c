#include <common.h>

static void *kalloc(size_t size) {
  return NULL;
}

static void kfree(void *ptr) {
}

#ifdef TEST
static void pmm_init() {
	char* pmsize = malloc(HEAP_SIZE);
	heap.start = ptr;
	heap.end   = ptr + HEAP_SIZE;
	printf("Got %d MiB heap: [%p, %p)\n", HEAP_SIZE >> 20, heap.start, heap.end);
#else
static void pmm_init() {
  uintptr_t pmsize = ((uintptr_t)heap.end - (uintptr_t)heap.start);
  printf("Got %d MiB heap: [%p, %p)\n", pmsize >> 20, heap.start, heap.end);
}
#endif

MODULE_DEF(pmm) = {
  .init  = pmm_init,
  .alloc = kalloc,
  .free  = kfree,
};
