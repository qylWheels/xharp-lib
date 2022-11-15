#include "xlist.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

xexcept_t mem_failed = "Memory alloc failed";
xexcept_t buf_failed = "Buffer size too small";

xlist_t *xlist_new(void)
{
	xlist_t *newlist;
	newlist = (xlist_t *)malloc(sizeof *newlist);
	if (!newlist)
		XRAISE(mem_failed);
	newlist->_first = NULL;
	newlist->_length = 0;
	return newlist;
}

void xlist_delete(xlist_t *l)
{
	assert(l);
	free(xlist_clear(l));
}

xlist_t *xlist_clear(xlist_t *l)
{
	assert(l);
	struct _xlist_node *n, *next;
	int iter = 0;
	for (n = l->_first; iter < l->_length; n = next) {
		++iter;
		next = n->_next;
		free(n);
	}
	l->_first = NULL;
	l->_length = 0;
	return l;
}

xlist_t *xlist_copy(xlist_t *dest, xlist_t *src)
{
	assert(dest);
	assert(src);
	xlist_clear(dest);
	return xlist_append(dest, src);
}

xlist_t *xlist_append(xlist_t *l, xlist_t *tail)
{
	assert(l);
	assert(tail);
	struct _xlist_node *n;
	int iter = 0;
	for (n = tail->_first; iter < tail->_length; n = n->_next) {
		++iter;
		xlist_insert_tail(l, n->_data, n->_data_size);
	}
	return l;
}

xlist_t *xlist_reverse(xlist_t *l)
{
	assert(l);
	struct _xlist_node *n, *tmp;
	int iter = 0;
	/* n = n->_prev? It seems a bit strange, but current "_prev" is
	 * actually "_next" before they are swapped.
	 */
	for (n = l->_first; iter < l->_length; n = n->_prev) {
		++iter;
		tmp = n->_prev;
		n->_prev = n->_next;
		n->_next = tmp;
		if (n->_prev == l->_first)
			break;
	}
	l->_first = n;
	return l;
}

void xlist_foreach(xlist_t *l, xlist_apply_fn apply, void *args)
{
	assert(l);
	assert(apply);
	struct _xlist_node *n;
	int iter = 0;
	for (n = l->_first; iter < l->_length; n = n->_next) {
		++iter;
		apply(n->_data, args);
	}
}

xlist_t *xlist_insert_head(xlist_t *l, void *data, size_t data_size)
{
	return xlist_insert_pos(l, 1, data, data_size);
}

xlist_t *xlist_insert_tail(xlist_t *l, void *data, size_t data_size)
{
	return xlist_insert_pos(l, l->_length + 1, data, data_size);
}

xlist_t *xlist_insert_pos(xlist_t *l, int pos, void *data, size_t data_size)
{
	assert(l);
	assert(pos >= 1 && pos <= l->_length + 1);	
	assert(data);
	assert(data_size != 0);
	struct _xlist_node *n, *newnode;
	int cur_pos;
	newnode = (struct _xlist_node *)malloc(sizeof *newnode + data_size);
	if (!newnode)
		XRAISE(mem_failed);
	newnode->_data = (void *)(newnode + 1);
	memmove(newnode->_data, data, data_size);
	newnode->_data_size = data_size;

	if (l->_length == 0) {
		newnode->_prev = newnode->_next = newnode;
	} else if (pos < l->_length / 2) {
		cur_pos = 1;
		for (n = l->_first; cur_pos++ < pos; n = n->_next);
	} else {
		cur_pos = l->_length + 1;
		for (n = l->_first; cur_pos-- > pos; n = n->_prev);
	}
	
	if (pos == 1)
		l->_first = newnode;
	if (l->_length > 0) {
		newnode->_next = n;
		newnode->_prev = n->_prev;
		n->_prev->_next = newnode;
		n->_prev = newnode;
	}
	++l->_length;

	return l;
}

xlist_t *xlist_get_head(xlist_t *l, void *buf, size_t buf_size)
{
	return xlist_get_pos(l, 1, buf, buf_size);
}

xlist_t *xlist_get_tail(xlist_t *l, void *buf, size_t buf_size)
{
	return xlist_get_pos(l, l->_length, buf, buf_size);
}

xlist_t *xlist_get_pos(xlist_t *l, int pos, void *buf, size_t buf_size)
{
	assert(l);
	assert(pos >= 1 && pos <= l->_length);
	assert(buf);
	struct _xlist_node *n;
	int cur_pos;
	if (pos < l->_length / 2) {
		cur_pos = 1;
		for (n = l->_first; cur_pos++ < pos; n = n->_next);
	} else {
		cur_pos = l->_length;
		for (n = l->_first->_prev; cur_pos-- > pos; n = n->_prev);
	}
	if (n->_data_size > buf_size)
		XRAISE(buf_failed);
	memmove(buf, n->_data, n->_data_size);
	return l;
}

xlist_t *xlist_remove_head(xlist_t *l)
{
	return xlist_remove_pos(l, 1);
}

xlist_t *xlist_remove_tail(xlist_t *l)
{
	return xlist_remove_pos(l, l->_length);
}

xlist_t *xlist_remove_pos(xlist_t *l, int pos)
{
	assert(l);
	assert(pos >= 1 && pos <= l->_length);
	struct _xlist_node *n;
	int cur_pos;
	if (pos < l->_length / 2) {
		cur_pos = 1;
		for (n = l->_first; cur_pos++ < pos; n = n->_next);
	} else {
		cur_pos = l->_length;
		for (n = l->_first->_prev; cur_pos-- > pos; n = n->_prev);
	}
	n->_prev->_next = n->_next;
	n->_next->_prev = n->_prev;
	if (pos == 1)
		l->_first = n->_next;
	free(n);
	--l->_length;
	return l;
}

int xlist_find(xlist_t *l, void *data, xlist_compare_fn compare)
{
	assert(l);
	assert(data);
	assert(compare);
	struct _xlist_node *n;
	int pos = 0;
	int flag = 0;
	for (n = l->_first; pos < l->_length; n = n->_next) {
		++pos;
		if (compare(data, n->_data) == 0) {
			flag = 1;
			break;
		}
	}
	if (flag)
		return pos;
	else
		return 0;
}

int xlist_length(xlist_t *l)
{
	assert(l);
	return l->_length;
}

int xlist_empty(xlist_t *l)
{
	assert(l);
	return l->_length == 0;
}

