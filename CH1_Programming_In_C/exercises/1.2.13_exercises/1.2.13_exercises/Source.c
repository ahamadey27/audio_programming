#include <stdio.h>
#include <math.h>

int main()
{
	/*Use sizeof() and printf() to report the size in bites of major data types */
	int size_int = sizeof(size_int);
	char size_char = sizeof(size_char);
	short size_short = sizeof(size_short);
	float size_float = sizeof(size_float);
	long size_long = sizeof(size_long);
	double size_double = sizeof(size_double);

	printf("Size of ineger: %d.\nSize of char: %d\nSize of short: %d\nSize of float: %d\nSize of long: %d\nSize of double: %d\n", 
		size_int, size_char, size_short, size_float, size_long, size_double);


	return 0;
}