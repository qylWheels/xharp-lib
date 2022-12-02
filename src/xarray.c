/**
 * @file xarray.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of interface "xarray".
 * @version 1.0.0
 * @date 2022-11-29
 *
 */

#include "xarray.h"
#include "xexcept.h"
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct xarray {
	void		*data;
	int		 block_count;
	int		 block_capacity;
	size_t		 block_size;
};

xarray *xarray_new(int block_count, size_t block_size)
{
	assert(block_count > 0);
	assert(block_size != 0);
	xarray *newarray = (xarray *)malloc(sizeof *newarray);
	if (!newarray)
		XRAISE(mem_failed);
	size_t total_size = (size_t)block_count * block_size;
	newarray->data 			= malloc(total_size);
	if (!newarray->data)
		XRAISE(mem_failed);
	newarray->block_count 		= block_count;
	newarray->block_capacity 	= block_count;
	newarray->block_size 		= block_size;
	return newarray;
}

void xarray_delete(xarray *arr)
{
	assert(arr);
	free(arr->data);
	free(arr);
}

xarray *xarray_clone(xarray *dest, xarray *src)
{
	assert(dest);
	assert(src);
	assert(dest->block_size == src->block_size);
	if (dest->block_capacity >= src->block_count) {
		dest->block_count = src->block_count;
	} else {
		xarray_resize(dest, src->block_count);
	}
	size_t total_size = (size_t)src->block_count * src->block_size;
	memmove(dest->data, src->data, total_size);
	return dest;
}

xarray *xarray_resize(xarray *arr, int new_block_count)
{
	assert(arr);
	assert(new_block_count > 0);
	if (new_block_count <= arr->block_capacity) {
		arr->block_count = new_block_count;
		return arr;
	} else {
		void *new_data = malloc(new_block_count * arr->block_size);
		if (!new_data)
			XRAISE(mem_failed);
		memmove(new_data, arr->data, arr->block_count * arr->block_size);
		free(arr->data);
		arr->data 		= new_data;
		arr->block_count 	= new_block_count;
		arr->block_capacity 	= new_block_count;
		return arr;
	}
}

xarray *xarray_put(xarray *arr, int index,
		const void *data, size_t data_size)
{
	assert(arr);
	assert(index < arr->block_count);
	assert(index >= -(arr->block_count));
	assert(data);
	assert(data_size <= arr->block_size);
	void *target_pos = NULL;
	if (index >= 0)
		target_pos = arr->data + index * arr->block_size;
	else
		target_pos = arr->data + (arr->block_count + index) * arr->block_size;
	memmove(target_pos, data, data_size);
	return arr;
}

void *xarray_get(xarray *arr, int index)
{
	assert(arr);
	assert(index < arr->block_count);
	assert(index >= -(arr->block_count));
	if (index >= 0)
		return arr->data + index * arr->block_size;
	else
		return arr->data + (arr->block_count + index) * arr->block_size;
}

int xarray_block_count(xarray *arr)
{
	assert(arr);
	return arr->block_count;
}

size_t xarray_block_size(xarray *arr)
{
	assert(arr);
	return arr->block_size;
}


