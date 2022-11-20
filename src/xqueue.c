/**
 * @file xqueue.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of interface "xqueue".
 * @version 1.0.0
 * @date 2022-11-17
 *
 */

#include "xqueue.h"
#include <stdlib.h>
#include <assert.h>

struct _xqueue {
	xlist_t 	*_l;
	int	 	 _length;
};

xqueue_t *xqueue_new(void)
{
	xqueue_t *newqueue;
	newqueue = (xqueue_t *)malloc(sizeof *newqueue);
	if (!newqueue)
		XRAISE(mem_failed);
	newqueue->_l = xlist_new();
	newqueue->_length = 0;
	return newqueue;
}

void xqueue_delete(xqueue_t *q)
{
	assert(q);
	xlist_delete(q->_l);
	free(q);
}

xqueue_t *xqueue_clear(xqueue_t *q)
{
	assert(q);
	xlist_clear(q->_l);
	q->_length = 0;
	return q;
}

xqueue_t *xqueue_in(xqueue_t *q, void *data, size_t data_size)
{
	assert(q);
	assert(data);
	assert(data_size != 0);
	xlist_insert_tail(q->_l, data, data_size);
	++q->_length;
	return q;
}

xqueue_t *xqueue_out(xqueue_t *q)
{
	assert(q);
	xlist_remove_head(q->_l);
	--q->_length;
	return q;
}

xqueue_t *xqueue_get_front(xqueue_t *q, void *buf, size_t buf_size)
{
	assert(q);
	assert(buf);
	assert(buf_size != 0);
	xlist_get_head(q->_l, buf, buf_size);
	return q;
}

xqueue_t *xqueue_get_rear(xqueue_t *q, void *buf, size_t buf_size)
{
	assert(q);
	assert(buf);
	assert(buf_size != 0);
	xlist_get_tail(q->_l, buf, buf_size);
	return q;
}

int xqueue_length(xqueue_t *q)
{
	assert(q);
	return q->_length;
}

int xqueue_empty(xqueue_t *q)
{
	assert(q);
	return q->_length == 0;
}

