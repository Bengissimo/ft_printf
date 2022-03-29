/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:40:33 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/29 09:54:56 by bkandemi         ###   ########.fr       */
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
	printf(" <- original\n\n");
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

void test_int_no_flag(void)
{
	printf("test_int_no_flag:\n");
	test_int("%.10d", -123);
	test_int("%.10i", -123);
	test_int("%.10u", -123);
	test_int("%.10o", -123);
	test_int("%.10x", -123);
	test_int("%.10X", -123);
}

void test_int_only_width(void)
{
	printf("test_int_only_width:\n");
	test_int("%15.10d", -123);
	test_int("%15.10i", -123);
	test_int("%15.10u", -123);
	test_int("%15.10o", -123);
	test_int("%15.10x", -123);
	test_int("%15.10X", -123);
}

void test_int_width_zero(void)
{
	printf("test_int_width_zero:\n");
	test_int("%05d", -123);
	test_int("%05i", -123);
	test_int("%05u", -123);
	test_int("%05o", -123);
	test_int("%05x", -123);
	test_int("%05X", -123);
}

void test_int_width_zero_plus(void)
{
	printf("test_int_width_zero_plus:\n");
	test_int("%+05d", -123);
	test_int("%+05i", -123);
	test_int("%+05u", -123);
	test_int("%+05o", -123);
	test_int("%+05x", -123);
	test_int("%+05X", -123);
}

void test_int_width_zero_space(void)
{
	printf("test_int_width_zero_space:\n");	
	test_int("% 05d", -123);
	test_int("% 05i", -123);
	test_int("% 05u", -123);
	test_int("% 05o", -123);
	test_int("% 05x", -123);
	test_int("% 05X", -123);
}

void test_int_width_zero_hash(void)
{
	printf("test_int_width_zero_hash:\n");

	test_int("%#05d", -123);
	test_int("%#05i", -123);
	test_int("%#05u", -123);
	test_int("%#05o", -123);
	test_int("%#05x", -123);
	test_int("%#05X", -123);
}

void test_int_width_hash_plus(void)
{
	printf("test_int_width_hash_plus: \n");
	test_int("%#+15.10d", -123);
	test_int("%#+15.10i", -123);
	test_int("%#+15.10u", -123);
	test_int("%#+15.10o", -123);
	test_int("%#+15.10x", -123);
	test_int("%#+15.10X", -123);
}

void test_int_width_hash(void)
{
	printf("test_int_width_hash: \n");
	test_int("%#15.10d", -123);
	test_int("%#15.10i", -123);
	test_int("%#15.10u", -123);
	test_int("%#15.10o", -123);
	test_int("%#15.10x", -123);
	test_int("%#15.10X", -123);
}

void test_int_hash_prec(void)
{
	printf("test_int_hash: \n");
	test_int("%#.10d", -123);
	test_int("%#.10i", -123);
	test_int("%#.10u", -123);
	test_int("%#.10o", -123);
	test_int("%#.10x", -123);
	test_int("%#.10X", -123);
}

void test_int_width_plus(void)
{
	printf("test_int_width_plus:\n");
	test_int("%+15.10d", -123);
	test_int("%+15.10i", -123);
	test_int("%+15.10u", -123);
	test_int("%+15.10o", -123);
	test_int("%+15.10x", -123);
	test_int("%+15.10X", -123);
}

void test_int_width_space(void)
{
	printf("test_int_width_space:\n");
	test_int("% 15.10d", -123);
	test_int("% 15.10i", -123);
	test_int("% 15.10u", -123);
	test_int("% 15.10o", -123);
	test_int("% 15.10x", -123);
	test_int("% 15.10X", -123);
}

void test_int_width_plus_zero(void)
{
	printf("test_int_width_plus_zero:\n");
	test_int("%+05d", -123);
	test_int("%+05i", -123);
	test_int("%+05u", -123);
	test_int("%+05o", -123);
	test_int("%+05x", -123);
	test_int("%+05X", -123);
}

void test_int_width_plus_zero_hash(void)
{
	printf("test_int_width_plus_zero_hash:\n");
	test_int("%+0#5d", -123);
	test_int("%+0#5i", -123);
	test_int("%+0#5u", -123);
	test_int("%+0#5o", -123);
	test_int("%+0#5x", -123);
	test_int("%+0#5X", -123);
}


void test_int_dash(void)
{
	printf("test_int_dash:\n");
	test_int("%-.10d", -123);
	test_int("%-.10i", -123);
	test_int("%-.10u", -123);
	test_int("%-.10o", -123);
	test_int("%-.10x", -123);
	test_int("%-.10X", -123);
}

