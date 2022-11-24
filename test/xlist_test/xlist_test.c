/**
 * @file xlist_test.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Testing routine of interface "xlist".
 * @version 1.0.0
 * @date 2022-11-24
 * 
 */

#include "../../src/xlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cmp(const void *a, const void *b)
{
	int aa = *(int *)a;
	int bb = *(int *)b;
	return aa != bb;
}

void apply(void *data, void *args)
{
	printf("%d ", *(int *)data);
}

void apply_add(void *data, void *args)
{
	int add = *(int *)args;
	(*(int *)data) += add;
}

/* Create a list for subsequent tests. */
xlist *xlist_create(void)
{
	xlist *l = xlist_new();
	for (int i = 0; i < 10; i++)
		xlist_insert_tail(l, &i, sizeof(int));
	return l;
}

/* Test xlist_new() */
void test_xlist_new(void)
{
	printf("The test of xlist_new() is running...\n");
	xlist *l = xlist_new();
	assert(l);
	xlist_delete(l);
}

/* Test xlist_delete() */
void test_xlist_delete(void)
{
	printf("The test of xlist_delete() is running...\n");
	xlist *l = xlist_create();
	xlist_delete(l);
}

/* Test xlist_clear() */
void test_xlist_clear(void)
{
	printf("The test of xlist_clear() is running...\n");
	xlist *l = xlist_create();
	xlist_clear(l);
	printf("length of l: %d\n", xlist_length(l));
	xlist_delete(l);
}

/* Test xlist_copy() */
void test_xlist_copy(void)
{
	printf("The test of xlist_copy() is running...\n");

	xlist *l1 = xlist_create();
	printf("l1: ");
	xlist_foreach(l1, apply, NULL);
	printf("\n");

	xlist *l2 = xlist_new();
	printf("l2: ");
	xlist_foreach(l2, apply, NULL);
	printf("\n");

	xlist_copy(l2, l1);

	printf("l1: ");
	xlist_foreach(l1, apply, NULL);
	printf("\n");

	printf("l2: ");
	xlist_foreach(l2, apply, NULL);
	printf("\n");

	xlist_delete(l1);
	xlist_delete(l2);
}

/* Test xlist_append() */
void test_xlist_append(void)
{
	printf("The test of xlist_append() is running...\n");
	xlist *l1 = xlist_create();
	xlist_remove_head(l1);
	printf("l1: ");
	xlist_foreach(l1, apply, NULL);
	printf("\n");

	xlist *l2 = xlist_create();
	printf("l2: ");
	xlist_foreach(l2, apply, NULL);
	printf("\n");

	xlist_append(l2, l1);

	printf("l1: ");
	xlist_foreach(l1, apply, NULL);
	printf("\n");

	printf("l2: ");
	xlist_foreach(l2, apply, NULL);
	printf("\n");

	xlist_delete(l1);
	xlist_delete(l2);
}

/* Test xlist_reverse() */
void test_xlist_reverse(void)
{
	printf("The test of xlist_reverse() is running...\n");
	xlist *l = xlist_create();
	printf("l: ");
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_reverse(l);
	printf("l: ");
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_delete(l);
}

/* Test xlist_foreach() */
void test_xlist_foreach(void)
{
	printf("The test of xlist_foreach() is running...\n");
	xlist *l = xlist_create();
	printf("l: ");
	xlist_foreach(l, apply, NULL);
	printf("\n");
	int add = 10;
	xlist_foreach(l, apply_add, &add);
	printf("l: ");
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_delete(l);
}

/* Test xlist_insert_head() */
void test_xlist_insert_head(void)
{
	printf("The test of xlist_insert_head() is running...\n");
	xlist *l = xlist_new();
	for (int i = 0; i < 5; i++)
		xlist_insert_head(l, &i, sizeof(int));
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_delete(l);
}

/* Test xlist_insert_tail() */
void test_xlist_insert_tail(void)
{
	printf("The test of xlist_insert_tail() is running...\n");
	xlist *l = xlist_new();
	for (int i = 0; i < 5; i++)
		xlist_insert_tail(l, &i, sizeof(int));
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_delete(l);
}

