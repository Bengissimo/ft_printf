/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:40:33 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/22 13:04:55 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
 #include <stdlib.h>

/* return values are in parenthesis */
void	test_int(char *format, uintmax_t nb)
{
	printf("(%d)", ft_printf(format, nb));
	printf(" <- ft_printf\n");
	printf("(%d)", printf(format, nb));
	printf(" <- original\n");
}


void	test_double(char *format, double nb)
{
	int ft_ret;
	int pf_ret;
	ft_ret = ft_printf(format, nb);
	printf(" <- ft_printf\n");
	pf_ret = printf(format, nb);
	printf(" <- original\n\n");
	if (ft_ret != pf_ret)
		printf("return values are different\n\n");
}

double db_random(int low, int high)
{
	return (high - low + 1) * rand() / (double) INT32_MAX + low;	
}

void random_double_test(int low, int high)
{
	for (int i = 0; i < 100; i++)
	{
		test_double("%.10f", db_random(low, high));
		printf("\n");
	}
}

void random_int_test()
{
	
}

int main(void)
{
	//int neg = -8;
	//uintmax_t pos = 0;

	//printf("test for positive integer:\n");

	/*test_int("%X", pos);
	test_int("%#X", pos);
	test_int("%#.0X", pos);
	test_int("%.0X", pos);*/
	/*test_int("%---X", pos);
	test_int("%+++X", pos);
	test_int("%   X", pos);
	test_int("%-+X", pos);
	test_int("%- X", pos);
	test_int("%5X", pos);
	test_int("%+5X", pos);
	test_int("%-5X", pos);
	test_int("%-+5X", pos);
	test_int("%- 5X", pos);
	test_int("%.3X", pos);
	test_int("%-.3X", pos);
	test_int("%-+.3X", pos);
	test_int("%- .3X", pos);
	test_int("%5.3X", pos);
	test_int("%-5.3X", pos);
	test_int("%-+5.3X", pos);
	test_int("%- 5.3X", pos);
	test_int("% 6.3X", pos);
	test_int("%+6.3X", pos);
	test_int("%05X", pos);
	test_int("%0+5X", pos);
	test_int("% 05X", pos);
	test_int("%0.0X", pos);*/
	/*test_int("%hX", pos);
	test_int("%lX", pos);
	test_int("%llX", pos);*/
	test_int("%hhX", 'a');
	test_int("%hX", -32768);
	test_int("%hX", 32767);
	test_int("%lX", 922337203685477580);
	test_int("%lX", -922337203685477580);
	test_int("%lX", -2147483648);
	test_int("%llX", 9223372036854775807L);
	test_int("%llX", -9223372036854775808);
	ft_printf("%hX", (short)-6);
	printf("\n");
	printf("%hX", (short)-6);
	printf("\n");
	ft_printf("%hX", (short)5);
	printf("\n");
	printf("%hX", (short)5);
	printf("\n");
	ft_printf("%hX", (short)-32768);
	printf("\n");
	printf("%hX", (short)-32768);
	printf("\n");
	ft_printf("%hX", (short)32764);
	printf("\n");
	printf("%hX", (short)32764);
	printf("\n");
	ft_printf("%hhX", (char)97);
	printf("\n");
	printf("%hhX", (char)97);
	printf("\n");
	printf("%.0d\n", 0);
	ft_printf("%.0X", 0);
	
	int nb = 8;
	int *p_nb;
	p_nb = &nb;

	ft_printf("%p", p_nb);
	printf(" <- ft_printf\n");
	printf("%p", p_nb);
	printf(" <- original\n\n");

	ft_printf("%.3f", 0.0005);
	printf(" <- ft_printf\n");
	printf("%.3f",  0.0005);
	printf(" <- original\n\n");

	ft_printf("%.4f", 0.0004);
	printf(" <- ft_printf\n");
	printf("%.4f",  0.0004);
	printf(" <- original\n\n");

	ft_printf("%.4f", 0.00015);
	printf(" <- ft_printf\n");
	printf("%.4f",  0.00015);
	printf(" <- original\n\n");

	ft_printf("%.4f", 0.00025);
	printf(" <- ft_printf\n");
	printf("%.4f",  0.00025);
	printf(" <- original\n\n");

	ft_printf("%.4f", 0.00035);
	printf(" <- ft_printf\n");
	printf("%.4f",  0.00035);
	printf(" <- original\n\n");

	ft_printf("%.4f", 0.00045);
	printf(" <- ft_printf\n");
	printf("%.4f",  0.00045);
	printf(" <- original\n\n");

	ft_printf("%.4f", 0.00055);
	printf(" <- ft_printf\n");
	printf("%.4f",  0.00055);
	printf(" <- original\n\n");

	ft_printf("%f", 2.5555545);
	printf(" <- ft_printf\n");
	printf("%f",  2.5555545);
	printf(" <- original\n\n");

	ft_printf("%.0f", 0.5);
	printf(" <- ft_printf\n");
	printf("%.0f",  0.5);
	printf(" <- original\n\n");

	ft_printf("%.0f", 1.5);
	printf(" <- ft_printf\n");
	printf("%.0f",  1.5);
	printf(" <- original\n\n");

	ft_printf("%.0f", 2.5);
	printf(" <- ft_printf\n");
	printf("%.0f",  2.5);
	printf(" <- original\n\n");

	ft_printf("%.0f", 3.5);
	printf(" <- ft_printf\n");
	printf("%.0f",  3.5);
	printf(" <- original\n\n");

	ft_printf("%.0f", 3.5);
	printf(" <- ft_printf\n");
	printf("%.0f",  3.5);
	printf(" <- original\n\n");

	ft_printf("%.0f", 4.5);
	printf(" <- ft_printf\n");
	printf("%.0f",  4.5);
	printf(" <- original\n\n");

	ft_printf("%.0f", 5.5);
	printf(" <- ft_printf\n");
	printf("%.0f",  5.5);
	printf(" <- original\n\n");

	ft_printf("%.0f", 6.5);
	printf(" <- ft_printf\n");
	printf("%.0f",  6.5);
	printf(" <- original\n\n");

	ft_printf("%.0f", 7.5);
	printf(" <- ft_printf\n");
	printf("%.0f",  7.5);
	printf(" <- original\n\n");

	ft_printf("%    -30.20Lf", 314.01L);
	printf(" <- ft_printf\n");
	printf("%    -30.20Lf",  314.01L);
	printf(" <- original\n\n");

	//random_double_test(0, 1);

	test_int("%u", 4294967295);
	test_int("%o", 4294967295);
	test_int("%x", 4294967295);
	test_int("%X", 4294967295);
	test_int("%#o", 4294967295);
	test_int("%#x", 4294967295);
	test_int("%#X", 4294967295);

	ft_printf("%.10f", -0.47560392166578300);
	printf(" <- ft_printf\n");
	printf("%.10f",  -0.47560392166578300);
	printf(" <- original\n\n");

	int ft_ret = ft_printf("%-5c, %5d    jdgfjhgsdf %+.10%", 'a', 5);
	printf(" <- ft_printf\n");
	int pf_ret = printf("%-5c, %5d    jdgfjhgsdf %+.10%", 'a', 5);
	printf(" <- original\n\n");
	if (ft_ret != pf_ret)
		printf("return values are different\n\n");

	return (0);
}
