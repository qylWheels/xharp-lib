/**
 * @file xexcept_test.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Testing routine of interface "xexcept".
 * @version 1.0.0
 * @date 2022-11-24
 * 
 */

#include "../../src/xexcept.h"
#include <stdio.h>

/* Directly raise an exception */
xexcept foo = "foo";
void test1(void)
{
    XRAISE(foo);
    printf("114514\n");  /* This line SHOULDN'T be executed */
}

/* Use TRY-EXCEPT-ELSE-ENDTRY structure */
xexcept bar = "bar";
xexcept baz = "baz";
xexcept other = "other";
void bar_func(void)
{
    XRAISE(bar);
}
void test2(void)
{
    XTRY {
        bar_func();
    } XEXCEPT(bar) {
        printf("raised \"bar\"\n");
    } XEXCEPT(baz) {
        printf("raised \"baz\"\n");
    } XELSE {  /* Delete this block will cause an uncaught exception */
        printf("raised other exception\n");
    } XENDTRY;
}

/* Use TRY-EXCEPT-ELSE-FINALLY-ENDTRY structure */
xexcept file_open_failed = "failed to open file";
FILE *file_open(const char *path, const char *mode)
{
    FILE *fp = fopen(path, mode);
    if (!fp)
        XRAISE(file_open_failed);
    else
        return fp;
}
void test3(void)
{
    FILE *fp;
    XTRY {
        fp = file_open("xexcept_test.log", "r");
    } XEXCEPT (file_open_failed) {
        fprintf(stderr, "Open file failed\n");
    } XELSE {
        printf("raised other exception\n");
    } XFINALLY {
        printf("XFINALLY branch\n");  /* This line MUST be executed */
    } XENDTRY;
}

int main(void)
{
    // test1();

    // test2();

    test3();

    return 0;
}
