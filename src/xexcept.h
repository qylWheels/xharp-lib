/**
 * @file xexcept.h
 * @author qylWheels (command1748165360@126.com)
 * @brief This interface provides a series of facilities that catch exceptions.
 *        You should ONLY use macros as follows:
 *        XTRY, XEXCEPT, XELSE, XFINALLY, XENDTRY, XRAISE.
 * @version 1.0.0
 * @date 2022-10-19
 * 
 */

#ifndef XHARPLIB_XEXCEPT_H_INCLUDED
#define XHARPLIB_XEXCEPT_H_INCLUDED

#include "xharp.h"
#include <setjmp.h>
#include <string.h>

typedef const char *xexcept_t;

struct _xexcept_frame {
    xexcept_t                _e;
    jmp_buf                  _env;
    const char              *_file;
    int                      _line;
    struct _xexcept_frame   *_prev;
};

enum _xexcept_flag {
    _XEXCEPT_ENTERED = 0,
    _XEXCEPT_RAISED,
    _XEXCEPT_HANDLED,
    _XEXCEPT_FINALIZED,
};

__XHARPLIB_BEGIN_DECLS

extern struct _xexcept_frame *_xexcept_stack;

extern void xexcept_raise(xexcept_t e, const char *file, int line);

__XHARPLIB_END_DECLS

#define XRAISE(e)                                       \
    xexcept_raise(e, __FILE__, __LINE__)

#define XTRY                                            \
do {                                                    \
    volatile int _xexcept_flag;                         \
    struct _xexcept_frame _xexcept_frame;               \
    _xexcept_frame._prev = _xexcept_stack;              \
    _xexcept_stack = &_xexcept_frame;                   \
    _xexcept_flag = setjmp(_xexcept_frame._env);        \
    if (_xexcept_flag == _XEXCEPT_ENTERED) {

#define XEXCEPT(e)                                      \
    if (_xexcept_flag == _XEXCEPT_ENTERED)              \
        _xexcept_stack = _xexcept_stack->_prev;         \
    } else if (strcmp(_xexcept_frame._e, (e)) == 0) {   \
        _xexcept_flag = _XEXCEPT_HANDLED;               \

#define XELSE                                           \
    if (_xexcept_flag == _XEXCEPT_ENTERED)              \
        _xexcept_stack = _xexcept_stack->_prev;         \
    } else {                                            \
        _xexcept_flag = _XEXCEPT_HANDLED;               \

#define XFINALLY                                        \
    if (_xexcept_flag == _XEXCEPT_ENTERED)              \
        _xexcept_stack = _xexcept_stack->_prev;         \
    } {                                                 \
    if (_xexcept_flag == _XEXCEPT_ENTERED)              \
        _xexcept_flag = _XEXCEPT_FINALIZED;                  

#define XENDTRY                                         \
    if (_xexcept_flag == _XEXCEPT_ENTERED)              \
        _xexcept_stack = _xexcept_stack->_prev;         \
    }                                                   \
    if (_xexcept_flag == _XEXCEPT_RAISED)               \
        xexcept_raise(_xexcept_frame._e, _xexcept_frame._file,  \
                      _xexcept_frame._line);            \
} while (0);

#endif  /* XHARPLIB_XEXCEPT_H_INCLUDED */
