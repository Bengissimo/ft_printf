#include <stdio.h>


int main(void)
{
	double a = 0.5554545345;
	double b = 0.555454;
	double c = 0.555455;
	printf("%f\n", a - b);
	printf("%f\n", c - a);
	printf("%.6f\n", a);
	return (0);
}