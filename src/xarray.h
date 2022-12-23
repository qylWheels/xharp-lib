/**
 * @file xarray.h
 * @author qylWheels (command1748165360@126.com)
 * @brief This interface provides dynamic array that can store any type of data.
 * @version 1.0.0
 * @date 2022-11-28
 *
 */

#ifndef XHARPLIB_XARRAY_H_INCLUDED
#define XHARPLIB_XARRAY_H_INCLUDED 1

#include "xharp.h"
#include "xexcept.h"
#include <stddef.h>
#include <stdbool.h>

extern xexcept mem_failed;

struct xarray;
typedef struct xarray xarray;

__XHARPLIB_BEGIN_DECLS

extern xarray *xarray_new(size_t block_count, size_t block_size);

extern void xarray_delete(xarray *arr);

extern xarray *xarray_clone(xarray *arr);

extern xarray *xarray_clone_to(xarray *dest, xarray *src);

extern xarray *xarray_resize(xarray *arr, size_t new_block_count);

extern xarray *xarray_put(xarray *arr, size_t index,
		const void *data, size_t data_size);

extern void *xarray_get(xarray *arr, size_t index);

extern size_t xarray_block_count(xarray *arr);

extern size_t xarray_block_size(xarray *arr);

__XHARPLIB_END_DECLS

#endif  /* XHARPLIB_XARRAY_H_INCLUDED */

