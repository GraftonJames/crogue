
#include <stdio.h> 
#include <stdarg.h> 

void print_to_stderr(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "log:");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}
