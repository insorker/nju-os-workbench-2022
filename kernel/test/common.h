#ifndef COMMOM_H
#define COMMON_H

#include <kernel.h>
#include <klib.h>
#include <klib-macros.h>

typedef struct {
	void *start, *end;
} Area;
Area heap;

#endif