/* Test xlist_insert_pos() */
void test_xlist_insert_pos(void)
{
	printf("The test of xlist_insert_pos() is running...\n");
	xlist *l = xlist_new();
	int i;
	i = 0;
	xlist_insert_pos(l, 1, &i, sizeof(int));
	xlist_foreach(l, apply, NULL);
	printf("\n");
	/* It covers all posible positions from the first half
	 * to the second half.
	 */
	for (i = 1; i < 10; i++)
		xlist_insert_pos(l, 2, &i, sizeof(int));
	xlist_foreach(l, apply, NULL);
	printf("\n");
	for (i = 10; i < 30; i++)
		xlist_insert_pos(l, 10, &i, sizeof(int));
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_delete(l);
}


/* Test xlist_get_head() */
void test_xlist_get_head(void)
{
	printf("The test of xlist_get_head() is running...\n");
	xlist *l = xlist_create();
	xlist_foreach(l, apply, NULL);
	printf("\n");
	int a = *(int *)xlist_get_head(l);
	printf("buf = %d\n", a);
	xlist_delete(l);
}

/* Test xlist_get_tail() */
void test_xlist_get_tail(void)
{
	printf("The test of xlist_get_tail() is running...\n");
	xlist *l = xlist_create();
	xlist_foreach(l, apply, NULL);
	printf("\n");
	int a = *(int *)xlist_get_tail(l);
	printf("buf = %d\n", a);
	xlist_delete(l);
}

/* Test xlist_get_pos() */
void test_xlist_get_pos(void)
{
	printf("The test of xlist_get_pos() is running...\n");
	xlist *l = xlist_create();
	xlist_foreach(l, apply, NULL);
	printf("\n");
	int a = *(int *)xlist_get_pos(l, 3);  /* the first half */
	printf("buf = %d\n", a);
	a = *(int *)xlist_get_pos(l, 7);  /* the first half */
	printf("buf = %d\n", a);
	xlist_delete(l);
}

/* Test xlist_remove_head() */
void test_xlist_remove_head(void)
{
	printf("The test of xlist_remove_head() is running...\n");
	xlist *l = xlist_create();
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_remove_head(l);
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_delete(l);
}

/* Test xlist_remove_tail() */
void test_xlist_remove_tail(void)
{
	printf("The test of xlist_remove_tail() is running...\n");
	xlist *l = xlist_create();
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_remove_tail(l);
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_delete(l);
}

/* Test xlist_remove_pos() */
void test_xlist_remove_pos(void)
{
	printf("The test of xlist_remove_pos() is running...\n");
	xlist *l = xlist_create();
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_remove_pos(l, 3);
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_remove_pos(l, 6);
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_delete(l);
}

/* Test xlist_find() */
void test_xlist_find(void)
{
	xlist *l = xlist_create();
	printf("The test of xlist_find() is running...\n");
	(void)xlist_foreach(l, apply, NULL);
	printf("\n");
	int i;
	int *a;
	i = 2;
	if ((a = xlist_find(l, &i, cmp)))
		printf("elem 2 is in: %d\n", *a);
	else
		printf("%d is not found\n", i);

	i = 9;
	if ((a = xlist_find(l, &i, cmp)))
		printf("elem 9 is in: %d\n", *a);
	else
		printf("%d is not found\n", i);

	i = 114514;
	if ((a = xlist_find(l, &i, cmp)))
		printf("elem 114514 is in: %d\n", *a);
	else
		printf("%d is not found\n", i);
	xlist_delete(l);
}

int main(int argc, char *argv[])
{
	test_xlist_new();
	test_xlist_delete();
	test_xlist_clear();
	test_xlist_copy();
	test_xlist_append();
	test_xlist_reverse();
	test_xlist_foreach();
	test_xlist_insert_head();
	test_xlist_insert_tail();
	test_xlist_insert_pos();
	test_xlist_get_head();
	test_xlist_get_tail();
	test_xlist_get_pos();
	test_xlist_remove_head();
	test_xlist_remove_tail();
	test_xlist_remove_pos();
	test_xlist_find();
	return 0;
}

