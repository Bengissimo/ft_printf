#include <stdio.h>


int main(void)
{
	double a = 0.56789123;
	double b = 17;
	double c = 18;
	printf("%f\n", a - b);
	printf("%f\n", c - a);
	printf("%.f\n", a);
	//printf("%f\n", 912.9 % 10.0);
	printf("%f\n", 912.9 / 100.0);
	printf("%f\n", 912.9 / 1000.0);
	printf("%f\n", 912.9 / 10000.0);
	printf("%d\n",(int)912.9);
	return (0);
}