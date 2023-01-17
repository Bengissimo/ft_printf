#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
	ft_printf("%.10f", -0.47560392166578300);
	printf(" <- ft_printf\n");
	printf("%.10f",  -0.47560392166578300);
	printf(" <- original\n\n");
	return (0);
}
