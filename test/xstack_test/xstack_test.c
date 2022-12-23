/**
 * @file xstack_test.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Testing routine of interface "xstack".
 * @version 1.0.0
 * @date 2022-11-25
 * 
 */

#include "../../src/xstack.h"
#include <stdio.h>

/* Create a non-empty stack */
xstack *xstack_create(void)
{
	xstack *stk = xstack_new();
	for (int i = 1; i <= 5; ++i)
		xstack_push(stk, &i, sizeof(i));
	return stk;
}

/* Test of xstack_new() and xstack_delete() */
void test_xstack_new_and_delete(void)
{
	printf("Test of xstack_new() and xstack_delete() is running...\n");
	xstack *stk = xstack_new();
	xstack_delete(stk);
	printf("\n");
}

/* Test of xstack_clear() */
/* xstack_size() will also be test */
void test_xstack_clear(void)
{
	printf("Test of xstack_clear() is running...\n");
	xstack *stk = xstack_create();
	printf("size = %ld\n", xstack_size(stk));
	xstack_clear(stk);
	printf("size = %ld\n", xstack_size(stk));
	xstack_delete(stk);
	printf("\n");
}

/* Test of xstack_clone() */
void test_xstack_clone(void)
{
	printf("Test of xstack_clone() is running...\n");
	xstack *stk1 = xstack_create();
	xstack *stk2 = xstack_clone(stk1);
	printf("stk1: ");
	while (!xstack_empty(stk1)) {
		printf("%d ", *(int *)xstack_get_top(stk1));
		xstack_pop(stk1);
	}
	printf("\n");
	printf("stk2: ");
	while (!xstack_empty(stk2)) {
		printf("%d ", *(int *)xstack_get_top(stk2));
		xstack_pop(stk2);
	}
	xstack_delete(stk1);
	xstack_delete(stk2);
	printf("\n\n");
}

/* Test of xstack_clone_to() */
void test_xstack_clone_to(void)
{
	printf("Test of xstack_clone_to() is running...\n");
	xstack *stk1 = xstack_create();
	xstack *stk2 = xstack_create();
	xstack_clone_to(stk1, stk2);
	printf("stk1: ");
	while (!xstack_empty(stk1)) {
		printf("%d ", *(int *)xstack_get_top(stk1));
		xstack_pop(stk1);
	}
	printf("\n");
	printf("stk2: ");
	while (!xstack_empty(stk2)) {
		printf("%d ", *(int *)xstack_get_top(stk2));
		xstack_pop(stk2);
	}
	xstack_delete(stk1);
	xstack_delete(stk2);
	printf("\n\n");
}

/* Test of xstack_push(), xstack_pop() and xstack_get_top() */
/* xstack_empty() will also be test */
void test_xstack_push_pop_gettop(void)
{
	printf("Test of xstack_push(), xstack_pop() and xstack_get_top()"
		" is running\n");
	xstack *stk = xstack_create();
	/* xstack_push() has been tested in xstack_create() */
	int a;
	if (!xstack_empty(stk))
		a = *(int *)xstack_get_top(stk);
	printf("a = %d\n", a);
	if (!xstack_empty(stk))
		xstack_pop(stk);
	if (!xstack_empty(stk))
		a = *(int *)xstack_get_top(stk);
	printf("a = %d\n", a);
	xstack_delete(stk);
	printf("\n");
}

int main(int argc, char *argv[])
{
	test_xstack_new_and_delete();
	test_xstack_clear();
	test_xstack_clone();
	test_xstack_clone_to();
	test_xstack_push_pop_gettop();
	return 0;
}

