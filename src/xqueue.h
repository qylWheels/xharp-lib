/**
 * @file xqueue.h
 * @author qylWheels (command1748165360@126.com)
 * @brief This interface provides queue that can store any type of data.
 * @version 1.0.0
 * @date 2022-11-16
 *
 */

#ifndef XHARPLIB_XQUEUE_H_INCLUDED
#define XHARPLIB_XQUEUE_H_INCLUDED 1

#include "xharp.h"
#include "xexcept.h"
#include "xlist.h"
#include <stddef.h>

extern xexcept_t mem_failed;
extern xexcept_t buf_failed;

struct _xqueue;
typedef struct _xqueue xqueue_t;

__XHARPLIB_BEGIN_DECLS

extern xqueue_t *xqueue_new(void);

extern void xqueue_delete(xqueue_t *q);

extern xqueue_t *xqueue_clear(xqueue_t *q);

extern xqueue_t *xqueue_in(xqueue_t *q, void *data, size_t data_size);

extern xqueue_t *xqueue_out(xqueue_t *q);

extern xqueue_t *xqueue_get_front(xqueue_t *q, void *buf, size_t buf_size);

extern xqueue_t *xqueue_get_rear(xqueue_t *q, void *buf, size_t buf_size);

extern int xqueue_length(xqueue_t *q);

extern int xqueue_empty(xqueue_t *q);

__XHARPLIB_END_DECLS

#endif  /* XHARPLIB_XQUEUE_H_INCLUDED */

