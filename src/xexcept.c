/**
 * @file xexcept.c
 * @author qylWheels (command1748165360@126.com)
 * @brief Implementation of interface "xexcept".
 * @version 1.0.0
 * @date 2022-11-24
 * 
 */

#include "xexcept.h"
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>  /* abort() */

struct _xexcept_frame *_xexcept_stack = NULL;

void xexcept_raise(xexcept e, const char *file, int line)
{
	struct _xexcept_frame *ef = _xexcept_stack;
	if (!ef) {
		fprintf(stderr, "Uncaught exception: ");
	if (e)
		fprintf(stderr, "%s\n", e);
	else
		fprintf(stderr, "(Undefined exception)\n");
	if (file && line > 0)
		fprintf(stderr, "Raised at %s:%d\n", file, line);
	else
		fprintf(stderr, "Unable to locate exception trigger point\n");
	fprintf(stderr, "Aborting...\n");
	fflush(stderr);
	abort();
	}
	ef->_e		= e;
	ef->_file	= file;
	ef->_line	= line;
	_xexcept_stack	= ef->_prev;
	longjmp(ef->_env, _XEXCEPT_RAISED);
}
