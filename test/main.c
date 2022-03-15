/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:40:33 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/15 20:18:51 by bkandemi         ###   ########.fr       */
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
	ft_printf("%f", nb);
	printf(" <- ft_printf\n");
	printf(format, nb);
	printf(" <- original\n");
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
	}
}

int main(void)
{
	//int neg = -8;
	//uintmax_t pos = 0;

	printf("test for positive integer:\n");

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
	/*test_int("%hhX", 'a');
	test_int("%hX", -32768);
	test_int("%hX", 32767);
	test_int("%lX", 922337203685477580);
	test_int("%lX", -922337203685477580);
	test_int("%lX", -2147483648);*/
	//test_int("%llX", 9223372036854775807);
	//test_int("%llX", -9223372036854775808);
	/*ft_printf("%hX", (short)-6);
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
	ft_printf("%.0X", 0);*/
	
	/*printf("(%d)", ft_printf("%#llX", 18446744073709551615ULL));
	printf("\n");
	printf("(%d)", printf("%#llX", 18446744073709551615ULL));*/


	ft_printf("%f", 2.5555525);
	printf(" <- ft_printf\n");
	printf("%.0f",  2.5555525);
	printf(" <- original\n");

	//random_double_test(0, 1);


	


	//printf("test for negative integer:\n");

	/*test_int("%X", neg);
	test_int("%-X", neg);
	test_int("%+X", neg);
	test_int("% X", neg);
	test_int("%---X", neg);
	test_int("%+++X", neg);
	test_int("%   X", neg);
	test_int("%-+X", neg);
	test_int("%- X", neg);
	test_int("%5X", neg);
	test_int("%+5X", neg);
	test_int("%-5X", neg);
	test_int("%-+5X", neg);
	test_int("%- 5X", neg);
	test_int("%.3X", neg);
	test_int("%-.3X", neg);
	test_int("%-+.3X", neg);
	test_int("%- .3X", neg);
	test_int("%6.3X", neg);
	test_int("%-6.3X", neg);
	test_int("%-+6.3X", neg);
	test_int("%- 6.3X", neg);
	test_int("% 6.3X", neg);
	test_int("%+6.3X", neg);
	test_int("%05X", neg);
	test_int("%0+5X", neg);
	test_int("% 05X", neg);*/
	
	return (0);
}


/*
for d or i
.  if precision > strlen, add leading (precision - strlen) zeros {
		if width > (precision) and no dash_flag, add (width - precision - strlen) leading space  
		if there is dash_flag add (width - precision - strlen) trailing space}
	else if precision <= strlen, print str.



*/