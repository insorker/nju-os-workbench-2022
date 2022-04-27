#include <common.h>
#include <assert.h>
#ifdef TEST
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

#define HB_MAX (1 << 16)
#define HB_MIN (1 << 4)
#define HB_HEAD_SIZE (2 * HB_MAX / HB_MIN + 1)
#define HB_CONT_SIZE HB_MAX
#define HB_WHOL_SIZE (HB_HEAD_SIZE + HB_CONT_SIZE)

typedef struct heap_block {
	void *head;
	void *cont;
	struct heap_block *next;
} heap_block;
static size_t heap_block_number;
static void  *heap_block_start;

static void hb_init(heap_block *hb, void *start) {
	hb->head = start;
	hb->cont = start + HB_HEAD_SIZE;
	hb->next = NULL;

	memset(hb->head, 0, HB_HEAD_SIZE);
}

static size_t hb_check_size(size_t size) {
	if (size >= heap_block_number * HB_WHOL_SIZE) {
		return 1;
	}
	return 0;
}

static size_t hb_check_addr(void *addr) {
	if (addr <  heap_block_start ||
			addr >= heap_block_start + heap_block_number * HB_WHOL_SIZE) {
		return 1;
	}
	return 0;
}

static size_t lowbit(size_t x) {
	return x & -x;
}

static size_t hb_roundup(size_t size) {
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

static void hb_pushup(char *head, size_t idx) {
	size_t le = idx >> 1, ri = le + 1;
	if (head[le] & 1 && head[ri] & 1) {
		head[idx] = 3;
	}
	else {
		head[idx] = 2;
	}
}

// 1 occupied
// 2 not occupied, but splited
// 3 occupied and splited
static size_t hb_find(char *head, size_t idx, size_t block_size, size_t size) {
	if (head[idx] == 1 || head[idx] == 3) {
		return 0;
	}
	/* printf("%ld\n", idx); */

	if (head[idx] == 0 && block_size == size) {
		printf("FIND!\n");
		head[idx] = 1;
		return idx;
	}

#ifndef TEST
	assert(block_size != 16);
#endif

	size_t le = idx << 1, ri = le + 1;
	if ((le = hb_find(head, le, block_size >> 1, size))) {
		hb_pushup(head, idx);
		return le;
	}
	if ((ri = hb_find(head, ri, block_size >> 1, size))) {
		hb_pushup(head, idx);
		return ri;
	}

	hb_pushup(head, idx);
	return 0;
}

static void *hb_idx2addr(void *cont, size_t idx, size_t size) {
	size_t start = idx;
	for (size_t i = lowbit(start); start - i; ) {
		start -= lowbit(start);
		i = lowbit(start);
	}
	return cont + (idx - start) * size;
}

static size_t hb_free(char *head, void *cont, size_t idx, size_t size, void *addr) {
	if (idx >= HB_HEAD_SIZE) { return 1; }
	if (hb_idx2addr(cont, idx, size) == addr) {
		head[idx] = 0;
		return 0;
	}
	else {
		if (!hb_free(head, cont, idx << 1, size >> 1, addr)) {
			hb_pushup(head, idx);
			return 0;
		}
		if (!hb_free(head, cont, (idx << 1) + 1, size >> 1, addr)) {
			hb_pushup(head, idx);
			return 0;
		}
	}

	return 1;
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
	size = hb_roundup(size);

	if (!hb_check_size(size)) {
		heap_block *hb_start;
		size_t hb_idx;

		for (size_t i = 0; i < heap_block_number; i++) {
			printf("%ld\n", i);
			hb_start = (heap_block *)(heap.start + i * sizeof(heap_block));
			hb_idx = hb_find(hb_start->head, 1, HB_MAX, size);
			if (hb_idx) {
				printf("%ld\n", hb_idx);
				return hb_idx2addr(hb_start->cont, hb_idx, size);
			}
		}
	}

  return NULL;
}

static void kfree(void *ptr) {
	if (hb_check_addr(ptr)) { assert(0); }

	uintptr_t addr = (uintptr_t)ptr - (uintptr_t)heap_block_start;
	if (addr % 16 != 0) { assert(0); }

	heap_block *hb = heap.start + addr / HB_MAX * sizeof(heap_block);
	hb_free(hb->head, hb->cont, 1, HB_MAX, ptr);
}

#ifdef TEST
#define HEAP_SIZE (1 << 27)
static void pmm_init() {
	char* ptr = malloc(HEAP_SIZE);
	heap.start = ptr;
	heap.end   = ptr + HEAP_SIZE;
	printf("Got %d MiB heap: [%p, %p)\n", HEAP_SIZE >> 20, heap.start, heap.end);

	kinit();
}
#else
static void pmm_init() {
  uintptr_t pmsize = ((uintptr_t)heap.end - (uintptr_t)heap.start);
  printf("Got %d MiB heap: [%p, %p)\n", pmsize >> 20, heap.start, heap.end);

	kinit();
}
#endif

MODULE_DEF(pmm) = {
  .init  = pmm_init,
  .alloc = kalloc,
  .free  = kfree,
};
