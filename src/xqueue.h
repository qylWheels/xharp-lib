/**
 * @file xqueue.h
 * @author qylWheels (command1748165360@126.com)
 * @brief This interface provides queue that can store any type of data.
 * @version 1.0.0
 * @date 2022-11-24
 *
 */

#include <stdbool.h>
#ifndef XHARPLIB_XQUEUE_H_INCLUDED
#define XHARPLIB_XQUEUE_H_INCLUDED 1

#include "xharp.h"
#include "xexcept.h"
#include "xlist.h"
#include <stddef.h>

extern xexcept mem_failed;

struct xqueue;
typedef struct xqueue xqueue;

__XHARPLIB_BEGIN_DECLS

extern xqueue *xqueue_new(void);

extern void xqueue_delete(xqueue *q);

extern xqueue *xqueue_clear(xqueue *q);

extern xqueue *xqueue_clone(xqueue *q);

extern xqueue *xqueue_clone_to(xqueue *dest, xqueue *src);

extern xqueue *xqueue_in(xqueue *q, const void *data, size_t data_size);

extern xqueue *xqueue_out(xqueue *q);

extern void *xqueue_get_front(xqueue *q);

extern void *xqueue_get_rear(xqueue *q);

extern size_t xqueue_length(xqueue *q);

extern bool xqueue_empty(xqueue *q);

__XHARPLIB_END_DECLS

#endif  /* XHARPLIB_XQUEUE_H_INCLUDED */

