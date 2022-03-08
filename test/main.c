/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:40:33 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/08 15:35:16 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* return values are in parenthesis */
void	test_int(char *format, uintmax_t nb)
{
	printf("(%d)", ft_printf(format, nb));
	printf(" <- ft_printf\n");
	printf("(%d)", printf(format, nb));
	printf(" <- original\n");
}

int main(void)
{
	//int neg = -8;
	uintmax_t pos = 100;

	printf("test for positive integer:\n");

	test_int("%o", pos);
	test_int("%#o", pos);
	test_int("%#.0o", pos);
	test_int("%.0o", pos);
	/*test_int("%---o", pos);
	test_int("%+++o", pos);
	test_int("%   o", pos);
	test_int("%-+o", pos);
	test_int("%- o", pos);
	test_int("%5o", pos);
	test_int("%+5o", pos);
	test_int("%-5o", pos);
	test_int("%-+5o", pos);
	test_int("%- 5o", pos);
	test_int("%.3o", pos);
	test_int("%-.3o", pos);
	test_int("%-+.3o", pos);
	test_int("%- .3o", pos);
	test_int("%5.3o", pos);
	test_int("%-5.3o", pos);
	test_int("%-+5.3o", pos);
	test_int("%- 5.3o", pos);
	test_int("% 6.3o", pos);
	test_int("%+6.3o", pos);
	test_int("%05o", pos);
	test_int("%0+5o", pos);
	test_int("% 05o", pos);
	test_int("%0.0o", pos);*/
	/*test_int("%ho", pos);
	test_int("%lo", pos);
	test_int("%llo", pos);*/
	/*test_int("%hho", 'a');
	test_int("%ho", -32768);
	test_int("%ho", 32767);
	test_int("%lo", 922337203685477580);
	test_int("%lo", -922337203685477580);
	test_int("%lo", -2147483648);*/
	//test_int("%llo", 9223372036854775807);
	//test_int("%llo", -9223372036854775808);
	/*ft_printf("%ho", (short)-6);
	printf("\n");
	printf("%ho", (short)-6);
	printf("\n");
	ft_printf("%ho", (short)5);
	printf("\n");
	printf("%ho", (short)5);
	printf("\n");
	ft_printf("%ho", (short)-32768);
	printf("\n");
	printf("%ho", (short)-32768);
	printf("\n");
	ft_printf("%ho", (short)32764);
	printf("\n");
	printf("%ho", (short)32764);
	printf("\n");
	ft_printf("%hho", (char)97);
	printf("\n");
	printf("%hho", (char)97);
	printf("\n");
	printf("%.0d\n", 0);
	ft_printf("%.0o", 0);*/
	
	printf("(%d)", ft_printf("%#llo", 18446744073709551615ULL));
	printf("\n");
	printf("(%d)", printf("%#llo", 18446744073709551615ULL));





	//printf("test for negative integer:\n");

	/*test_int("%o", neg);
	test_int("%-o", neg);
	test_int("%+o", neg);
	test_int("% o", neg);
	test_int("%---o", neg);
	test_int("%+++o", neg);
	test_int("%   o", neg);
	test_int("%-+o", neg);
	test_int("%- o", neg);
	test_int("%5o", neg);
	test_int("%+5o", neg);
	test_int("%-5o", neg);
	test_int("%-+5o", neg);
	test_int("%- 5o", neg);
	test_int("%.3o", neg);
	test_int("%-.3o", neg);
	test_int("%-+.3o", neg);
	test_int("%- .3o", neg);
	test_int("%6.3o", neg);
	test_int("%-6.3o", neg);
	test_int("%-+6.3o", neg);
	test_int("%- 6.3o", neg);
	test_int("% 6.3o", neg);
	test_int("%+6.3o", neg);
	test_int("%05o", neg);
	test_int("%0+5o", neg);
	test_int("% 05o", neg);*/
	
	return (0);
}


/*
for d or i
.  if precision > strlen, add leading (precision - strlen) zeros {
		if width > (precision) and no dash_flag, add (width - precision - strlen) leading space  
		if there is dash_flag add (width - precision - strlen) trailing space}
	else if precision <= strlen, print str.



*/