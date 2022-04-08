#include "co.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <setjmp.h>
#include <string.h>
#include <assert.h>

#define Assert(x, s) \
	({ if (!x) { printf("%s", s); assert(x); } })

static inline void stack_switch_call(void *sp, void *entry, uintptr_t arg) {
	asm volatile (
#if __x86_64__
		"movq %0, %%rsp; movq %2, %%rdi; jmp *%1"
			: : "b"((uintptr_t)sp), "d"(entry), "a"(arg) : "memory"
#else
		"movl %0, %%esp; movl %2, 4(%0); jmp *%1"
			: : "b"((uintptr_t)sp - 8), "d"(entry), "a"(arg) : "memory"
#endif
	);
}

#define CO_STACK_SIZE (1 << 16)
enum co_status {
	CO_NEW = 1, // 新创建，还未执行过
	CO_RUNNING, // 已经执行过
	CO_WAITING, // co_wait等待中
	CO_DEAD,    // 已经结束，还未释放资源
};

struct co {
	int  id;					// co_pool id
	char *name;					// 协程名字
	void (*func)(void *);		// co_start 入口函数地址
	void *arg;					// 入口函数参数

	enum co_status	status;		// 协程状态
	struct co *		waiter; 	// 是否有其他协程在等待当前协程，如果有，优先执行
	jmp_buf			context;	// 协程栈的上下文
	uint8_t			stack[CO_STACK_SIZE];	// 协程栈
};

struct co *current;

#define CO_POOL_SIZE 128
struct co *co_pool[CO_POOL_SIZE];
int co_pool_add_idx, co_pool_yield_idx;

void co_pool_add(struct co *co) {
	int i, add_idx;
	for (i = 0; i < CO_POOL_SIZE; i ++ ) {
		add_idx = (co_pool_add_idx + i) % CO_POOL_SIZE;
		if (!co_pool[add_idx]) {
			co_pool_add_idx = add_idx;
			co_pool[add_idx] = co;
			co->id = add_idx;
			return;
		}
	}
	Assert((i == CO_POOL_SIZE), "Number of co has exceeded the upper limit\n");
}

void co_pool_remove(struct co *co) {
	co_pool[co->id] = NULL;
}

static void co_run() {
	struct co *co = current;

	if (co->status == CO_NEW) {
		co->status = CO_RUNNING;
		co->func(co->arg);
		co->status = CO_DEAD;
		co_pool_remove(co);
	}
	else if (co->status == CO_RUNNING) {
		longjmp(co->context, 1);
	}
	else if (co->status == CO_WAITING) {
		free(co);
	}
}

struct co *co_start(const char *name, void (*func)(void *), void *arg) {
	struct co *co = (struct co *)malloc(sizeof(struct co));
	co->name = (char *)malloc(sizeof(name));
	strcpy(co->name, name);
	co->func = func;
	co->arg  = arg;

	co->status = CO_NEW;
	co->waiter = NULL;

	co_pool_add(co);

	return co;
}

void co_wait(struct co *co) {
	if (!co) {
		Assert(0, "Wait a non-existent co\n");
	}

	int val = setjmp(current->context);
	if (val == 0) {
		co->waiter = current;
		current = co;

		while (co->status != CO_DEAD) {
			co_run();
		}
		co->status = CO_WAITING;
		co_run();
		
		current = co->waiter;
		co_run();
	}
}

void co_yield() {
	int val = setjmp(current->context);
	if (val == 0) {
		int i, yield_idx;;
		for (i = 0; i < CO_POOL_SIZE; i ++ ) {
			yield_idx = co_pool_yield_idx + i;
			if (co_pool[yield_idx]) {
				current = co_pool[yield_idx];
				co_run();
				break;
			}
		}
	}
}

__attribute__((constructor)) void co_pool_init() {
	for (int i = 0; i < CO_POOL_SIZE; i ++ ) {
		co_pool[i] = NULL;
	}
	co_pool_add_idx = co_pool_yield_idx = 0;
}
