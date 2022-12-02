/**
 * @file xstack.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of interface "xstack".
 * @version 1.0.0
 * @date 2022-11-25
 *
 */

#include "xstack.h"
#include <stdlib.h>
#include <assert.h>

struct xstack {
	xlist		*l;
	/* FIXME: Use "size_t" instead */
	int		 size;
};

xstack *xstack_new(void)
{
	xstack *newstack;
	newstack = (xstack *)malloc(sizeof *newstack);
	if (!newstack)
		XRAISE(mem_failed);
	newstack->l = xlist_new();
	newstack->size = 0;
	return newstack;
}

void xstack_delete(xstack *stk)
{
	assert(stk);
	xlist_delete(stk->l);
	free(stk);
}

xstack *xstack_clear(xstack *stk)
{
	assert(stk);
	xlist_clear(stk->l);
	stk->size = 0;
	return stk;
}

xstack *xstack_push(xstack *stk, void *data, size_t data_size)
{
	assert(stk);
	assert(data);
	assert(data_size != 0);
	xlist_insert_head(stk->l, data, data_size);
	++stk->size;
	return stk;
}

xstack *xstack_pop(xstack *stk)
{
	assert(stk);
	assert(stk->size > 0);
	xlist_remove_head(stk->l);
	--stk->size;
	return stk;
}

void *xstack_get_top(xstack *stk)
{
	assert(stk);
	assert(stk->size > 0);
	return xlist_get_head(stk->l);
}

int xstack_size(xstack *stk)
{
	assert(stk);
	return stk->size;
}

int xstack_empty(xstack *stk)
{
	assert(stk);
	return stk->size == 0;
}

