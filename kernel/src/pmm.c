#include <common.h>
#ifdef TEST
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

#define BLOCK_MAX (1 << 16)
#define BLOCK_MIN (1 << 4)
#define HB_HEAD_SIZE (2 * BLOCK_MAX / BLOCK_MIN + 1)
#define HB_CONT_SIZE BLOCK_MAX
#define HB_WHOL_SIZE (HB_HEAD_SIZE + HB_CONT_SIZE)

typedef struct heap_block {
	void *head;
	void *cont;
	struct heap_block *next;
} heap_block;
static size_t heap_block_number;
static void  *heap_block_start;

void hb_init(heap_block *hb, void *start) {
	hb->head = start;
	hb->cont = start + HB_HEAD_SIZE;
	hb->next = NULL;

	memset(hb->head, 0, HB_HEAD_SIZE);
}

size_t hb_check(uintptr_t del) {
	if (del % 16 != 0) {
		return 0;
	}
	return 0;
}

static size_t lowbit(size_t x) {
	return x & -x;
}

static size_t hb_roundup(size_t size) {
	if (size >= heap_block_number * HB_WHOL_SIZE) { return 0; }

	size_t new_size = 0, cnt = 0;
	while (size) {
		new_size = lowbit(size);
		size -= lowbit(size);
		cnt++;
	}
	if (cnt > 1) { new_size <<= 1; }
	if (new_size < 16) { new_size = 16; }

	return new_size;
}

size_t hb_free(void *addr) {
	if (addr <  heap_block_start ||
			addr >= heap_block_start + heap_block_number * HB_WHOL_SIZE) {
		return 1;
	}

	uintptr_t del = (uintptr_t)addr - (uintptr_t)heap_block_start;
	
}

static void kinit() {
  uintptr_t pmsize = ((uintptr_t)heap.end - (uintptr_t)heap.start);
	heap_block_number = pmsize / (HB_WHOL_SIZE + sizeof(heap_block));
	heap_block_start  = heap.start + heap_block_number * sizeof(heap_block);
	
	for (size_t i = 0; i < heap_block_number; i++) {
		heap_block *hb = (heap_block *)(heap.start + i * sizeof(heap_block));
		hb_init(hb, heap_block_start + i * HB_WHOL_SIZE);
	}
}

static void *kalloc(size_t size) {
	kinit();
	printf("%ld\n", hb_roundup(4));
	printf("%ld\n", hb_roundup(3));
	printf("%ld\n", hb_roundup(16));
	printf("%ld\n", hb_roundup(17));
	printf("%ld\n", hb_roundup(20));
	printf("%ld\n", hb_roundup(127));
	printf("%ld\n", hb_roundup(256));

  return NULL;
}

static void kfree(void *ptr) {
}

#ifdef TEST
#define HEAP_SIZE (1 << 27)
static void pmm_init() {
	char* ptr = malloc(HEAP_SIZE);
	heap.start = ptr;
	heap.end   = ptr + HEAP_SIZE;
	printf("Got %d MiB heap: [%p, %p)\n", HEAP_SIZE >> 20, heap.start, heap.end);
}
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
