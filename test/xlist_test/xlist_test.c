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

int apply(void *data, void *args)
{
	printf("%d ", *(int *)data);
	return 0;
}

int apply_add(void *data, void *args)
{
	int add = *(int *)args;
	(*(int *)data) += add;
	return 0;
}

/* Create a list for subsequent tests. */
xlist_t *xlist_create(void)
{
	xlist_t *l = xlist_new();
	for (int i = 0; i < 10; i++)
		xlist_insert_tail(l, &i, sizeof(int));
	return l;
}

/* Test xlist_new() */
void test_xlist_new(void)
{
	printf("The test of xlist_new() is running...\n");
	xlist_t *l = xlist_new();
	assert(l);
	assert(l->_first == NULL);
	assert(l->_length == 0);
	xlist_delete(l);
}

/* Test xlist_delete() */
void test_xlist_delete(void)
{
	printf("The test of xlist_delete() is running...\n");
	xlist_t *l = xlist_create();
	xlist_delete(l);
}

/* Test xlist_clear() */
void test_xlist_clear(void)
{
	printf("The test of xlist_clear() is running...\n");
	xlist_t *l = xlist_create();
	xlist_clear(l);
	assert(!l->_first);
	assert(l->_length == 0);
	xlist_delete(l);
}

/* Test xlist_copy() */
void test_xlist_copy(void)
{
	printf("The test of xlist_copy() is running...\n");

	xlist_t *l1 = xlist_create();
	printf("l1: ");
	xlist_foreach(l1, apply, NULL);
	printf("\n");

	xlist_t *l2 = xlist_new();
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
}

/* Test xlist_append() */
void test_xlist_append(void)
{
	printf("The test of xlist_append() is running...\n");
	xlist_t *l1 = xlist_create();
	xlist_remove_head(l1);
	printf("l1: ");
	xlist_foreach(l1, apply, NULL);
	printf("\n");

	xlist_t *l2 = xlist_create();
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
}

/* Test xlist_reverse() */
void test_xlist_reverse(void)
{
	printf("The test of xlist_reverse() is running...\n");
	xlist_t *l = xlist_create();
	printf("l: ");
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_reverse(l);
	printf("l: ");
	xlist_foreach(l, apply, NULL);
	printf("\n");
}

/* Test xlist_foreach() */
void test_xlist_foreach(void)
{
	printf("The test of xlist_foreach() is running...\n");
	xlist_t *l = xlist_create();
	printf("l: ");
	xlist_foreach(l, apply, NULL);
	printf("\n");
	int add = 10;
	xlist_foreach(l, apply_add, &add);
	printf("l: ");
	xlist_foreach(l, apply, NULL);
	printf("\n");
}

/* Test xlist_insert_head() */
void test_xlist_insert_head(void)
{
	printf("The test of xlist_insert_head() is running...\n");
	xlist_t *l = xlist_new();
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
	xlist_t *l = xlist_new();
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
	xlist_t *l = xlist_new();
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
	int buf;
	xlist_t *l = xlist_create();
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_get_head(l, &buf, sizeof(buf));
	printf("buf = %d\n", buf);
	xlist_delete(l);
}

/* Test xlist_get_tail() */
void test_xlist_get_tail(void)
{
	printf("The test of xlist_get_tail() is running...\n");
	int buf;
	xlist_t *l = xlist_create();
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_get_tail(l, &buf, sizeof(buf));
	printf("buf = %d\n", buf);
	xlist_delete(l);
}

/* Test xlist_get_pos() */
void test_xlist_get_pos(void)
{
	printf("The test of xlist_get_pos() is running...\n");
	int buf;
	xlist_t *l = xlist_create();
	xlist_foreach(l, apply, NULL);
	printf("\n");
	xlist_get_pos(l, 3, &buf, sizeof(buf));  /* the first half */
	printf("buf = %d\n", buf);
	xlist_get_pos(l, 7, &buf, sizeof(buf));  /* the second half */
	printf("buf = %d\n", buf);
	// char buf2;
	// xlist_get_pos(l, 7, &buf2, sizeof(buf2));  /* raise "buf_failed" */
	xlist_delete(l);
}

/* Test xlist_remove_head() */
void test_xlist_remove_head(void)
{
	printf("The test of xlist_remove_head() is running...\n");
	xlist_t *l = xlist_create();
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
	xlist_t *l = xlist_create();
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
	xlist_t *l = xlist_create();
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
	xlist_t *l = xlist_create();
	printf("The test of xlist_find() is running...\n");
	(void)xlist_foreach(l, apply, NULL);
	printf("\n");
	int i;
	i = 2;
	printf("elem 2 is in: %d\n", xlist_find(l, &i, cmp));
	i = 9;
	printf("elem 9 is in: %d\n", xlist_find(l, &i, cmp));
	i = 114514;
	printf("elem 114514 is in: %d\n", xlist_find(l, &i, cmp));
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

