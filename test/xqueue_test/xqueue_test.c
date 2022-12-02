/**
 * @file xqueue_test.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Testing routine of interface "xqueue".
 * @version 1.0.0
 * @date 2022-11-25
 * 
 */

#include "../../src/xqueue.h"
#include <stdio.h>

/* Create a non-empty queue */
xqueue *xqueue_create(void)
{
	xqueue *q = xqueue_new();
	for (int i = 1; i <= 5; ++i)
		xqueue_in(q, &i, sizeof(i));
	return q;
}

/* Test of xqueue_new() and xqueue_delete() */
void test_xqueue_new_and_delete(void)
{
	printf("Test of xqueue_new() and xqueue_delete() is running...\n");
	xqueue *q = xqueue_new();
	xqueue_delete(q);
}

/* Test of xqueue_clear() */
void test_xqueue_clear(void)
{
	printf("Test of xqueue_clear() is running...\n");
	xqueue *q = xqueue_create();
	xqueue_clear(q);
	printf("len = %d\n", xqueue_length(q));
	xqueue_delete(q);
}

/* Test of xqueue_in() and xqueue_out() */
void test_xqueue_in_and_out(void)
{
	printf("Test of xqueue_in_and_out() is running...\n");
	xqueue *q = xqueue_create();
	int i = 114514;
	int a;
	xqueue_in(q, &i, sizeof(i));
	if (!xqueue_empty(q))
		a = *(int *)xqueue_get_front(q);
	printf("a = %d\n", a);
	xqueue_out(q);
	if (!xqueue_empty(q))
		a = *(int *)xqueue_get_rear(q);
	printf("a = %d\n", a);
	xqueue_delete(q);
}


int main(int argc, char *argv[])
{
	test_xqueue_new_and_delete();
	test_xqueue_clear();
	test_xqueue_in_and_out();
	return 0;
}

