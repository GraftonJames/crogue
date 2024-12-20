#include <stdio.h>
#include <errno.h>


void outputError(
	bool useErr,
	int *format,
	bool flushStdout,
	const char *format,
	va_list ap
) {

#define BUF_SIZE 500

	char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];

	vsnprintf(userMsg, BUF_SIZE, format, ap)

	
	if (useErr) {
	}
}
