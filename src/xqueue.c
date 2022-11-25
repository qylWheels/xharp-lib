/**
 * @file xqueue.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of interface "xqueue".
 * @version 1.0.0
 * @date 2022-11-25
 *
 */

#include "xqueue.h"
#include <stdlib.h>
#include <assert.h>

struct xqueue {
	xlist		*l;
	int	 	 length;
};

xqueue *xqueue_new(void)
{
	xqueue *newqueue;
	newqueue = (xqueue *)malloc(sizeof *newqueue);
	if (!newqueue)
		XRAISE(mem_failed);
	newqueue->l = xlist_new();
	newqueue->length = 0;
	return newqueue;
}

void xqueue_delete(xqueue *q)
{
	assert(q);
	xlist_delete(q->l);
	free(q);
}

xqueue *xqueue_clear(xqueue *q)
{
	assert(q);
	xlist_clear(q->l);
	q->length = 0;
	return q;
}

xqueue *xqueue_in(xqueue *q, void *data, size_t data_size)
{
	assert(q);
	assert(data);
	assert(data_size != 0);
	xlist_insert_tail(q->l, data, data_size);
	++q->length;
	return q;
}

xqueue *xqueue_out(xqueue *q)
{
	assert(q);
	assert(q->length > 0);
	xlist_remove_head(q->l);
	--q->length;
	return q;
}

void *xqueue_get_front(xqueue *q)
{
	assert(q);
	assert(q->length > 0);
	return xlist_get_head(q->l);
}

void *xqueue_get_rear(xqueue *q)
{
	assert(q);
	assert(q->length > 0);
	return xlist_get_tail(q->l);
}

int xqueue_length(xqueue *q)
{
	assert(q);
	return q->length;
}

int xqueue_empty(xqueue *q)
{
	assert(q);
	return q->length == 0;
}

