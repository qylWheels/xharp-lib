/**
 * @file xarray_test.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Testing routine of interface "xarray".
 * @version 1.0.0
 * @date 2022-12-2
 * 
 */

#include "../../src/xarray.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	xarray *arr1 = xarray_new(10, sizeof(int));
	xarray *arr2 = xarray_new(1, sizeof(int));

	printf("arr1's block count: %ld\n", xarray_block_count(arr1));
	printf("arr1's block size: %ld\n", xarray_block_size(arr1));
	printf("arr2's block count: %ld\n", xarray_block_count(arr2));
	printf("arr2's block size: %ld\n", xarray_block_size(arr2));
	
	for (int i = 0; i < xarray_block_count(arr1); ++i)
		xarray_put(arr1, i, &i, sizeof(i));

	for (int i = 0; i < xarray_block_count(arr1); ++i)
		printf("arr1[%d] = %d\n", i, *(int *)xarray_get(arr1, i));

	xarray *arr3 = xarray_clone(arr1);
	printf("arr3's block count: %ld\n", xarray_block_count(arr3));
	printf("arr3's block size: %ld\n", xarray_block_size(arr3));
	for (int i = 0; i < xarray_block_count(arr3); ++i)
		printf("arr3[%d] = %d\n", i, *(int *)xarray_get(arr3, i));

	xarray_clone_to(arr2, arr1);
	printf("arr2's block count: %ld\n", xarray_block_count(arr2));
	printf("arr2's block size: %ld\n", xarray_block_size(arr2));
	for (int i = 0; i < xarray_block_count(arr2); ++i)
		printf("arr2[%d] = %d\n", i, *(int *)xarray_get(arr2, i));
	
	xarray_resize(arr1, 20);
	printf("arr1's block count: %ld\n", xarray_block_count(arr1));
	printf("arr1's block size: %ld\n", xarray_block_size(arr1));
	for (int i = 0; i < xarray_block_count(arr1); ++i)
		printf("arr1[%d] = %d\n", i, *(int *)xarray_get(arr1, i));
	
	xarray_resize(arr1, 5);
	printf("arr1's block count: %ld\n", xarray_block_count(arr1));
	printf("arr1's block size: %ld\n", xarray_block_size(arr1));
	for (int i = 0; i < xarray_block_count(arr1); ++i)
		printf("arr1[%d] = %d\n", i, *(int *)xarray_get(arr1, i));

	xarray_delete(arr1);
	xarray_delete(arr2);
	xarray_delete(arr3);
}
