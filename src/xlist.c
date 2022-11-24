/**
 * @file xlist.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of interface "xlist".
 * @version 1.0.0
 * @date 2022-11-24
 *
 */

#include "xlist.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct xlist_node {
	void			*data;
	size_t		 	 data_size;
	struct xlist_node	*prev;
	struct xlist_node	*next;
};

struct xlist {
	struct xlist_node	*first;
	int			 length;
};

xlist *xlist_new(void)
{
	xlist *newlist;
	newlist = (xlist *)malloc(sizeof *newlist);
	if (!newlist)
		XRAISE(mem_failed);
	newlist->first = NULL;
	newlist->length = 0;
	return newlist;
}

void xlist_delete(xlist *l)
{
	assert(l);
	free(xlist_clear(l));
}

xlist *xlist_clear(xlist *l)
{
	assert(l);
	struct xlist_node *n, *next;
	int iter = 0;
	for (n = l->first; iter < l->length; n = next) {
		++iter;
		next = n->next;
		free(n);
	}
	l->first = NULL;
	l->length = 0;
	return l;
}

xlist *xlist_copy(xlist *dest, xlist *src)
{
	assert(dest);
	assert(src);
	xlist_clear(dest);
	return xlist_append(dest, src);
}

xlist *xlist_append(xlist *l, xlist *tail)
{
	assert(l);
	assert(tail);
	struct xlist_node *n;
	int iter = 0;
	for (n = tail->first; iter < tail->length; n = n->next) {
		++iter;
		xlist_insert_tail(l, n->data, n->data_size);
	}
	return l;
}

xlist *xlist_reverse(xlist *l)
{
	assert(l);
	struct xlist_node *n, *tmp;
	int iter = 0;
	/* n = n->prev? It seems a bit strange, but current "prev" is
	 * actually "next" before they are swapped.
	 */
	for (n = l->first; iter < l->length; n = n->prev) {
		++iter;
		tmp = n->prev;
		n->prev = n->next;
		n->next = tmp;
		if (n->prev == l->first)
			break;
	}
	l->first = n;
	return l;
}

xlist *xlist_foreach(xlist *l,
		void (*apply_fn)(void *node_data, void *args),
		void *args)
{
	assert(l);
	assert(apply_fn);
	struct xlist_node *n;
	int iter = 0;
	for (n = l->first; iter < l->length; n = n->next) {
		++iter;
		apply_fn(n->data, args);
	}
	return l;
}

xlist *xlist_insert_head(xlist *l, void *data, size_t data_size)
{
	assert(l);
	assert(data);
	assert(data_size != 0);
	return xlist_insert_pos(l, 1, data, data_size);
}

xlist *xlist_insert_tail(xlist *l, void *data, size_t data_size)
{
	assert(l);
	assert(data);
	assert(data_size != 0);
	return xlist_insert_pos(l, l->length + 1, data, data_size);
}

xlist *xlist_insert_pos(xlist *l, int pos, void *data, size_t data_size)
{
	assert(l);
	assert(pos >= 1 && pos <= l->length + 1);	
	assert(data);
	assert(data_size != 0);
	struct xlist_node *n, *newnode;
	int cur_pos;
	newnode = (struct xlist_node *)malloc(sizeof *newnode + data_size);
	if (!newnode)
		XRAISE(mem_failed);
	newnode->data = (void *)(newnode + 1);
	memmove(newnode->data, data, data_size);
	newnode->data_size = data_size;

	if (l->length == 0) {
		newnode->prev = newnode->next = newnode;
	} else if (pos < l->length / 2) {
		cur_pos = 1;
		for (n = l->first; cur_pos++ < pos; n = n->next);
	} else {
		cur_pos = l->length + 1;
		for (n = l->first; cur_pos-- > pos; n = n->prev);
	}
	
	if (pos == 1)
		l->first = newnode;
	if (l->length > 0) {
		newnode->next = n;
		newnode->prev = n->prev;
		n->prev->next = newnode;
		n->prev = newnode;
	}
	++l->length;

	return l;
}

void *xlist_get_head(xlist *l)
{
	assert(l);
	return xlist_get_pos(l, 1);
}

void *xlist_get_tail(xlist *l)
{
	assert(l);
	return xlist_get_pos(l, l->length);
}

void *xlist_get_pos(xlist *l, int pos)
{
	assert(l);
	assert(pos >= 1 && pos <= l->length);
	struct xlist_node *n;
	int cur_pos;
	if (pos < l->length / 2) {
		cur_pos = 1;
		for (n = l->first; cur_pos++ < pos; n = n->next);
	} else {
		cur_pos = l->length;
		for (n = l->first->prev; cur_pos-- > pos; n = n->prev);
	}
	return n->data;
}

xlist *xlist_remove_head(xlist *l)
{
	assert(l);
	return xlist_remove_pos(l, 1);
}

xlist *xlist_remove_tail(xlist *l)
{
	assert(l);
	return xlist_remove_pos(l, l->length);
}

xlist *xlist_remove_pos(xlist *l, int pos)
{
	assert(l);
	assert(pos >= 1 && pos <= l->length);
	struct xlist_node *n;
	int cur_pos;
	if (pos < l->length / 2) {
		cur_pos = 1;
		for (n = l->first; cur_pos++ < pos; n = n->next);
	} else {
		cur_pos = l->length;
		for (n = l->first->prev; cur_pos-- > pos; n = n->prev);
	}
	n->prev->next = n->next;
	n->next->prev = n->prev;
	if (pos == 1)
		l->first = n->next;
	free(n);
	--l->length;
	return l;
}

void *xlist_find(xlist *l, void *data,
		int (*compare_fn)(const void *node_data, const void *user_data))
{
	assert(l);
	assert(data);
	assert(compare_fn);
	struct xlist_node *n;
	int pos = 0;
	int flag = 0;
	for (n = l->first; pos < l->length; n = n->next) {
		++pos;
		if (compare_fn(data, n->data) == 0) {
			flag = 1;
			break;
		}
	}
	if (flag)
		return n->data;
	else
		return NULL;
}

int xlist_length(xlist *l)
{
	assert(l);
	return l->length;
}

int xlist_empty(xlist *l)
{
	assert(l);
	return l->length == 0;
}

