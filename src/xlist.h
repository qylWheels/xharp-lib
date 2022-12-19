/**
 * @file xlist.h
 * @author qylWheels (command1748165360@126.com)
 * @brief This interface provides linked lists that can store any type of data.
 * @version 1.0.0
 * @date 2022-11-24
 *
 */

#ifndef XHARPLIB_XLIST_H_INCLUDED
#define XHARPLIB_XLIST_H_INCLUDED 1

#include "xharp.h"
#include "xexcept.h"
#include <stddef.h>
#include <stdbool.h>

extern xexcept mem_failed;

struct xlist;
typedef struct xlist xlist;

__XHARPLIB_BEGIN_DECLS

extern xlist *xlist_new(void);

extern void xlist_delete(xlist *l);

extern xlist *xlist_clear(xlist *l);

extern xlist *xlist_clone(xlist *l);

extern xlist *xlist_clone_to(xlist *dest, xlist *src);

extern xlist *xlist_append(xlist *l, xlist *tail);

extern xlist *xlist_reverse(xlist *l);

extern xlist *xlist_foreach(xlist *l,
		void (*apply_fn)(void *node_data, void *args),
		void *args);

extern xlist *xlist_insert_head(xlist *l, const void *data, size_t data_size);

extern xlist *xlist_insert_tail(xlist *l, const void *data, size_t data_size);

extern xlist *xlist_insert_pos(xlist *l, size_t pos,
		const void *data, size_t data_size);

extern void *xlist_get_head(xlist *l);

extern void *xlist_get_tail(xlist *l);

extern void *xlist_get_pos(xlist *l, size_t pos);

extern xlist *xlist_remove_head(xlist *l);

extern xlist *xlist_remove_tail(xlist *l);

extern xlist *xlist_remove_pos(xlist *l, size_t pos);

extern void *xlist_find(xlist *l, const void *data,
		int (*compare_fn)(const void *node_data, const void *user_data));

extern size_t xlist_length(xlist *l);

extern bool xlist_empty(xlist *l);

__XHARPLIB_END_DECLS

#endif  /* XHARPLIB_XLIST_H_INCLUDED */

