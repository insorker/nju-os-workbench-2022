#ifndef COMMOM_H
#define COMMON_H

#include <kernel.h>
#include <stdio.h>

typedef struct {
	void *start, *end;
} Area;
Area heap;

#endif
