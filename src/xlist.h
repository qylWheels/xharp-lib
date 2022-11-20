/**
 * @file xlist.h
 * @author qylWheels (command1748165360@126.com)
 * @brief This interface provides linked lists that can store any type of data.
 * @version 1.0.0
 * @date 2022-11-17
 *
 */

#ifndef XHARPLIB_XLIST_H_INCLUDED
#define XHARPLIB_XLIST_H_INCLUDED 1

#include "xharp.h"
#include "xexcept.h"
#include <stddef.h>

extern xexcept_t mem_failed;
extern xexcept_t buf_failed;

struct _xlist;
typedef struct _xlist xlist_t;

typedef int (*xlist_apply_fn)(void *data, void *args);
typedef int (*xlist_compare_fn)(const void *a, const void *b);

__XHARPLIB_BEGIN_DECLS

extern xlist_t *xlist_new(void);

extern void xlist_delete(xlist_t *l);

extern xlist_t *xlist_clear(xlist_t *l);

extern xlist_t *xlist_copy(xlist_t *dest, xlist_t *src);

extern xlist_t *xlist_append(xlist_t *l, xlist_t *tail);

extern xlist_t *xlist_reverse(xlist_t *l);

extern void xlist_foreach(xlist_t *l, xlist_apply_fn apply, void *args);

extern xlist_t *xlist_insert_head(xlist_t *l, void *data, size_t data_size);

extern xlist_t *xlist_insert_tail(xlist_t *l, void *data, size_t data_size);

extern xlist_t *xlist_insert_pos(xlist_t *l, int pos, void *data, size_t data_size);

extern xlist_t *xlist_get_head(xlist_t *l, void *buf, size_t buf_size);

extern xlist_t *xlist_get_tail(xlist_t *l, void *buf, size_t buf_size);

extern xlist_t *xlist_get_pos(xlist_t *l, int pos, void *buf, size_t buf_size);

extern xlist_t *xlist_remove_head(xlist_t *l);

extern xlist_t *xlist_remove_tail(xlist_t *l);

extern xlist_t *xlist_remove_pos(xlist_t *l, int pos);

extern int xlist_find(xlist_t *l, void *data, xlist_compare_fn compare);

extern int xlist_length(xlist_t *l);

extern int xlist_empty(xlist_t *l);

__XHARPLIB_END_DECLS

#endif  /* XHARPLIB_XLIST_H_INCLUDED */