void test_int_dash_width(void)
{
	printf("test_int_dash_width:\n");
	test_int("%-16.10d", -123);
	test_int("%-16.10i", -123);
	test_int("%-16.10u", -123);
	test_int("%-16.10o", -123);
	test_int("%-16.10x", -123);
	test_int("%-16.10X", -123);
}


void test_int_dash_width_zero(void)
{
	printf("test_int_dash_width_zero:\n");
	test_int("%-06d", -123);
	test_int("%-06i", -123);
	test_int("%-06u", -123);
	test_int("%-06o", -123);
	test_int("%-06x", -123);
	test_int("%-06X", -123);
}

void test_int_dash_width_plus(void)
{
	printf("test_int_dash_width_plus:\n");
	test_int("%-+16.10d", -123);
	test_int("%-+16.10i", -123);
	test_int("%-+16.10u", -123);
	test_int("%-+16.10o", -123);
	test_int("%-+16.10x", -123);
	test_int("%-+16.10X", -123);
}

void test_int_dash_width_space(void)
{
	printf("test_int_dash_width_space:\n");
	test_int("%- 16.10d", -123);
	test_int("%- 16.10i", -123);
	test_int("%- 16.10u", -123);
	test_int("%- 16.10o", -123);
	test_int("%- 16.10x", -123);
	test_int("%- 16.10X", -123);
}

void test_int_dash_width_hash(void)
{
	printf("test_int_dash_width_hash:\n");
	test_int("%-#16.10d", -123);
	test_int("%-#16.10i", -123);
	test_int("%-#16.10u", -123);
	test_int("%-#16.10o", -123);
	test_int("%-#16.10x", -123);
	test_int("%-#16.10X", -123);
}

void test_int_dash_width_plus_hash(void)
{
	printf("test_int_dash_width_plus_hash:\n");
	test_int("%-+#16.10d", -123);
	test_int("%-+#16.10i", -123);
	test_int("%-+#16.10u", -123);
	test_int("%-+#16.10o", -123);
	test_int("%-+#16.10x", -123);
	test_int("%-+#16.10X", -123);
}

void	test_int_plus(void)
{
	printf("test_int_plus:\n");
	test_int("%+d", -123);
	test_int("%+i", -123);
	test_int("%+u", -123);
	test_int("%+o", -123);
	test_int("%+x", -123);
	test_int("%+X", -123);
}

void	test_int_space(void)
{
	printf("test_int_space:\n");
	test_int("% d", -123);
	test_int("% i", -123);
	test_int("% u", -123);
	test_int("% o", -123);
	test_int("% x", -123);
	test_int("% X", -123);
}


void	test_int_hash(void)
{
	printf("test_int_hash:\n");
	test_int("%#d", -123);
	test_int("%#i", -123);
	test_int("%#u", -123);
	test_int("%#o", -123);
	test_int("%#x", -123);
	test_int("%#X", -123);
}

void	test_int_hash_plus(void)
{
	printf("test_int_hash_plus:\n");
	test_int("%#+d", -123);
	test_int("%#+i", -123);
	test_int("%#+u", -123);
	test_int("%#+o", -123);
	test_int("%#+x", -123);
	test_int("%#+X", -123);
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
	
	/*test_int("%hhX", 'a');
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
	printf(" <- original\n\n");*/

	random_double_test(20, 22);

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

	test_int_no_flag();
	test_int_only_width();
	test_int_hash_prec();
	test_int_width_hash();
	test_int_width_hash_plus();
	test_int_width_zero();
	test_int_width_zero_hash();
	test_int_width_zero_plus();
	test_int_width_zero_space();
	test_int_width_plus();
	test_int_width_space();
	test_int_width_plus_zero();
	test_int_width_plus_zero_hash();

	test_int_dash();
	test_int_dash_width();
	test_int_dash_width_hash();
	test_int_dash_width_plus();
	test_int_dash_width_plus_hash();
	test_int_dash_width_space();
	test_int_dash_width_zero();

	test_int_hash();
	test_int_hash_plus();
	test_int_plus();
	test_int_space();

	ft_printf("%#.3o", -0);
	printf(" <- ft_printf\n");
	printf("%#.3o", -0);
	printf(" <- original\n\n");
	
	ft_printf("%5p", -0);
	printf(" <- ft_printf\n");
	printf("%5p", -0);
	printf(" <- original\n\n");

	ft_printf("{%05.*d}", -15, 42);
	printf(" <- ft_printf\n");
	printf("{%05.*d}", -15, 42);
	printf(" <- original\n\n");

	ft_printf("{e}", 42.0);
	printf(" <- ft_printf\n");
	printf("{e}", 42.0);
	printf(" <- original\n\n");


	
	

	
	return (0);
}
