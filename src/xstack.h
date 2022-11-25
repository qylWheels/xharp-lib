/**
 * @file xstack.h
 * @author qylWheels (command1748165360@126.com)
 * @brief This interface provides stack that can store any type of data.
 * @version 1.0.0
 * @date 2022-11-25
 *
 */

#ifndef XHARPLIB_XSTACK_H_INCLUDED
#define XHARPLIB_XSTACK_H_INCLUDED 1

#include "xharp.h"
#include "xexcept.h"
#include "xlist.h"
#include <stddef.h>

extern xexcept mem_failed;

struct xstack;
typedef struct xstack xstack;

__XHARPLIB_BEGIN_DECLS

extern xstack *xstack_new(void);

extern void xstack_delete(xstack *stk);

extern xstack *xstack_clear(xstack *stk);

extern xstack *xstack_push(xstack *stk, void *data, size_t data_size);

extern xstack *xstack_pop(xstack *stk);

extern void *xstack_get_top(xstack *stk);

extern int xstack_size(xstack *stk);

extern int xstack_empty(xstack *stk);

__XHARPLIB_END_DECLS

#endif  /* XHARPLIB_XSTACK_H_INCLUDED */

