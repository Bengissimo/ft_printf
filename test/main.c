/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:40:33 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/08 11:00:31 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* original printf result is in parenthesis */
void	test_int(char *format, uintmax_t nb)
{
	ft_printf(format, nb);
	printf("(");
	printf(format, nb);
	printf(")\n\n");
}

int main(void)
{
	//int neg = -8;
	uintmax_t pos = 100;

	printf("test for positive integer:\n");

	test_int("%u", 4294967295);
	test_int("%-u", pos);
	test_int("%+u", pos);
	test_int("% u", pos);
	test_int("%---u", pos);
	test_int("%+++u", pos);
	test_int("%   u", pos);
	test_int("%-+u", pos);
	test_int("%- u", pos);
	test_int("%5u", pos);
	test_int("%+5u", pos);
	test_int("%-5u", pos);
	test_int("%-+5u", pos);
	test_int("%- 5u", pos);
	test_int("%.3u", pos);
	test_int("%-.3u", pos);
	test_int("%-+.3u", pos);
	test_int("%- .3u", pos);
	test_int("%5.3u", pos);
	test_int("%-5.3u", pos);
	test_int("%-+5.3u", pos);
	test_int("%- 5.3u", pos);
	test_int("% 6.3u", pos);
	test_int("%+6.3u", pos);
	test_int("%05u", pos);
	test_int("%0+5u", pos);
	test_int("% 05u", pos);
	test_int("%0.0u", pos);
	/*test_int("%hu", pos);
	test_int("%lu", pos);
	test_int("%llu", pos);*/
	/*test_int("%hhu", 'a');
	test_int("%hu", -32768);
	test_int("%hu", 32767);
	test_int("%lu", 922337203685477580);
	test_int("%lu", -922337203685477580);
	test_int("%lu", -2147483648);*/
	//test_int("%llu", 9223372036854775807);
	//test_int("%llu", -9223372036854775808);
	/*ft_printf("%hu", (short)-6);
	printf("\n");
	printf("%hu", (short)-6);
	printf("\n");
	ft_printf("%hu", (short)5);
	printf("\n");
	printf("%hu", (short)5);
	printf("\n");
	ft_printf("%hu", (short)-32768);
	printf("\n");
	printf("%hu", (short)-32768);
	printf("\n");
	ft_printf("%hu", (short)32764);
	printf("\n");
	printf("%hu", (short)32764);
	printf("\n");
	ft_printf("%hhu", (char)97);
	printf("\n");
	printf("%hhu", (char)97);
	printf("\n");
	printf("%.0d\n", 0);
	ft_printf("%.0u", 0);*/
	
	ft_printf("%llu", 18446744073709551615ULL);
	printf("\n");
	printf("%llu", 18446744073709551615ULL);





	//printf("test for negative integer:\n");

	/*test_int("%u", neg);
	test_int("%-u", neg);
	test_int("%+u", neg);
	test_int("% u", neg);
	test_int("%---u", neg);
	test_int("%+++u", neg);
	test_int("%   u", neg);
	test_int("%-+u", neg);
	test_int("%- u", neg);
	test_int("%5u", neg);
	test_int("%+5u", neg);
	test_int("%-5u", neg);
	test_int("%-+5u", neg);
	test_int("%- 5u", neg);
	test_int("%.3u", neg);
	test_int("%-.3u", neg);
	test_int("%-+.3u", neg);
	test_int("%- .3u", neg);
	test_int("%6.3u", neg);
	test_int("%-6.3u", neg);
	test_int("%-+6.3u", neg);
	test_int("%- 6.3u", neg);
	test_int("% 6.3u", neg);
	test_int("%+6.3u", neg);
	test_int("%05u", neg);
	test_int("%0+5u", neg);
	test_int("% 05u", neg);*/
	
	return (0);
}


/*
for d or i
.  if precision > strlen, add leading (precision - strlen) zeros {
		if width > (precision) and no dash_flag, add (width - precision - strlen) leading space  
		if there is dash_flag add (width - precision - strlen) trailing space}
	else if precision <= strlen, print str.



*/