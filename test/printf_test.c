#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

static double power(int nb, int power)
{
	double	result;
	
	result = 1.0;
	if (power == 0)
		return (1.0);
	if (power < 0)
	{
		while (power < 0)
		{
			result = result / nb;
			power++;
		}
		return (result);
	}
	while (power > 0)
	{
		result = result * nb;
		power--;
	}
	return (result);
}

int main(void)
{
	/*double a = 0.56789123;
	double b = 17;
	double c = 18;
	printf("%f\n", a - b);
	printf("%f\n", c - a);
	printf("%.f\n", a);
	//printf("%f\n", 912.9 % 10.0);
	printf("%f\n", 912.9 / 100.0);
	printf("%f\n", 912.9 / 1000.0);
	printf("%f\n", 912.9 / 10000.0);
	printf("%d\n",(int)912.9);*/

	/*printf("%f\n", power(10, 0));
	printf("%f\n", power(10, -1));
	printf("%f\n", power(10, -2));
	printf("%f\n", power(10, -3));
	printf("%f\n", power(10, 3));
	printf("%f\n", power(10, 4));
	printf("%f\n", power(10, 5));
	printf("%f\n", power(10, 6));
	printf("%f\n", power(10, 7));
	printf("%f\n", power(10, 8));
	printf("%f\n", power(10, 9));
	printf("%f\n", power(10, 10));
	printf("%f\n", power(10, 11));
	printf("%f\n", power(10, 12));
	printf("%f\n", power(10, 13));
	printf("%f\n", power(10, 14));
	printf("%f\n", power(10, 15));
	printf("%f\n", power(10, 16));
	printf("%f\n", power(10, 17));
	printf("%f\n", power(10, 18));
	printf("%f\n", power(10, 19));
	printf("%f\n", power(10, 20));*/

	
	int a = printf("(%.123d)\n", 0);
	int b = printf("(%-5.0d)\n", 0);

	printf("a: %d b: %d\n", a, b);
	printf("%zd\n", write(1, "\0", 1));

	printf("%.10x\n", 123);
	printf("%#.10x\n", 123);

	printf("%.20e\n", 340282300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000006548767898754546576876.0);

	//printf("expect: [% z5%]\n");




	return (0);
}