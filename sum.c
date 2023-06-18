/**
 * A C code that takes user input,...
 * calculates sum, and prints out thr result
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int a, b, sum;
	
	system("clear");
	/* Ask for first number */
	printf("Enter the first number: ");
	scanf("%d", &a);

	/* Ask for second number */
	printf("Enter the second number: ");
	scanf("%d", &b);

	/* Calculate sum */
	sum = a + b;

	/* output information */
	printf("%d + %d = %d\n", a, b, sum);

	return (0);
}
